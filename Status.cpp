/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.5 on 8/20/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#include "Status.h"

QuakeLiveRcon::Status::Status(array<System::String^>^ info)
{
	InitializeComponent();

	this->disconnect = false;
	this->info = info;
}

QuakeLiveRcon::Status::~Status()
{
	if (components)
	{
		delete components;
	}
	delete this->info;

}

System::Void QuakeLiveRcon::Status::close_Click(Object^  sender, System::EventArgs^  e) {
	TimeSpan waitTime = TimeSpan(0, 0, 0, 0, 100); //wait 100 milliseconds
	if (this->statusThread && this->statusThread->IsAlive) {
		this->statusThread->Abort();
		System::Threading::Thread::Sleep(waitTime);
	}

	this->disconnect = true;
	this->Close();
}

System::Void QuakeLiveRcon::Status::Window_Load(System::Object^  sender, System::EventArgs^  e) {

}

System::Void QuakeLiveRcon::Status::Window_Shown(System::Object^  sender, System::EventArgs^  e) {
	this->statusThread = gcnew Thread(gcnew ThreadStart(this, &QuakeLiveRcon::Status::connectToServer));
	this->statusThread->Start();
}

void QuakeLiveRcon::Status::connectToServer() {
	int count = 0;
	String^ serverString = "tcp://" + this->info[0] + ":" + this->info[1];
	//convert ip:port to char*
	pin_ptr<const wchar_t> wch = PtrToStringChars(serverString);
	const size_t origsize = wcslen(wch) + 1;
	const size_t newsize = origsize * 2;
	size_t convertedChars = 0;
	char * server = new char[newsize];
	wcstombs_s(&convertedChars, server, newsize, wch, _TRUNCATE);
	delete serverString;
	serverString = nullptr;
	wch = nullptr; //unhooks 'wch' from the memory now being used by 'server'

	void * context = zmq_ctx_new();
	void * socket = zmq_socket(context, ZMQ_SUB);
	
	if (String::Compare(this->info[2], "")) {
		//convert password to char*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(this->info[2]);
		const size_t origsize2 = wcslen(wch2) + 1;
		const size_t newsize2 = origsize2 * 2;
		size_t convertedChars2 = 0;
		char * pass = new char[newsize2];
		wcstombs_s(&convertedChars2, pass, newsize2, wch2, _TRUNCATE);
		wch2 = nullptr;
	
		//set the connect username in the socket
		zmq_setsockopt(socket, ZMQ_PLAIN_USERNAME, "stats", 6);
		zmq_setsockopt(socket, ZMQ_ZAP_DOMAIN, "stats", 6);
		//set the connect password in the socket
		zmq_setsockopt(socket, ZMQ_PLAIN_PASSWORD, pass, strlen(pass));
		delete pass;
		pass = nullptr;
	}

	zmq_connect(socket, server);

	zmq_setsockopt(socket, ZMQ_SUBSCRIBE, "", 0);

	while (true) {
		zmq_msg_t * serverMsg = new zmq_msg_t;
		zmq_msg_init(serverMsg);

		try {
			int size = zmq_recvmsg(socket, serverMsg, ZMQ_DONTWAIT);
			if (size == -1 || size == 0) {
				if (zmq_errno() == EAGAIN) {}
				else {}
				System::Threading::Thread::Sleep(TimeSpan(0, 0, 0, 0, 300));//wait 300 milliseconds
				continue;
			
			}

			char * buff = new char[size + 1];
			memcpy(buff, zmq_msg_data(serverMsg), size);

			zmq_msg_close(serverMsg);
			delete serverMsg;
			serverMsg = NULL;

			if (buff != NULL && size > 0) {
				count++;
				buff[size] = '\0';
				wchar_t * wstr = new wchar_t[size + 1];
				MultiByteToWideChar(CP_UTF8, 0, buff, -1, wstr, size + 1);
				String^ message = gcnew String(wstr);

				this->serverStatus->AppendText(message);

				delete buff;
				buff = NULL;
				delete[] wstr;
				wstr = NULL;
				delete message;
				message = nullptr;
			}
			else {
				delete buff;
				buff = NULL;
				delete serverMsg;
				serverMsg = NULL;
				continue;
			}
		}
		catch (...) {}
	}
	zmq_disconnect(socket, server);
	delete server;
	server = NULL;
	zmq_close(socket);
	socket = NULL;
	zmq_ctx_destroy(context);
	context = NULL;

}

//Initial formatting of the messages received by the zmq socket
System::String^ QuakeLiveRcon::Status::formatMessage(System::String^ message) {
	String^ temp = message->Replace("\\n", "");

	char c = 25;
	String^ d = gcnew String(&c);
	temp = temp->Replace(d, "");
	delete d;
	d = nullptr;

	char e = 19;
	String^ f = gcnew String(&e);
	temp = temp->Replace(f, "");
	delete f;
	f = nullptr;

	char g = (char)0x0d0a;
	String^ h = gcnew String(&g);
	temp = temp->Replace(h, "\n");
	delete h;
	h = nullptr;

	return temp;
}

//formats and prints the messages recieved from the server to the specified RichTextBox
void QuakeLiveRcon::Status::displayServerMessage(System::String^ text) {
	array<System::String^>^ textArray = text->Split('^');

	if (textArray->Length > 1) {
		int color;
		for (int i = 0; i < textArray->Length; i++) {
			System::String^ first = textArray[i];
			if (first->Length > 1)
				first = first->Substring(0, 1);
			if (!int::TryParse(first, color) || color < 0 || color > 8) { //if there is no number after the '^' or the number is les than 0 or greater than 8
				System::String^ newText;
				if (i == 0) {
					newText = textArray[i];
				}
				else {
					newText = "^" + textArray[i];
				}
				try {
					this->serverStatus->AppendText(newText);
				}
				catch (ObjectDisposedException^) {}
				catch (NullReferenceException^) {}
			}
			else { //If there is a number (0,8) after the '^' (meaning a color code)
				System::String^ newText = textArray[i]->Substring(1);
				try {
					this->serverStatus->AppendText(newText);
					this->serverStatus->Select(this->serverStatus->Text->Length - newText->Length, newText->Length);

					switch (color) {
					case 0:
						this->serverStatus->SelectionColor = ColorTranslator::FromHtml(this->info[4]); //Color::Black;
						break;
					case 1:
						this->serverStatus->SelectionColor = ColorTranslator::FromHtml(this->info[5]); //Color::Red;
						break;
					case 2:
						this->serverStatus->SelectionColor = ColorTranslator::FromHtml(this->info[6]); //Color::Green;
						break;
					case 3:
						this->serverStatus->SelectionColor = ColorTranslator::FromHtml(this->info[7]); //Color::Yellow;
						break;
					case 4:
						this->serverStatus->SelectionColor = ColorTranslator::FromHtml(this->info[8]); //Color::Blue;
						break;
					case 5:
						this->serverStatus->SelectionColor = ColorTranslator::FromHtml(this->info[9]); //Color::Cyan;
						break;
					case 6:
						this->serverStatus->SelectionColor = ColorTranslator::FromHtml(this->info[10]); //Color::Purple;
						break;
					case 7:
						this->serverStatus->SelectionColor = ColorTranslator::FromHtml(this->info[11]); //Color::White;
						break;
					case 8:
						this->serverStatus->SelectionColor = ColorTranslator::FromHtml(this->info[12]); //Color::Black;
						break;
					default:
						this->serverStatus->SelectionColor = ColorTranslator::FromHtml(this->info[11]); //Color::White;
						break;
					}
					this->serverStatus->Select(this->serverStatus->Text->Length, 0);
				}
				catch (ObjectDisposedException^) {}
				catch (NullReferenceException^) {}
			}
		}
	}
	else {
		try {
			this->serverStatus->AppendText(text);
		}
		catch (ObjectDisposedException^) {}
		catch (NullReferenceException^) {}
	}
	return;
}

