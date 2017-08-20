/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.5 on 8/20/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#include "ServersEdit.h"

///Constructors
QuakeLiveRcon::ServersEdit::ServersEdit() {
	InitializeComponent();
}
QuakeLiveRcon::ServersEdit::ServersEdit(const char *file) {
	InitializeComponent();

	this->ini = gcnew IniEditor(file);
	this->sections = gcnew List<String^>();
	this->serverNames = gcnew List<String^>();
	this->keys = gcnew List<String^>();
	this->fillComboBox();
	this->selectServer("Add New Server");
	this->alphabeticSort->Checked = this->ini->isTrue("main", "alphabetically");
}

///Destructor
QuakeLiveRcon::ServersEdit::~ServersEdit() {
	if (components)
	{
		delete components;
	}
	delete this->ini;
	delete this->sections;
	delete this->keys;
}

System::Void QuakeLiveRcon::ServersEdit::close_Click(System::Object^  sender, System::EventArgs^  e) {
	//this->ini->SaveFile(iniFile);
	this->Close();
}

//fill ServerList comboBox with the saved servers
void QuakeLiveRcon::ServersEdit::fillComboBox() {
	this->sections->Clear();
	this->serverNames->Clear();
	//get the alphabetical list display status
	bool sortAlphabetically = this->ini->isTrue("main", "alphabetically");

	List<String^>^ sectionsTemp = gcnew List<String^>();
	int count = 0;
	this->savedServers->Items->Clear();
	this->ini->getSectionNames(sectionsTemp);
	for each (String^ section in sectionsTemp) {
		//make suer that the section being read is a IP:PORT
		if (this->isServerIpPort(section)) {
			this->sections->Add(section);
			this->serverNames->Add(this->ini->getValue(section, "name"));
			count++;
		}
	}

	if (sortAlphabetically) {
		bool swap = true;
		int i;
		int j = 2;
		int length = this->serverNames->Count;
		String^ tempIpPort;
		String^ tempName;

		//Perform a bubble sort if alphabetically sort is selected
		while (swap) {
			swap = false;
			for (i = 0; i <= length - j; i++) {
				if (String::Compare(this->serverNames[i], this->serverNames[i + 1]) > 0) {
					tempName = this->serverNames[i + 1];
					this->serverNames[i + 1] = this->serverNames[i];
					this->serverNames[i] = tempName;
					tempIpPort = this->sections[i + 1];
					this->sections[i + 1] = this->sections[i];
					this->sections[i] = tempIpPort;
					swap = true;
				}
			}
			j++;
		}
		delete tempIpPort;
		tempIpPort = nullptr;
		delete tempName;
		tempName = nullptr;
	}

	for each (String^ server in this->serverNames) {
		this->savedServers->Items->Add(server);
	}

	this->savedServersLabel->Text = gcnew String(count + " Saved Servers");
	this->savedServers->Items->Add("Add New Server");

	delete sectionsTemp;
	sectionsTemp = nullptr;

	return;
}

System::Void QuakeLiveRcon::ServersEdit::alphabeticSort_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	//save the alphabetical sort check status
	this->ini->writeValue("main", "alphabetically", this->alphabeticSort->Checked);
	this->fillComboBox();
}

System::Void QuakeLiveRcon::ServersEdit::savedServers_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	int selectedIndex = this->savedServers->SelectedIndex;
	if (selectedIndex < this->savedServers->Items->Count - 1) {
		array<String^>^ sectionArray = this->sections[selectedIndex]->Split(':');
		this->ip->Text = sectionArray[0];
		this->port->Text = sectionArray[1];
		this->name->Text = gcnew String(this->ini->getValue(this->sections[selectedIndex], "name"));
		this->password->Text = gcnew String(this->ini->getValue(this->sections[selectedIndex], "password"));
		this->logRcon->Checked = this->ini->getBoolean(this->sections[selectedIndex], "log", false);
		delete sectionArray;
		sectionArray = nullptr;
	}
	else {
		this->connectOnStart->Checked = false;
		this->ip->Text = "";
		this->port->Text = "";
		this->name->Text = "";
		this->password->Text = "";
		this->logRcon->Checked = false;
	}
}

System::Void QuakeLiveRcon::ServersEdit::save_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->checkIpFormat(this->ip->Text)) {
		String^ section = gcnew String(this->ip->Text + ":" + this->port->Text);
		//save the connect on startup status
		this->ini->writeValue(section, "connect", this->connectOnStart->Checked);
		//save the server name
		this->ini->writeValue(section, "name", this->name->Text);
		//save the rcon password
		this->ini->writeValue(section, "password", this->password->Text);
		//save te connect on startup status
		this->ini->writeValue(section, "log", this->logRcon->Checked);
		//fill the combo box again
		this->fillComboBox();
		this->selectServer(this->name->Text);
	}
	else {
		MessageBox::Show("The IP address is invalid. Fix the IP Address in order to save the server information.",
			"Invalid IP Address", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
}

bool QuakeLiveRcon::ServersEdit::checkIpFormat(String^ ip) {
	int len = ip->Length;
	int dots = 0;
	bool ipCheck = true;

	for (int i = 0; i < len; i++) {
		if (!Char::IsDigit(ip[i]) && (i == 0 || i == len - 1 || dots == 3)) {
			ipCheck = false;
		}
		if (ip[i] == '.')
			dots++;
	}
	if (dots != 3)
		ipCheck = false;

	return ipCheck;
}

//Select a server in the combobox based on server name
void QuakeLiveRcon::ServersEdit::selectServer(String ^ name) {
	this->savedServers->SelectedIndex = this->savedServers->FindStringExact(name);
}

//Delete the selected server from the saved servers
System::Void QuakeLiveRcon::ServersEdit::deleteServer_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ section = gcnew String(this->ip->Text + ":" + this->port->Text);
	this->ini->deleteSection(section);
	this->fillComboBox();
	this->selectServer("Add New Server");
}

//do not allow spaces in the password textbox
System::Void QuakeLiveRcon::ServersEdit::password_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == ' ')
		e->Handled = true;
	//if (e->KeyChar == (char)Keys::Space) //should be the same as the above if check (no casting of (char) required above)
	//	e->Handled = true;
}

//do not allow spaces; only allow digits and dots and 15 chars max in tha ip textbox (allow backspace)
System::Void QuakeLiveRcon::ServersEdit::ip_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == 22)
		return;
	else if (e->KeyChar == ' ')
		e->Handled = true;
	else if (this->ip->Text->Length >= 15 && e->KeyChar != 0x08)
		e->Handled = true;
	else if (e->KeyChar == '.')
		return;
	else if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
		e->Handled = true;
}

System::Void QuakeLiveRcon::ServersEdit::ip_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->ip->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->ip->SelectedText->ToString());
		else if (e->KeyCode == Keys::X)
			this->ip->Cut();
}

//do not allow spaces; only allow digits and 6 chars max in the port textbox (allow backspace)
System::Void QuakeLiveRcon::ServersEdit::port_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == 22)
		return;
	else if (e->KeyChar == ' ')
		e->Handled = true;
	else if (this->port->Text->Length >= 6 && e->KeyChar != 0x08)
		e->Handled = true;
	else if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
		e->Handled = true;
}

System::Void QuakeLiveRcon::ServersEdit::port_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->port->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->port->SelectedText->ToString());
		else if (e->KeyCode == Keys::X)
			this->port->Cut();
}

//
bool QuakeLiveRcon::ServersEdit::isServerIpPort(String^ ipPort) {
	bool isIpPort = false;
	int convertToNum;
	array<String^>^ split1 = ipPort->Split(':');
	if (split1->Length == 2) {
		if (Int32::TryParse(split1[1], convertToNum) && split1[0]->CompareTo("127.0.0.1")
			&& split1[0]->CompareTo("0.0.0.0") && split1[0]->CompareTo("255.255.255.255")) {
			array<String^>^ split2 = split1[0]->Split('.');
			if (split2->Length == 4) {
				if (Int32::TryParse(split2[0], convertToNum) && convertToNum >= 0 && convertToNum <= 255)
					if (Int32::TryParse(split2[1], convertToNum) && convertToNum >= 0 && convertToNum <= 255)
						if (Int32::TryParse(split2[2], convertToNum) && convertToNum >= 0 && convertToNum <= 255)
							if (Int32::TryParse(split2[3], convertToNum) && convertToNum >= 0 && convertToNum <= 255)
								isIpPort = true;
			}
			delete split2;
			split2 = nullptr;
		}
	}
	delete split1;
	split1 = nullptr;
	return isIpPort;
}
