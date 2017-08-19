/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.4 on 8/18/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#include "QLRcon.h"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:main")

[STAThread]
int main(array<String^>^ args) {
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);

	QuakeLiveRcon::QLRcon gui;
	System::Windows::Forms::Application::Run(%gui);

	return 0;
}

///Contructor
QuakeLiveRcon::QLRcon::QLRcon(void) {
	InitializeComponent();

	//this->Text += " : Version " + this->ProductVersion;

	this->serverTabs = gcnew array<System::Windows::Forms::TabPage^>(MAX_SERVERS) {
		this->rcon0, this->rcon1, this->rcon2, this->rcon3, this->rcon4, this->rcon5,
			this->rcon6, this->rcon7, this->rcon8, this->rcon9, this->rcon10, this->rcon11,
			this->rcon12, this->rcon13, this->rcon14, this->rcon15, this->rcon16, this->rcon17,
			this->rcon18, this->rcon19
	};

	this->outBox = gcnew array<System::Windows::Forms::RichTextBox^>(MAX_SERVERS) {
		this->output0, this->output1, this->output2, this->output3, this->output4, this->output5,
			this->output6, this->output7, this->output8, this->output9, this->output10, this->output11,
			this->output12, this->output13, this->output14, this->output15, this->output16, this->output17,
			this->output18, this->output19
	};

	this->inBox = gcnew array<System::Windows::Forms::TextBox^>(MAX_SERVERS) {
		this->input0, this->input1, this->input2, this->input3, this->input4, this->input5,
			this->input6, this->input7, this->input8, this->input9, this->input10, this->input11,
			this->input12, this->input13, this->input14, this->input15, this->input16, this->input17,
			this->input18, this->input19
	};

	this->eventKeys = gcnew array<int>(EVENT_ARRAY_SIZE) {
		ZMQ_EVENT_ACCEPTED, ZMQ_EVENT_ACCEPT_FAILED, ZMQ_EVENT_BIND_FAILED, ZMQ_EVENT_CLOSED, ZMQ_EVENT_CLOSE_FAILED,
			ZMQ_EVENT_CONNECTED, ZMQ_EVENT_CONNECT_DELAYED, ZMQ_EVENT_CONNECT_RETRIED, ZMQ_EVENT_DISCONNECTED,
			ZMQ_EVENT_LISTENING, ZMQ_EVENT_MONITOR_STOPPED
	};
	this->eventNames = gcnew array<String^>(EVENT_ARRAY_SIZE) {
		L"EVENT_ACCEPTED", L"EVENT_ACCEPT_FAILED", L"EVENT_BIND_FAILED", L"EVENT_CLOSED", L"EVENT_CLOSE_FAILED",
			L"EVENT_CONNECTED", L"EVENT_CONNECT_DELAYED", L"EVENT_CONNECT_RETRIED", L"EVENT_DISCONNECTED",
			L"EVENT_LISTENING", L"EVENT_MONITOR_STOPPED"
	};

	this->tabs = gcnew array<int>(MAX_SERVERS);
	for (int i = 0; i < MAX_SERVERS; i++) {
		this->tabs[i] = 0;
	}

	this->tabLocation = gcnew array<int>(MAX_SERVERS);
	this->commandEntries = gcnew array<int>(MAX_SERVERS);
	this->connectedServers = gcnew array<String^>(MAX_SERVERS);
	this->serverNames = gcnew array<String^>(MAX_SERVERS);
	this->logServer = gcnew array<bool>(MAX_SERVERS);
	this->ini = gcnew IniEditor(gcnew String(iniFile));
	this->savedServers = gcnew List<String^>();
	this->keys = gcnew List<String^>();
	this->logServerWriter = gcnew array<LogFileWriter^>(MAX_SERVERS);
	this->serverConnectionThread = gcnew array<Thread^>(MAX_SERVERS);
	this->statsConnectionThread = gcnew array<Thread^>(MAX_SERVERS);

	this->commands = gcnew array<String^, 2>(MAX_SERVERS, STORED_COMMANDS);
	for (int i = 0; i < MAX_SERVERS; i++) {
		for (int j = 0; j < STORED_COMMANDS; j++) {
			this->commands[i, j] = "";
		}
	}

	this->sendCommands = gcnew array<String^, 2>(MAX_SERVERS, STORED_COMMANDS);
	for (int i = 0; i < MAX_SERVERS; i++) {
		for (int j = 0; j < STORED_COMMANDS; j++) {
			this->sendCommands[i, j] = "";
		}
	}

	this->command = gcnew array<char*>(MAX_SERVERS);
	for (int i = 0; i < MAX_SERVERS; i++) {
		this->command[i] = nullptr;
	}

	this->settingsArray = gcnew array<String^>(SETTINGS_ARRAY_SIZE);
	for (int i = 0; i < SETTINGS_ARRAY_SIZE; i++) {
		this->settingsArray[i] = "";
	}

	this->rconBooleans = gcnew array<bool>(RCON_BOOLEANS);
	for (int i = 0; i < RCON_BOOLEANS; i++) {
		this->rconBooleans[i] = false;
	}

	this->disconnect = gcnew array<bool>(MAX_SERVERS);
	for (int i = 0; i < MAX_SERVERS; i++) {
		this->disconnect[i] = false;
	}

	this->buildDisplayLines = gcnew array<List<String^>^>(MAX_SERVERS);
	for (int i = 0; i < MAX_SERVERS; i++) {
		this->buildDisplayLines[i] = gcnew List<String^>();
	}

	this->buildLines = gcnew array<List<String^>^>(MAX_SERVERS);
	for (int i = 0; i < MAX_SERVERS; i++) {
		this->buildLines[i] = gcnew List<String^>();
	}

	this->statsConnectInfo = gcnew array<String^, 2>(MAX_SERVERS, 2);
	for (int i = 0; i < MAX_SERVERS; i++) {
		for (int j = 0; j < 2; j++) {
			this->statsConnectInfo[i, j] = "";
		}
	}

	this->colorIndex = gcnew array<Dictionary<Int32, Int32>^>(MAX_SERVERS);
	for (int i = 0; i < MAX_SERVERS; i++) {
		this->colorIndex[i] = gcnew Dictionary<Int32, Int32>();
	}
	this->colorLength = gcnew array<Dictionary<Int32, Int32>^>(MAX_SERVERS);
	for (int i = 0; i < MAX_SERVERS; i++) {
		this->colorLength[i] = gcnew Dictionary<Int32, Int32>();
	}
	this->foundColor = gcnew array<bool>(MAX_SERVERS);
	for (int i = 0; i < RCON_BOOLEANS; i++) {
		this->foundColor[i] = false;
	}
	this->conversion = gcnew array<bool>(MAX_SERVERS);
	for (int i = 0; i < RCON_BOOLEANS; i++) {
		this->conversion[i] = false;
	}

	this->color = gcnew array<int>(MAX_SERVERS);
	//for (int i = 0; i < MAX_SERVERS; i++) {
	//	this->color[i] = NULL;
	//}
	this->pos = gcnew array<int>(MAX_SERVERS);
	//for (int i = 0; i < MAX_SERVERS; i++) {
	//	this->pos[i] = NULL;
	//}
	this->nextPos = gcnew array<int>(MAX_SERVERS);
	//for (int i = 0; i < MAX_SERVERS; i++) {
	//	this->nextPos[i] = NULL;
	//}
	this->nextColor = gcnew array<int>(MAX_SERVERS);
	//for (int i = 0; i < MAX_SERVERS; i++) {
	//	this->nextColor[i] = NULL;
	//}
	//array<QuakeLiveRcon::QLRcon::ObjectArgReturningVoidDelegate^>^ callAgain;
	this->callAgain = gcnew array<QuakeLiveRcon::QLRcon::ObjectArgReturningVoidDelegate^>(MAX_SERVERS);
	this->msgAgain = gcnew array<QuakeLiveRcon::QLRcon::MessageArgReturningVoidDelegate^>(MAX_SERVERS);


	this->maxLines = MAX_TEXTBOX_LINES;
	this->linesRemove = LINES_TO_DELETE;

	this->outputRClick = gcnew System::Windows::Forms::ContextMenuStrip();
	this->rClickItem1 = gcnew ToolStripMenuItem(L"Copy");
	this->rClickItem2 = gcnew ToolStripMenuItem(L"Open Log File");
	this->rClickItem3 = gcnew ToolStripMenuItem(L"Open Log File Folder");
	this->rClickItem4 = gcnew ToolStripMenuItem(L"Disconnect/Reconnect");
	this->rClickItem5 = gcnew ToolStripMenuItem(L"Close Tab");
	this->rClickItem6 = gcnew ToolStripMenuItem(L"Commands");
	//this->rClickItem7 = gcnew ToolStripMenuItem(L"View Game Stats");
	this->outputRClick->Items->Add(this->rClickItem1);
	this->outputRClick->Items->Add(this->rClickItem2);
	this->outputRClick->Items->Add(this->rClickItem3);
	this->outputRClick->Items->Add(this->rClickItem4);
	this->outputRClick->Items->Add(this->rClickItem5);
	this->outputRClick->Items->Add(this->rClickItem6);
	//this->outputRClick->Items->Add(this->rClickItem7);
	this->rClickItem1->Click += gcnew EventHandler(this, &QLRcon::rClickItem1_MouseDown);
	this->rClickItem2->Click += gcnew EventHandler(this, &QLRcon::rClickItem2_MouseDown);
	this->rClickItem3->Click += gcnew EventHandler(this, &QLRcon::rClickItem3_MouseDown);
	this->rClickItem4->Click += gcnew EventHandler(this, &QLRcon::rClickItem4_MouseDown);
	this->rClickItem5->Click += gcnew EventHandler(this, &QLRcon::rClickItem5_MouseDown);
	this->rClickItem6->Click += gcnew EventHandler(this, &QLRcon::rClickItem6_MouseDown);
	//this->rClickItem7->Click += gcnew EventHandler(this, &QLRcon::rClickItem7_MouseDown);
	this->rClickTab = -1;

	this->generateUUID();

	//load the settings into the settingsArray
	this->loadSettings();

	this->checkForOldFiles();

	this->currentInstance = this;
}

///Destructor
QuakeLiveRcon::QLRcon::~QLRcon() {
	//Sets the system sleep settings back to default
	if (this->rconBooleans[4]) {
		SetThreadExecutionState(ES_CONTINUOUS);
	}

	if (components)
	{
		delete components;
	}

	//for (int i = 0; i < MAX_SERVERS; i++) {
	//	if (this->tabs[i] == 1) {
	//		bool wait = this->closeOut();
	//		break;
	//	}
	//	if (this->logServer[i]) {
	//		bool wait = this->closeOut();
	//		break;
	//	}
	//}

	delete this->tabs;
	delete this->tabLocation;
	delete this->commandEntries;
	delete this->ini;
	delete this->savedServers;
	delete this->keys;
	delete this->activeTab;
	delete this->commands;
	delete this->sendCommands;
	delete this->settingsArray;

	///delete this->connectedServers;
	///delete this->serverNames;
	///delete this->logServer;
	///delete this->eventKeys;
	///delete this->eventNames;
	///delete this->disconnect;
	//delete this->serverTabs;
	//delete this->outBox;
	//delete this->inBox;
	//delete this->buildLines;
	//delete this->logServerWriter;
	///delete this->serverConnectionThread;
	///delete this->gamePort;
	///delete this->GamePortThread;
	//delete this->outputRClick;
	//delete this->rClickItem1;
	//delete this->rClickItem2;
	//delete this->rClickItem3;
	//delete this->rClickItem4;
	//delete this->rClickItem5;
	//delete this->rClickItem6;
}

///Form User Interface Functions
System::Void QuakeLiveRcon::QLRcon::Window_Load(System::Object^  sender, System::EventArgs^  e) {
	this->loadServersToComboBox();
}

System::Void QuakeLiveRcon::QLRcon::Window_Shown(System::Object^  sender, System::EventArgs^  e) {
	this->autoConectServers();
}

System::Void QuakeLiveRcon::QLRcon::rconTabs_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ tabName = "{" + this->rconTabs->SelectedTab->Name + "}";
	if (String::Compare(tabName, this->activeTab)) {
		this->activeTab = tabName;
		int tab = this->getRconTabNumber(this->activeTab);
		this->updateServerTabInfo(tab);
		//MessageBox::Show(activeTab, "Tab", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		//Scroll to the bottom of the output (window is ~34 lines)
		int currentLine = (int)SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_GETFIRSTVISIBLELINE, 0, 0);
		int lineCount = (int)SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_GETLINECOUNT, 0, 0);
		SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_LINESCROLL, 0, lineCount - currentLine - 34);
	}
	delete tabName;
	tabName = nullptr;
}

System::Void QuakeLiveRcon::QLRcon::exit_Click(System::Object^  sender, System::EventArgs^  e) {
	bool wait = this->closeOut();
	this->Close();
}

bool QuakeLiveRcon::QLRcon::closeOut() {
	for (int i = 0; i < MAX_SERVERS; i++)
		if (this->tabs[i] == 1)
			this->exitConnection(i);

	bool allOff = false;
	bool allLogged = false;

	while (!allOff || !allLogged) {
		allOff = true;
		allLogged = true;
		for (int i = 0; i < MAX_SERVERS; i++) {
			if (this->tabs[i] == 1)
				allOff = false;
			if (this->logServer[i])
				allLogged = false;
		}
	}
	return (allOff && allLogged);
}

System::Void QuakeLiveRcon::QLRcon::settings_Click(System::Object^  sender, System::EventArgs^  e) {
	//Creates the instance of the edit servers Form
	Settings ^ settingsEdit = gcnew Settings(iniFile, this->ProductVersion);
	//Creates an event handler for when the edit servers Form is closed
	FormClosedEventHandler ^ settingsHandler = gcnew FormClosedEventHandler(this, &QLRcon::OnSettingsFormClosed);
	//Registers the event handler with the new edit servers Form (must hapen before showing the form)
	settingsEdit->FormClosed += settingsHandler;
	//Shows the edit servers Form
	settingsEdit->ShowDialog();
}

void QuakeLiveRcon::QLRcon::OnSettingsFormClosed(Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
	this->loadSettings();
}

System::Void QuakeLiveRcon::QLRcon::editServers_Click(System::Object^  sender, System::EventArgs^  e) {
	//Creates the instance of the edit servers Form
	ServersEdit^ serversEdit = gcnew ServersEdit(iniFile);
	//Creates an event handler for when the edit servers Form is closed
	FormClosedEventHandler^ serversHandler = gcnew FormClosedEventHandler(this, &QLRcon::OnEditServersFormClosed);
	//Registers the event handler with the new edit servers Form (must hapen before showing the form)
	serversEdit->FormClosed += serversHandler;
	//Shows the edit servers Form
	serversEdit->ShowDialog();
}

void QuakeLiveRcon::QLRcon::OnEditServersFormClosed(Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
	this->loadServersToComboBox();
}

void QuakeLiveRcon::QLRcon::OnStatusFormClosed(Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
	//this->GameStatsThread->Abort();
	delete this->GameStatsThread;
	this->GameStatsThread = nullptr;
	//here;
}

void QuakeLiveRcon::QLRcon::loadSettings() {
	//get the status command on connect status
	this->settingsArray[0] = this->ini->getValue("main", "sendStatus");
	//get the command 1 enable status
	this->settingsArray[1] = this->ini->getValue("main", "command1:enabled");
	//get the command 1 button label
	this->settingsArray[2] = this->ini->getValue("main", "command1:label");
	//get the command 1 button command
	this->settingsArray[3] = this->ini->getValue("main", "command1:command");
	//get the command 2 enable status
	this->settingsArray[4] = this->ini->getValue("main", "command2:enabled");
	//get the command 2 button label	  
	this->settingsArray[5] = this->ini->getValue("main", "command2:label");
	//get the command 2 button command	  
	this->settingsArray[6] = this->ini->getValue("main", "command2:command");
	//get the command 3 enable status
	this->settingsArray[7] = this->ini->getValue("main", "command3:enabled");
	//get the command 3 button label	  
	this->settingsArray[8] = this->ini->getValue("main", "command3:label");
	//get the command 3 button command	  
	this->settingsArray[9] = this->ini->getValue("main", "command3:command");
	//get the command 4 enable status
	this->settingsArray[10] = this->ini->getValue("main", "command4:enabled");
	//get the command 4 button label	  
	this->settingsArray[11] = this->ini->getValue("main", "command4:label");
	//get the command 4 button command	  
	this->settingsArray[12] = this->ini->getValue("main", "command4:command");
	//get the command 5 enable status
	this->settingsArray[13] = this->ini->getValue("main", "command5:enabled");
	//get the command 5 button label	  
	this->settingsArray[14] = this->ini->getValue("main", "command5:label");
	//get the command 5 button command	  
	this->settingsArray[15] = this->ini->getValue("main", "command5:command");
	//get the command 6 enable status
	this->settingsArray[16] = this->ini->getValue("main", "command6:enabled");
	//get the command 6 button label	  
	this->settingsArray[17] = this->ini->getValue("main", "command6:label");
	//get the command 6 button command	  
	this->settingsArray[18] = this->ini->getValue("main", "command6:command");
	//get the connect to game server button enable status
	this->settingsArray[19] = this->ini->getValue("main", "connectToGame:enabled");
	//get the strip colors for log file enable status
	this->settingsArray[20] = this->ini->getValue("main", "stripLogColors:enabled");
	//get the auto scroll disable status
	this->settingsArray[21] = this->ini->getValue("main", "scroll:disabled");
	//get the max lines displayed value
	this->settingsArray[22] = this->ini->getValue("main", "maxLines");
	//get the lines to delete value
	this->settingsArray[23] = this->ini->getValue("main", "removeLines");
	//get the logging enabled value
	this->settingsArray[24] = (this->ini->getBoolean("main", "logging:enabled", true) ? L"true" : L"false");

	if (!System::String::Compare(this->settingsArray[20], "true") || !System::String::Compare(this->settingsArray[20], "True")
		|| !System::String::Compare(this->settingsArray[20], "TRUE"))
		this->rconBooleans[1] = true;
	else
		this->rconBooleans[1] = false;

	if (!System::String::Compare(this->settingsArray[21], "true") || !System::String::Compare(this->settingsArray[21], "True")
		|| !System::String::Compare(this->settingsArray[21], "TRUE"))
		this->rconBooleans[2] = true;
	else
		this->rconBooleans[2] = false;

	if (String::Compare("", this->settingsArray[22]))
		this->maxLines = System::Convert::ToInt32(this->settingsArray[22]->Replace(",", ""));
	else
		this->maxLines = MAX_TEXTBOX_LINES;

	if (String::Compare("", this->settingsArray[23]))
		this->linesRemove = System::Convert::ToInt32(this->settingsArray[23]->Replace(",", ""));
	else
		this->linesRemove = LINES_TO_DELETE;

	if (!System::String::Compare(this->settingsArray[24], "true") || !System::String::Compare(this->settingsArray[24], "True")
		|| !System::String::Compare(this->settingsArray[24], "TRUE"))
		this->rconBooleans[0] = true;
	else
		this->rconBooleans[0] = false;

	//get color 0 (Black)
	this->settingsArray[25] = this->ini->getValue("main", "color0", "#73879B");
	//get color 1 (Red)	
	this->settingsArray[26] = this->ini->getValue("main", "color1", "#FF0000");
	//get color 2 (Green)	
	this->settingsArray[27] = this->ini->getValue("main", "color2", "#00FF00");
	//get color 3 (Yellow)	
	this->settingsArray[28] = this->ini->getValue("main", "color3", "#FFFF00");
	//get color 4 (Blue)	
	this->settingsArray[29] = this->ini->getValue("main", "color4", "#306EFF");
	//get color 5 (Cyan)	
	this->settingsArray[30] = this->ini->getValue("main", "color5", "#53DCCD");
	//get color 6 (Purple)	
	this->settingsArray[31] = this->ini->getValue("main", "color6", "#B041FF");
	//get color 7 (White)	
	this->settingsArray[32] = this->ini->getValue("main", "color7", "#FFFFFF");
	//get color 8 (Black)	
	this->settingsArray[33] = this->ini->getValue("main", "color8", "#73879B");

	//get the keep alive status
	this->settingsArray[34] = (this->ini->getBoolean("main", "keepAlive", true) ? L"true" : L"false");
	if (!System::String::Compare(this->settingsArray[34], "true") || !System::String::Compare(this->settingsArray[34], "True")
		|| !System::String::Compare(this->settingsArray[34], "TRUE"))
		this->rconBooleans[3] = true;
	else
		this->rconBooleans[3] = false;

	//get the gameEvents:enabled status
	this->settingsArray[35] = (this->ini->getBoolean("main", "gameEvents:enabled", true) ? L"true" : L"false");
	if (!System::String::Compare(this->settingsArray[35], "true") || !System::String::Compare(this->settingsArray[35], "True")
		|| !System::String::Compare(this->settingsArray[35], "TRUE"))
		this->rconBooleans[5] = true;
	else
		this->rconBooleans[5] = false;
	//get the killMessages:enabled status
	this->settingsArray[36] = (this->ini->getBoolean("main", "killMessages:enabled", true) ? L"true" : L"false");
	if (!System::String::Compare(this->settingsArray[36], "true") || !System::String::Compare(this->settingsArray[36], "True")
		|| !System::String::Compare(this->settingsArray[36], "TRUE"))
		this->rconBooleans[6] = true;
	else
		this->rconBooleans[6] = false;
	//get the teamSwitch:enabled status
	this->settingsArray[37] = (this->ini->getBoolean("main", "teamSwitch:enabled", true) ? L"true" : L"false");
	if (!System::String::Compare(this->settingsArray[37], "true") || !System::String::Compare(this->settingsArray[37], "True")
		|| !System::String::Compare(this->settingsArray[37], "TRUE"))
		this->rconBooleans[7] = true;
	else
		this->rconBooleans[7] = false;
	//get the warmUp:enabled status
	this->settingsArray[38] = (this->ini->getBoolean("main", "warmUp:enabled", true) ? L"true" : L"false");
	if (!System::String::Compare(this->settingsArray[38], "true") || !System::String::Compare(this->settingsArray[38], "True")
		|| !System::String::Compare(this->settingsArray[38], "TRUE"))
		this->rconBooleans[8] = true;
	else
		this->rconBooleans[8] = false;
	//get the playerMedals:enabled status
	this->settingsArray[39] = (this->ini->getBoolean("main", "playerMedals:enabled", true) ? L"true" : L"false");
	if (!System::String::Compare(this->settingsArray[39], "true") || !System::String::Compare(this->settingsArray[39], "True")
		|| !System::String::Compare(this->settingsArray[39], "TRUE"))
		this->rconBooleans[9] = true;
	else
		this->rconBooleans[9] = false;

	//get the timeStamp:enabled status
	this->settingsArray[40] = (this->ini->getBoolean("main", "timeStamp:enabled", false) ? L"true" : L"false");
	if (!System::String::Compare(this->settingsArray[40], "true") || !System::String::Compare(this->settingsArray[40], "True")
		|| !System::String::Compare(this->settingsArray[40], "TRUE"))
		this->rconBooleans[10] = true;
	else
		this->rconBooleans[10] = false;
	//get the timeStampFormat value
	String^ format = this->ini->getValue("main", "timeStampFormat", "11:45:30 AM");
	if (format->Equals("Friday, August 4, 2017 11:45 AM"))
		this->settingsArray[41] = "f";
	else if (format->Equals("Friday, August 4, 2017 11:45:30 AM"))
		this->settingsArray[41] = "F";
	else if (format->Equals("8/4/2017 11:45 AM"))
		this->settingsArray[41] = "g";
	else if (format->Equals("8/4/2017 11:45:30 AM"))
		this->settingsArray[41] = "G";
	else if (format->Equals("11:45 AM"))
		this->settingsArray[41] = "t";
	else if (format->Equals("11:45:30 AM"))
		this->settingsArray[41] = "T";
	else
		this->settingsArray[41] = "T";

	//get chatColor (Green)	
	this->settingsArray[42] = this->ini->getValue("main", "chatColor", "2");
	//get teamColor (Cyan)	
	this->settingsArray[43] = this->ini->getValue("main", "teamColor", "5");


	this->viewServerTabButtons();
}

void QuakeLiveRcon::QLRcon::input0_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[0] != 1 && this->tabs[0] == 1) {
		this->commandEntries[0] = 1;
		this->input0->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input0_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input0->Text->Length > 0)
			this->addComandEntry(0, this->input0->Text);
		this->input0->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input0_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input0->Text = this->getCommandEntry(0, this->input0->Text, "up");
		this->input0->Select(this->input0->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input0->Text = this->getCommandEntry(0, this->input0->Text, "down");
		this->input0->Select(this->input0->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input1_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[1] != 1 && this->tabs[1] == 1) {
		this->commandEntries[1] = 1;
		this->input1->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input1->Text->Length > 0)
			this->addComandEntry(1, this->input1->Text);
		this->input1->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input1->Text = this->getCommandEntry(1, this->input1->Text, "up");
		this->input1->Select(this->input1->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input1->Text = this->getCommandEntry(1, this->input1->Text, "down");
		this->input1->Select(this->input1->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input2_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[2] != 1 && this->tabs[2] == 1) {
		this->commandEntries[2] = 1;
		this->input2->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input2_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input2->Text->Length > 0)
			this->addComandEntry(2, this->input2->Text);
		this->input2->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input2_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input2->Text = this->getCommandEntry(2, this->input2->Text, "up");
		this->input2->Select(this->input2->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input2->Text = this->getCommandEntry(2, this->input2->Text, "down");
		this->input2->Select(this->input2->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input3_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[3] != 1 && this->tabs[3] == 1) {
		this->commandEntries[3] = 1;
		this->input3->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input3_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input3->Text->Length > 0)
			this->addComandEntry(3, this->input3->Text);
		this->input3->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input3_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input3->Text = this->getCommandEntry(3, this->input3->Text, "up");
		this->input3->Select(this->input3->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input3->Text = this->getCommandEntry(3, this->input3->Text, "down");
		this->input3->Select(this->input3->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input4_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[4] != 1 && this->tabs[4] == 1) {
		this->commandEntries[4] = 1;
		this->input4->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input4_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input4->Text->Length > 0)
			this->addComandEntry(4, this->input4->Text);
		this->input4->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input4_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input4->Text = this->getCommandEntry(4, this->input4->Text, "up");
		this->input4->Select(this->input4->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input4->Text = this->getCommandEntry(4, this->input4->Text, "down");
		this->input4->Select(this->input4->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input5_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[5] != 1 && this->tabs[5] == 1) {
		this->commandEntries[5] = 1;
		this->input5->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input5_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input5->Text->Length > 0)
			this->addComandEntry(5, this->input5->Text);
		this->input5->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input5_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input5->Text = this->getCommandEntry(5, this->input5->Text, "up");
		this->input5->Select(this->input5->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input5->Text = this->getCommandEntry(5, this->input5->Text, "down");
		this->input5->Select(this->input5->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input6_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[6] != 1 && this->tabs[6] == 1) {
		this->commandEntries[6] = 1;
		this->input6->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input6_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input6->Text->Length > 0)
			this->addComandEntry(6, this->input6->Text);
		this->input6->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input6_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input6->Text = this->getCommandEntry(6, this->input6->Text, "up");
		this->input6->Select(this->input6->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input6->Text = this->getCommandEntry(6, this->input6->Text, "down");
		this->input6->Select(this->input6->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input7_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[7] != 1 && this->tabs[7] == 1) {
		this->commandEntries[7] = 1;
		this->input7->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input7_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input7->Text->Length > 0)
			this->addComandEntry(7, this->input7->Text);
		this->input7->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input7_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input7->Text = this->getCommandEntry(7, this->input7->Text, "up");
		this->input7->Select(this->input7->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input7->Text = this->getCommandEntry(7, this->input7->Text, "down");
		this->input7->Select(this->input7->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input8_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[8] != 1 && this->tabs[8] == 1) {
		this->commandEntries[8] = 1;
		this->input8->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input8_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input8->Text->Length > 0)
			this->addComandEntry(8, this->input8->Text);
		this->input8->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input8_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input8->Text = this->getCommandEntry(8, this->input8->Text, "up");
		this->input8->Select(this->input8->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input8->Text = this->getCommandEntry(8, this->input8->Text, "down");
		this->input8->Select(this->input8->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input9_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[9] != 1 && this->tabs[9] == 1) {
		this->commandEntries[9] = 1;
		this->input9->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input9_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input9->Text->Length > 0)
			this->addComandEntry(9, this->input9->Text);
		this->input9->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input9_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input9->Text = this->getCommandEntry(9, this->input9->Text, "up");
		this->input9->Select(this->input9->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input9->Text = this->getCommandEntry(9, this->input9->Text, "down");
		this->input9->Select(this->input9->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input10_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[10] != 1 && this->tabs[10] == 1) {
		this->commandEntries[10] = 1;
		this->input10->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input10_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input10->Text->Length > 0)
			this->addComandEntry(10, this->input10->Text);
		this->input10->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input10_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input10->Text = this->getCommandEntry(10, this->input10->Text, "up");
		this->input10->Select(this->input10->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input10->Text = this->getCommandEntry(10, this->input10->Text, "down");
		this->input10->Select(this->input10->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input11_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[11] != 1 && this->tabs[11] == 1) {
		this->commandEntries[11] = 1;
		this->input11->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input11_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input11->Text->Length > 0)
			this->addComandEntry(11, this->input11->Text);
		this->input11->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input11_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input11->Text = this->getCommandEntry(11, this->input11->Text, "up");
		this->input11->Select(this->input11->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input11->Text = this->getCommandEntry(11, this->input11->Text, "down");
		this->input11->Select(this->input11->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input12_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[12] != 1 && this->tabs[12] == 1) {
		this->commandEntries[12] = 1;
		this->input12->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input12_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input12->Text->Length > 0)
			this->addComandEntry(12, this->input12->Text);
		this->input12->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input12_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input12->Text = this->getCommandEntry(12, this->input12->Text, "up");
		this->input12->Select(this->input12->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input12->Text = this->getCommandEntry(12, this->input12->Text, "down");
		this->input12->Select(this->input12->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input13_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[13] != 1 && this->tabs[13] == 1) {
		this->commandEntries[13] = 1;
		this->input13->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input13_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input13->Text->Length > 0)
			this->addComandEntry(13, this->input13->Text);
		this->input13->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input13_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input13->Text = this->getCommandEntry(13, this->input13->Text, "up");
		this->input13->Select(this->input13->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input13->Text = this->getCommandEntry(13, this->input13->Text, "down");
		this->input13->Select(this->input13->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input14_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[14] != 1 && this->tabs[14] == 1) {
		this->commandEntries[14] = 1;
		this->input14->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input14_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input14->Text->Length > 0)
			this->addComandEntry(14, this->input14->Text);
		this->input14->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input14_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input14->Text = this->getCommandEntry(14, this->input14->Text, "up");
		this->input14->Select(this->input14->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input14->Text = this->getCommandEntry(14, this->input14->Text, "down");
		this->input14->Select(this->input14->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input15_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[15] != 1 && this->tabs[15] == 1) {
		this->commandEntries[15] = 1;
		this->input15->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input15_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input15->Text->Length > 0)
			this->addComandEntry(15, this->input15->Text);
		this->input15->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input15_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input15->Text = this->getCommandEntry(15, this->input15->Text, "up");
		this->input15->Select(this->input15->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input15->Text = this->getCommandEntry(15, this->input15->Text, "down");
		this->input15->Select(this->input15->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input16_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[16] != 1 && this->tabs[16] == 1) {
		this->commandEntries[16] = 1;
		this->input16->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input16_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input16->Text->Length > 0)
			this->addComandEntry(16, this->input16->Text);
		this->input16->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input16_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input16->Text = this->getCommandEntry(16, this->input16->Text, "up");
		this->input16->Select(this->input16->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input16->Text = this->getCommandEntry(16, this->input16->Text, "down");
		this->input16->Select(this->input16->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input17_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[17] != 1 && this->tabs[17] == 1) {
		this->commandEntries[17] = 1;
		this->input17->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input17_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input17->Text->Length > 0)
			this->addComandEntry(17, this->input17->Text);
		this->input17->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input17_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input17->Text = this->getCommandEntry(17, this->input17->Text, "up");
		this->input17->Select(this->input17->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input17->Text = this->getCommandEntry(17, this->input17->Text, "down");
		this->input17->Select(this->input17->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input18_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[18] != 1 && this->tabs[18] == 1) {
		this->commandEntries[18] = 1;
		this->input18->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input18_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input18->Text->Length > 0)
			this->addComandEntry(18, this->input18->Text);
		this->input18->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input18_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input18->Text = this->getCommandEntry(18, this->input18->Text, "up");
		this->input18->Select(this->input18->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input18->Text = this->getCommandEntry(18, this->input18->Text, "down");
		this->input18->Select(this->input18->Text->Length, 0);
	}
}

void QuakeLiveRcon::QLRcon::input19_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->commandEntries[19] != 1 && this->tabs[19] == 1) {
		this->commandEntries[19] = 1;
		this->input19->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input19_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->input19->Text->Length > 0)
			this->addComandEntry(19, this->input19->Text);
		this->input19->Text = "";
	}
}
System::Void QuakeLiveRcon::QLRcon::input19_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Up) {
		e->Handled = true;
		this->input19->Text = this->getCommandEntry(19, this->input19->Text, "up");
		this->input19->Select(this->input19->Text->Length, 0);
	}
	else if (e->KeyCode == Keys::Down) {
		e->Handled = true;
		this->input19->Text = this->getCommandEntry(19, this->input19->Text, "down");
		this->input19->Select(this->input19->Text->Length, 0);
	}
}

System::Void QuakeLiveRcon::QLRcon::connect_Click(System::Object^  sender, System::EventArgs^  e) {
	if (!String::Compare(this->serverList->Text, "")) //don't execute anything if a server is not selected
		return;

	if (!this->rconTabs->TabCount) {
		this->Controls->Add(this->rconTabs);
		this->Controls->Remove(this->notConnectedMessage);
		//sets the system so it will not go to sleep while the program is running (allows the monitor to turn off)
		if (this->rconBooleans[3]) {
			this->rconBooleans[4] = true;
			SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);
		}
	}

	int selectedIndex = this->serverList->SelectedIndex;
	String^ ipPort = this->savedServers[selectedIndex];

	for (int i = 0; i < MAX_SERVERS; i++) {
		if (this->tabs[i]) {
			String^ serverIpPort = this->connectedServers[i];

			if (!String::Compare(ipPort, serverIpPort)) {
				//MessageBox::Show(System::Convert::ToString(this->tabLocation[i]), "Tab", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				this->rconTabs->SelectedIndex = this->tabLocation[i];
				this->serverName->Text = this->serverNames[i];
				this->IPLabel->Text = ipPort;
				if (this->tabs[i] == -1) {
					this->logServer[i] = this->ini->isTrue(ipPort, "log");
					this->tabs[i] = 1;
					this->disconnect[i] = false;
					this->serverConnection(i, L"connect");
					this->updateServerTabInfo(i);
				}
				return;
			}
			delete serverIpPort;
			serverIpPort = nullptr;
		}
	}

	int firstFree = -1;
	for (int i = 0; i < MAX_SERVERS; i++) {
		if (this->tabs[i] == 0) {
			firstFree = i;
			break;
		}
	}

	if (firstFree >= 0 && firstFree < MAX_SERVERS) {
		this->tabLocation[firstFree] = this->rconTabs->TabCount;
		this->tabs[firstFree] = 1;
		this->disconnect[firstFree] = false;
		this->connectedServers[firstFree] = ipPort;
		this->serverNames[firstFree] = this->ini->getValue(ipPort, "name");
		this->logServer[firstFree] = this->ini->isTrue(ipPort, "log");
		this->addTab(firstFree);
		this->updateServerTabInfo(firstFree);
		this->activeTab = "{rcon" + firstFree + "}";
		this->rconTabs->SelectedIndex = this->tabLocation[firstFree];
		//connect to the server
		this->serverConnection(firstFree, L"connect");
	}
	else {
		MessageBox::Show("All available connections are in use.Close a server tab to be able to connect to another server.",
			"No Available Connection Tabs", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
	//MessageBox::Show("End", "End", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);

	this->viewServerTabButtons();
	delete ipPort;
	ipPort = nullptr;
	return;
}

System::Void QuakeLiveRcon::QLRcon::disconnectTab_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->rconTabs->TabCount) {
		int tab = this->getRconTabNumber(this->activeTab);
		this->serverTabConnection(tab);
	}
}

System::Void QuakeLiveRcon::QLRcon::closeTab_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->rconTabs->TabCount) {
		int tab = this->getRconTabNumber(this->activeTab);
		this->closeServerTab(tab);
	}
}

//Command button clicks enter the command into the commands to be sent array (using 'addCommandEntry')
System::Void QuakeLiveRcon::QLRcon::command1_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->rconTabs->TabCount) {
		this->addComandEntry(this->getRconTabNumber(this->activeTab), this->settingsArray[3]);
	}
}

System::Void QuakeLiveRcon::QLRcon::command2_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->rconTabs->TabCount) {
		this->addComandEntry(this->getRconTabNumber(this->activeTab), this->settingsArray[6]);
	}
}

System::Void QuakeLiveRcon::QLRcon::command3_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->rconTabs->TabCount) {
		this->addComandEntry(this->getRconTabNumber(this->activeTab), this->settingsArray[9]);
	}
}

System::Void QuakeLiveRcon::QLRcon::command4_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->rconTabs->TabCount) {
		this->addComandEntry(this->getRconTabNumber(this->activeTab), this->settingsArray[12]);
	}
}

System::Void QuakeLiveRcon::QLRcon::command5_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->rconTabs->TabCount) {
		this->addComandEntry(this->getRconTabNumber(this->activeTab), this->settingsArray[15]);
	}
}

System::Void QuakeLiveRcon::QLRcon::command6_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->rconTabs->TabCount) {
		this->addComandEntry(this->getRconTabNumber(this->activeTab), this->settingsArray[18]);
	}
}

//uses the steam connect link. Requires the link have a default setting in Windows
System::Void QuakeLiveRcon::QLRcon::connectGame_Click(System::Object^  sender, System::EventArgs^  e) {
	//Steam Connection Link from Teamspeak
	// steam://connect/107.182.225.231:27960
	if (this->rconTabs->TabCount) {
		this->GamePortThreadTries = 0;
		this->connectToGame();
	}
}

//Event handlers for selection on the mouse right-click menu in the ouput boxes
System::Void QuakeLiveRcon::QLRcon::rClickItem1_MouseDown(System::Object^  sender, EventArgs^  e) {
	Clipboard::SetText(this->outBox[this->rClickTab]->SelectedText->ToString());
}
System::Void QuakeLiveRcon::QLRcon::rClickItem2_MouseDown(System::Object^  sender, EventArgs^  e) {
	FileInfo^ fileInfo = gcnew FileInfo(LOG_FILE_LOCATION + this->logFileName);
	if (fileInfo->Exists)
		System::Diagnostics::Process::Start(LOG_FILE_LOCATION + this->logFileName);
	else
		MessageBox::Show("There is no log file for this server.", "No log file exists.", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
}
System::Void QuakeLiveRcon::QLRcon::rClickItem3_MouseDown(System::Object^  sender, EventArgs^  e) {
	if (System::IO::Directory::Exists(LOG_FILE_LOCATION))
		System::Diagnostics::Process::Start(LOG_FILE_LOCATION);
	else
		MessageBox::Show("There is no directory for storing log files.", "No log file directory exists.", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
}
System::Void QuakeLiveRcon::QLRcon::rClickItem4_MouseDown(System::Object^  sender, EventArgs^  e) {
	this->serverTabConnection(this->rClickTab);
}
System::Void QuakeLiveRcon::QLRcon::rClickItem5_MouseDown(System::Object^  sender, EventArgs^  e) {
	this->closeServerTab(this->rClickTab);
}
System::Void QuakeLiveRcon::QLRcon::rClickItem6_MouseDown(System::Object^  sender, EventArgs^  e) {
	//Creates the instance of the Commands Form
	Commands ^ commandDialog = gcnew Commands(iniFile, this->rClickTab);
	//Shows the Commands Form
	commandDialog->ShowDialog();
}
//System::Void QuakeLiveRcon::QLRcon::rClickItem7_MouseDown(System::Object^  sender, EventArgs^  e) {
//	if (this->rconTabs->TabCount && !this->GameStatsThread) {
//		this->GameStatsThreadTries = 0;
//		this->startStatusWindowProcess();
//	}
//}

void QuakeLiveRcon::QLRcon::startStatusWindowProcess() {
	if (this->GameStatsThread && this->GameStatsThread->IsAlive && this->GamePortThreadTries < 10) {
		this->GameStatsThreadTries++;
		this->GameStatsThread->Abort();
		this->startStatusWindowProcess();
		//this->openStatusWindow(this->connectedServers[this->rClickTab]);
	}
	else if (this->GameStatsThreadTries >= 10) {
		MessageBox::Show("A problem occurred with the connection attempt. Please try again. Restart the program if the problem persists.",
			"Connect Attempt Unsuccessful", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
	else {
		int tab = this->getRconTabNumber(this->activeTab);
		if (this->tabs[tab] == 1) {
			this->GameStatsThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &QuakeLiveRcon::QLRcon::openStatusWindow));
			this->GameStatsThread->Start(this->rClickTab);
		}
		else {
			MessageBox::Show("The " + this->serverNames[tab] + " Server is not connected to the RCON port."
				"\nConnect to the RCON port of the server before connecting to the game.",
				"RCON not Connected", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		}
	}

}

void QuakeLiveRcon::QLRcon::openStatusWindow(Object^ tab) {
	int serverTab = (int)tab;
	array<String^>^ ipArray = this->connectedServers[serverTab]->Split(':');
	array<String^>^ info = gcnew array<String^>(13);
	//info[0] is the IP; info[1] is the Game Port; info[2] is the Password; info[3] is the UUID; info[4] thru info[12] are the Colors
	info[0] = ipArray[0];
	info[1] = ipArray[1];
	info[2] = "";
	info[3] = this->uuid;
	info[4] = this->settingsArray[25];
	info[5] = this->settingsArray[26];
	info[6] = this->settingsArray[27];
	info[7] = this->settingsArray[28];
	info[8] = this->settingsArray[29];
	info[9] = this->settingsArray[30];
	info[10] = this->settingsArray[31];
	info[11] = this->settingsArray[32];
	info[12] = this->settingsArray[33];

	bool found = false;
	this->GameStatsThreadTries = 0;
	
	this->addComandEntry(serverTab, "zmq_stats_password");
	while (!found && this->GameStatsThreadTries < 1000) {
		this->GameStatsThreadTries++;
		if (String::Compare(this->statsConnectInfo[serverTab, 1], "")) {
			info[2] = this->statsConnectInfo[serverTab, 1];
			found = true;
		}
		this->GameStatsThread->Sleep(1);
	}
	this->GameStatsThreadTries = 0;
	found = false;
	this->addComandEntry(serverTab, "net_port");
	while (!found && this->GameStatsThreadTries < 1000) {
		this->GameStatsThreadTries++;
		if (String::Compare(this->statsConnectInfo[serverTab, 0], "")) {
			info[1] = this->statsConnectInfo[serverTab, 0];
			found = true;
		}
		//System::Threading::Thread::Sleep(1);
		this->GameStatsThread->Sleep(1);
	}

	//MessageBox::Show("Info " + this->statsConnectInfo[serverTab, 0] + " : " + this->statsConnectInfo[serverTab, 1], "QLRcon", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	if (found) {
		//Creates the instance of the status Form
		Status ^ statusWindow = gcnew Status(info);
		//Creates an event handler for when the edit servers Form is closed
		FormClosedEventHandler^ serversHandler = gcnew FormClosedEventHandler(this, &QLRcon::OnStatusFormClosed);
		//Registers the event handler with the new edit servers Form (must hapen before showing the form)
		statusWindow->FormClosed += serversHandler;
		//Shows the status Form
		statusWindow->ShowDialog();
	}
	else {
		this->GameStatsThread->Abort();
		delete this->GameStatsThread;
		this->GameStatsThread = nullptr;
	}

	this->statsConnectInfo[serverTab, 0] = "";
	this->statsConnectInfo[serverTab, 1] = "";

	delete ipArray;
	ipArray = nullptr;
	delete info;
	info = nullptr;
	return;
}

System::Void QuakeLiveRcon::QLRcon::output0_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[0];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 0;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
	//if (e->Button == System::Windows::Forms::MouseButtons::Left) {
	//	here;
	//}
}
System::Void QuakeLiveRcon::QLRcon::output0_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output0_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output0->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output0->SelectedText->ToString());
		else
			e->Handled = true;
	e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[1];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 1;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output1->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output1->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[2];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 2;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output2_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output2_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output2->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output2->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output3_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[3];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 3;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output3_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output3_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output3->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output3->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output4_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[4];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 4;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output4_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output4_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output4->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output4->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output5_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[5];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 5;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output5_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output5_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output5->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output5->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output6_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[6];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 6;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output6_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output6_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output6->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output6->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output7_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[7];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 7;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output7_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output7_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output7->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output7->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output8_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[8];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 8;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output8_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output8_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output8->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output8->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output9_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[9];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 9;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output9_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output9_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output9->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output9->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output10_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[10];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 10;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output10_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output10_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output10->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output10->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output11_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[11];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 11;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output11_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output11_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output11->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output11->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output12_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[12];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 12;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output12_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output12_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output12->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output12->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output13_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[13];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 13;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output13_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output13_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output13->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output13->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output14_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[14];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 14;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output14_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output14_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output14->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output14->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output15_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[15];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 15;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output15_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output15_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output15->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output15->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output16_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[16];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 16;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output16_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output16_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output16->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output16->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output17_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[17];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 17;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output17_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output17_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output17->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output17->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output18_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[18];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 18;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output18_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output18_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output18->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output18->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::output19_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		String^ ipPort = this->connectedServers[19];
		array<String^>^ sectionArray = ipPort->Split(':');
		this->logFileName = gcnew String(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
		this->outputRClick->Show(Point(MousePosition));
		this->rClickTab = 19;
		delete ipPort;
		ipPort = nullptr;
		delete sectionArray;
		sectionArray = nullptr;
	}
}
System::Void QuakeLiveRcon::QLRcon::output19_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}
System::Void QuakeLiveRcon::QLRcon::output19_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control == true)
		if (e->KeyCode == Keys::A)
			this->output19->SelectAll();
		else if (e->KeyCode == Keys::C)
			Clipboard::SetText(this->output19->SelectedText->ToString());
		else
			e->Handled = true;
		e->Handled = true;
}

System::Void QuakeLiveRcon::QLRcon::serverList_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}

///Utility Functions

//loads the server names from the ini to the combobox
void QuakeLiveRcon::QLRcon::loadServersToComboBox() {
	this->savedServers->Clear();
	List<String^>^ sections = gcnew List<String^>();
	List<String^>^ serverNames = gcnew List<String^>();
	this->ini->getSectionNames(sections); // same as (*ini).getSectionNames();
	this->serverList->Items->Clear();

	for (int i = 0; i < sections->Count; i++) {
		if (QuakeLiveRcon::ServersEdit::isServerIpPort(sections[i])) {
			this->savedServers->Add(sections[i]);
			serverNames->Add(this->ini->getValue(sections[i], "name"));
		}
	}

	if (this->ini->isTrue("main", "alphabetically")) {
		bool swap = true;
		int i;
		int j = 2;
		int length = serverNames->Count;
		String^ tempIpPort;
		String^ tempName;

		//Perform a bubble sort if alphabetically sort is selected
		while (swap) {
			swap = false;
			for (i = 0; i <= length - j; i++) {
				if (String::Compare(serverNames[i], serverNames[i + 1]) > 0) {
					tempName = serverNames[i + 1];
					serverNames[i + 1] = serverNames[i];
					serverNames[i] = tempName;
					tempIpPort = this->savedServers[i + 1];
					this->savedServers[i + 1] = this->savedServers[i];
					this->savedServers[i] = tempIpPort;
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

	for (int i = 0; i < serverNames->Count; i++) {
		this->serverList->Items->Add(serverNames[i]);
	}

	this->serverList->Items->Add("");
	delete sections;
	sections = nullptr;
	delete serverNames;
	serverNames = nullptr;
	return;
}

void QuakeLiveRcon::QLRcon::autoConectServers() {
	for each (String^ server in this->savedServers) {
		//MessageBox::Show(server, "Server", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		if (QuakeLiveRcon::ServersEdit::isServerIpPort(server) && this->ini->isTrue(server, "connect")) {
			this->conectServer(server);
		}
	}
	
	this->viewServerTabButtons();	
}

void QuakeLiveRcon::QLRcon::viewServerTabButtons() {
	if (this->rconTabs->TabCount) {
		//sets the system so it will not go to sleep while the program is running (allows the monitor to turn off)
		if (this->rconBooleans[3]) {
			this->rconBooleans[4] = true;
			SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);
		}

		this->disconnectTab->Visible = true;
		this->closeTab->Visible = true;

		if (!System::String::Compare(this->settingsArray[1], "true") || !System::String::Compare(this->settingsArray[1], "True")
			|| !System::String::Compare(this->settingsArray[1], "TRUE")) {
			this->command1->Visible = true;
			this->command1->Text = this->settingsArray[2];
		}
		else
			this->command1->Visible = false;

		if (!System::String::Compare(this->settingsArray[4], "true") || !System::String::Compare(this->settingsArray[4], "True")
			|| !System::String::Compare(this->settingsArray[4], "TRUE")) {
			this->command2->Visible = true;
			this->command2->Text = this->settingsArray[5];
		}
		else
			this->command2->Visible = false;

		if (!System::String::Compare(this->settingsArray[7], "true") || !System::String::Compare(this->settingsArray[7], "True")
			|| !System::String::Compare(this->settingsArray[7], "TRUE")) {
			this->command3->Visible = true;
			this->command3->Text = this->settingsArray[8];
		}
		else
			this->command3->Visible = false;

		if (!System::String::Compare(this->settingsArray[10], "true") || !System::String::Compare(this->settingsArray[10], "True")
			|| !System::String::Compare(this->settingsArray[10], "TRUE")) {
			this->command4->Visible = true;
			this->command4->Text = this->settingsArray[11];
		}
		else
			this->command4->Visible = false;

		if (!System::String::Compare(this->settingsArray[13], "true") || !System::String::Compare(this->settingsArray[13], "True")
			|| !System::String::Compare(this->settingsArray[13], "TRUE")) {
			this->command5->Visible = true;
			this->command5->Text = this->settingsArray[14];
		}
		else
			this->command5->Visible = false;

		if (!System::String::Compare(this->settingsArray[16], "true") || !System::String::Compare(this->settingsArray[16], "True")
			|| !System::String::Compare(this->settingsArray[16], "TRUE")) {
			this->command6->Visible = true;
			this->command6->Text = this->settingsArray[17];
		}
		else
			this->command6->Visible = false;

		if (!System::String::Compare(this->settingsArray[19], "true") || !System::String::Compare(this->settingsArray[19], "True")
			|| !System::String::Compare(this->settingsArray[19], "TRUE"))
			this->connectGame->Visible = true;
		else
			this->connectGame->Visible = false;
	}
	else {
		this->disconnectTab->Visible = false;
		this->closeTab->Visible = false;

		this->command1->Visible = false;
		this->command2->Visible = false;
		this->command3->Visible = false;
		this->command4->Visible = false;
		this->command5->Visible = false;
		this->command6->Visible = false;
		this->connectGame->Visible = false;
	}
}

//Used during startup to connect the servers marked as auto connect
bool QuakeLiveRcon::QLRcon::conectServer(String^ server) {
	bool connected = false;
	if (!this->rconTabs->TabCount) {
		this->Controls->Add(this->rconTabs);
		this->Controls->Remove(this->notConnectedMessage);
	}

	int firstFree = -1;
	for (int i = 0; i < MAX_SERVERS; i++) {
		if (this->tabs[i] == 0) {
			firstFree = i;
			break;
		}
	}

	if (firstFree >= 0 && firstFree < MAX_SERVERS) {
		this->tabLocation[firstFree] = this->rconTabs->TabCount;
		this->tabs[firstFree] = 1;
		this->disconnect[firstFree] = false;
		this->connectedServers[firstFree] = server;
		this->serverNames[firstFree] = this->ini->getValue(server, "name");
		this->logServer[firstFree] = this->ini->isTrue(server, "log");
		this->addTab(firstFree);
		this->updateServerTabInfo(firstFree);
		this->activeTab = "{rcon" + firstFree + "}";
		this->rconTabs->SelectedIndex = this->tabLocation[firstFree];
		//connect to the server
		this->serverConnection(firstFree, L"connect");
		connected = true;
	}
	else {
		MessageBox::Show("All available connections are in use. Close a server tab to be able to connect to another server.",
			"No Available Connection Tabs", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
	return connected;
}

//Used when the up/down arrows are used to get the prev/next command
String^ QuakeLiveRcon::QLRcon::getCommandEntry(int tab, String^ line, String^ direction) {
	String^ command;
	int i, count = -1;
	bool foundMatch = false, foundNext = false;

	for (i = 0; i < STORED_COMMANDS && !foundMatch; i++) {
		if (!String::Compare(line, this->commands[tab, i])) {
			count = i;
			foundMatch = true;
			break;
		}
	}

	if (foundMatch && count != -1) {
		if (!String::Compare(direction, "down")) {
			if (count > 0)
				command = this->commands[tab, count - 1];
			else {
				for (i = STORED_COMMANDS - 1; i > 0 && !foundNext; i--) {
					if (String::Compare("", this->commands[tab, i])) {
						command = this->commands[tab, i];
						foundNext = true;
					}
				}
			}
		}
		else {
			if (count < STORED_COMMANDS - 1) {
				if (String::Compare("", this->commands[tab, i]))
					command = this->commands[tab, count + 1];
				else
					command = this->commands[tab, 0];
			}
			else
				command = this->commands[tab, 0];
		}
	}
	else {
		//this->output0->AppendText("Not Matched\n");
		command = this->commands[tab, 0];
	}

	return command;
}

//Adds supplied command to the send command array
void QuakeLiveRcon::QLRcon::addComandEntry(int tab, String^ command) {
	if (this->tabs[tab] == 1) {
		//add command to the send commands array
		for (int i = 0; i < STORED_COMMANDS; i++) {
			if (!String::Compare("", this->sendCommands[tab, i])) {
				this->sendCommands[tab, i] = command;
				break;
			}
		}

		//add command to the stored commands array
		bool match = false;
		int i, j;

		for (i = 0; i < STORED_COMMANDS && !match; i++) {
			if (!String::Compare("", this->commands[tab, i]))
				break;
			else if (!String::Compare(this->commands[tab, i], command)) {
				match = true;
				break;
			}
		}

		if (match || i < STORED_COMMANDS)
			j = i;
		else
			j = STORED_COMMANDS - 1;

		for (j; j > 0; j--)
			this->commands[tab, j] = this->commands[tab, j - 1];
		this->commands[tab, 0] = command;
	}
}

//Clears the send command array
void QuakeLiveRcon::QLRcon::clearCommandEntries(int tab) {
	for (int i = 0; i < STORED_COMMANDS; i++)
		this->commands[tab, i] = "";
}

//returns the next command in the send command array and clears the one returned
char* QuakeLiveRcon::QLRcon::getNextCommand(int tab) {
	this->command[tab] = nullptr;
	if (!this->disconnect[tab]) {
		if (String::Compare("", this->sendCommands[tab, 0])) {
			//convert this->sendCommands[tab, 0] to char*
			pin_ptr<const wchar_t> wch = PtrToStringChars(this->sendCommands[tab, 0]);
			const size_t origsize = wcslen(wch) + 1;
			const size_t newsize = origsize * 2;
			size_t convertedChars = 0;
			this->command[tab] = new char[newsize];
			wcstombs_s(&convertedChars, this->command[tab], newsize, wch, _TRUNCATE);

			for (int i = 0; i < STORED_COMMANDS - 1; i++)
				if (String::Compare("", this->sendCommands[tab, i + 1]))
					this->sendCommands[tab, i] = this->sendCommands[tab, i + 1];
				else
					this->sendCommands[tab, i] = "";
		}
	}
	return this->command[tab];
}

//Handles the server zmq threads and conneciton/disconneciton statuses
void QuakeLiveRcon::QLRcon::serverConnection(int server, String^ action) {
	String^ ipPort = this->connectedServers[server];
	array<String^>^ sectionArray = ipPort->Split(':');
	String^ ip = sectionArray[0];
	String^ port = sectionArray[1];
	String^ password = this->ini->getValue(ipPort, "password");
	//TimeSpan waitTime = TimeSpan(0, 0, 1); //wait 1 second

	if (!System::String::Compare(action, L"connect")) {
		if (this->rconBooleans[0] && this->logServer[server])
			this->logServerWriter[server] = gcnew LogFileWriter(gcnew String(ip + "_" + port + "_log"), LOG_FILE_LOCATION);
		this->serverConnectionThread[server] = gcnew Thread(gcnew ParameterizedThreadStart(this, &QuakeLiveRcon::QLRcon::connectToServer));
		this->serverConnectionThread[server]->Start(Tuple::Create(ip, port, password, server));
	}
	else {
		this->displayText(server, "Disconnecting from the server.\n");
		this->disconnect[server] = true;
		this->serverConnectionThread[server]->Join(TimeSpan(0, 0, 1)); //wait 1 second
		this->serverConnectionThread[server]->Abort();
		if (this->statsConnectionThread[server] && this->statsConnectionThread[server]->IsAlive)
			this->statsConnectionThread[server]->Abort();
		if (this->rconBooleans[0] && this->logServer[server])
			this->logServer[server] = !this->logServerWriter[server]->writeRemaining();
		if (this->logServerWriter[server]) {
			delete this->logServerWriter[server];
			this->logServerWriter[server] = nullptr;
		}
		delete this->serverConnectionThread[server];
		this->serverConnectionThread[server] = nullptr;
	}
	delete ipPort;
	ipPort = nullptr;
	delete sectionArray;
	sectionArray = nullptr;
	delete ip;
	ip = nullptr;
	delete port;
	port = nullptr;
	delete password;
	password = nullptr;
}

//used to disconnect from servers still connected when the program exits
void QuakeLiveRcon::QLRcon::exitConnection(int server) {
	bool logging = false;

	this->displayText(server, "Disconnecting from the server.\n");

	if (this->rconBooleans[0] && this->logServer[server] && this->tabs[server] != 0)
		logging = true;

	this->disconnect[server] = true;

	if (logging)
		this->logServer[server] = !this->logServerWriter[server]->writeRemaining();
	else
		this->logServer[server] = false;

	if (this->statsConnectionThread[server] && this->statsConnectionThread[server]->IsAlive)
		this->statsConnectionThread[server]->Abort();

	this->tabs[server] = 0;
	return;
}

//updates displayed information for the selected server tab
void QuakeLiveRcon::QLRcon::updateServerTabInfo(int selectedTab) {
	String^ ipPort = this->connectedServers[selectedTab];
	String^ name = this->serverNames[selectedTab];
	this->serverName->Text = name;
	this->IPLabel->Text = ipPort;
	String^ tabName;

	if (name->Length > 15) {
		array<Char>^ truncated = gcnew array<Char>(name->Length);
		System::IO::StringReader^ sr = gcnew System::IO::StringReader(name);
		sr->Read(truncated, 0, 15);
		tabName = gcnew String(truncated);
		delete truncated;
		truncated = nullptr;
	}
	else
		tabName = name;
	//MessageBox::Show(System::Convert::ToString(this->tabs[selectedTab]), "Tab: " + System::Convert::ToString(selectedTab), MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	if (this->tabs[selectedTab] == -1) {
		this->disconnectTab->Text = "Reconnect Current Tab";
	}
	else {
		this->disconnectTab->Text = "Disconnect Current Tab";
	}

	this->serverTabs[selectedTab]->Text = tabName;
	delete ipPort;
	ipPort = nullptr;
	delete name;
	name = nullptr;
	delete tabName;
	tabName = nullptr;
}

//returns the rconTabs->rcon* tab number (used primarily for array access)
int QuakeLiveRcon::QLRcon::getRconTabNumber(String^ tabName) {
	if (tabName->Contains("{rcon0}"))
		return 0;
	if (tabName->Contains("{rcon1}"))
		return 1;
	if (tabName->Contains("{rcon2}"))
		return 2;
	if (tabName->Contains("{rcon3}"))
		return 3;
	if (tabName->Contains("{rcon4}"))
		return 4;
	if (tabName->Contains("{rcon5}"))
		return 5;
	if (tabName->Contains("{rcon6}"))
		return 6;
	if (tabName->Contains("{rcon7}"))
		return 7;
	if (tabName->Contains("{rcon8}"))
		return 8;
	if (tabName->Contains("{rcon9}"))
		return 9;
	if (tabName->Contains("{rcon10}"))
		return 10;
	if (tabName->Contains("{rcon11}"))
		return 11;
	if (tabName->Contains("{rcon12}"))
		return 12;
	if (tabName->Contains("{rcon13}"))
		return 13;
	if (tabName->Contains("{rcon14}"))
		return 14;
	if (tabName->Contains("{rcon15}"))
		return 15;
	if (tabName->Contains("{rcon16}"))
		return 16;
	if (tabName->Contains("{rcon17}"))
		return 17;
	if (tabName->Contains("{rcon18}"))
		return 18;
	if (tabName->Contains("{rcon19}"))
		return 19;
	return -1;
}

//Udates the tabPage index number location for visible/active rconTab pages
void QuakeLiveRcon::QLRcon::updateTabLocations() {
	int rconIndex;
	for (int i = 0; i < this->rconTabs->TabCount; i++) {
		this->rconTabs->SelectedIndex = i;
		rconIndex = this->getRconTabNumber(gcnew String("{" + this->rconTabs->SelectedTab->Name + "}"));
		this->tabLocation[rconIndex] = i;
	}
}

//adds a tab to be used for a new server connection
void QuakeLiveRcon::QLRcon::addTab(int add) {
	if (this->rconTabs->TabPages->Contains(this->serverTabs[add])) {
		//MessageBox::Show("Already Here", "Tab", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		this->rconTabs->SelectedIndex = this->tabLocation[add];
	}
	else {
		this->rconTabs->Controls->Add(this->serverTabs[add]);
		this->outBox[add]->ResetText();
		this->inBox[add]->Text = L"Enter Command Here ... <Enter to send> ...";
	}
}

//removes a tab when no longer used for a server conneciton
void QuakeLiveRcon::QLRcon::removeTab(int remove) {
	//MessageBox::Show(System::Convert::ToString(remove), "Tab", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	this->outBox[remove]->ResetText();
	this->inBox[remove]->ResetText();
	this->rconTabs->Controls->Remove(this->serverTabs[remove]);
	if (!this->rconTabs->TabCount) {
		this->viewServerTabButtons();
	}
}

//Generates a random UUID for use by the zmq socket for identification
//TODO: See if making this less random (so it identifies the computer) is a good idea?
void QuakeLiveRcon::QLRcon::generateUUID() {
	UUID uuid;
	UuidCreate(&uuid);
	char * str;
	UuidToStringA(&uuid, (RPC_CSTR*)&str);
	this->uuid = gcnew String(str);
}

//Used to start the game port conneciton thread
void QuakeLiveRcon::QLRcon::connectToGame() {
	if (this->GamePortThread && this->GamePortThread->IsAlive && this->GamePortThreadTries < 10) {
		this->GamePortThreadTries++;
		this->GamePortThread->Abort();
		this->connectToGame();
	}
	else if (this->GamePortThreadTries >= 10) {
		MessageBox::Show("A problem occurred with the connection attempt. Please try again. Restart the program if the problem persists.",
			"Connect Attempt Unsuccessful", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
	else {
		int tab = this->getRconTabNumber(this->activeTab);
		if (this->tabs[tab] == 1) {
			this->GamePortThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &QuakeLiveRcon::QLRcon::connectToGameServer));
			this->GamePortThread->Start(Tuple::Create(tab));
		}
		else {
			MessageBox::Show("The " + this->serverNames[tab] + " Server is not connected to the RCON port."
				"\nConnect to the RCON port of the server before connecting to the game.",
				"RCON not Connected", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		}
	}
}

//Adds the command to get the game port number and connects to the server once the zmq socket gets the port number
void QuakeLiveRcon::QLRcon::connectToGameServer(Object^ tab) {
	auto args = safe_cast<Tuple<int> ^>(tab);
	this->addComandEntry(args->Item1, "net_port");

	bool portFound = false;
	this->statsConnectInfo[args->Item1, 0] = gcnew String("");
	this->GamePortThreadTries = 0;

	while (!portFound && this->GamePortThreadTries < 1000) {
		this->GamePortThreadTries++;
		if (String::Compare(this->statsConnectInfo[args->Item1, 0], ""))
			portFound = true;
		//System::Threading::Thread::Sleep(1);
		this->GamePortThread->Sleep(1);
	}
	if (portFound) {
		String^ connectLink = "steam://connect/" + this->connectedServers[args->Item1]->Split(':')[0] + ":" + this->statsConnectInfo[args->Item1, 0];
		msclr::interop::marshal_context link;
		LPCTSTR cstr = link.marshal_as<const TCHAR*>(connectLink);
		ShellExecuteW(NULL, L"open", cstr, NULL, NULL, SW_SHOWDEFAULT);
		delete connectLink;
		connectLink = nullptr;
	}

	this->GamePortThread->Abort();
	delete this->GamePortThread;
	this->GamePortThread = nullptr;
	delete args;
	args = nullptr;

	return;
}

//starts and maintains the zmq socket for each server connection (each run in a Thread)
void QuakeLiveRcon::QLRcon::connectToServer(Object^ parameters) {
	auto args = safe_cast<Tuple<String^, String^, String^, Int32> ^>(parameters);

	String^ serverString = "tcp://" + args->Item1 + ":" + args->Item2;
	//convert ip:port to char*
	pin_ptr<const wchar_t> wch = PtrToStringChars(serverString);
	const size_t origsize = wcslen(wch) + 1;
	const size_t newsize = origsize * 2;
	size_t convertedChars = 0;
	char * server = new char[newsize];
	wcstombs_s(&convertedChars, server, newsize, wch, _TRUNCATE);
	delete serverString;
	wch = nullptr; //unhooks 'wch' from the memory now being used by 'server'

	bool registered = false;
	void * context = zmq_ctx_new();
	//assert(context);
	void * socket = zmq_socket(context, ZMQ_DEALER);
	//assert(socket);

	// monitor
	zmq_socket_monitor(socket, server, 0);
	//int rc = zmq_socket_monitor(socket, server, 0);
	//assert(rc == -1);
	//assert(zmq_errno() == EPROTONOSUPPORT);

	zmq_socket_monitor(socket, "inproc://monitor-socket", ZMQ_EVENT_ALL);
	//rc = zmq_socket_monitor(socket, "inproc://monitor-socket", ZMQ_EVENT_ALL);
	//assert(rc == 0);

	if (String::Compare(args->Item3, "")) {
		//convert password to char*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(args->Item3);
		const size_t origsize2 = wcslen(wch2) + 1;
		const size_t newsize2 = origsize2 * 2;
		size_t convertedChars2 = 0;
		char * pass = new char[newsize2];
		wcstombs_s(&convertedChars2, pass, newsize2, wch2, _TRUNCATE);
		wch2 = nullptr;

		//set the connect username and password in the socket
		zmq_setsockopt(socket, ZMQ_PLAIN_USERNAME, "rcon", 5);
		zmq_setsockopt(socket, ZMQ_PLAIN_PASSWORD, pass, strlen(pass));
		zmq_setsockopt(socket, ZMQ_ZAP_DOMAIN, "rcon", 5);

		this->displayText(args->Item4, L"Setting Username and Password for access.\n");
		delete pass;
		pass = NULL;
	}

	//convert uuid to char*
	pin_ptr<const wchar_t> wch3 = PtrToStringChars(this->uuid);
	const size_t origsize3 = wcslen(wch3) + 1;
	const size_t newsize3 = origsize3 * 2;
	size_t convertedChars3 = 0;
	char * uuid = new char[newsize3];
	wcstombs_s(&convertedChars3, uuid, newsize3, wch3, _TRUNCATE);
	zmq_setsockopt(socket, ZMQ_IDENTITY, uuid, strlen(uuid));
	wch3 = nullptr;

	this->displayText(args->Item4, "UUID: " + this->uuid + "\n");

	void * server_mon = zmq_socket(context, ZMQ_PAIR);
	zmq_connect(server_mon, "inproc://monitor-socket");
	zmq_connect(socket, server);

	this->displayText(args->Item4, "Connecting to " + gcnew String(server) + "\n");

	Int32 eventNum = NULL;
	array<String^>^ eventInfo = gcnew array<String^>(2) { nullptr, nullptr };
	bool status = !System::String::Compare(this->settingsArray[0], "true") ||
		!System::String::Compare(this->settingsArray[0], "True") || !System::String::Compare(this->settingsArray[0], "TRUE");

	bool playerEvents = !System::String::Compare(this->settingsArray[35], "true") ||
		!System::String::Compare(this->settingsArray[35], "True") || !System::String::Compare(this->settingsArray[35], "TRUE");

	zmq_pollitem_t pollset[1];
	pollset[0].socket = server_mon;
	pollset[0].events = ZMQ_POLLIN;	
	//= { { *server_mon, 0, ZMQ_POLLIN, 0 } };

	bool goodEvent;
	char * command = nullptr;
	String^ message;
	char * buff = new char[4096];
	wchar_t * wstr = new wchar_t[4096];
	char * monitorBuff = new char[256];
	wchar_t * monitorWstr = new wchar_t[256];
	Int32 numberCheck;
	size_t len;
	Int32 size;
	array<String^>^ msgArray = nullptr;
	Int32 messageInfoNumberCheck = NULL;
	Int32 eventID = NULL;
	Int32 eventSize = NULL;
	Int32 eventCheck = NULL;
	String^ displayLine = nullptr;
	bool printEntry = false;
	Int32 index = -1;

	while (!this->disconnect[args->Item4]) {
		zmq_poll(pollset, 1, POLL_TIMEOUT);

		goodEvent = this->checkMonitor(server_mon, &eventNum, eventInfo, monitorBuff, monitorWstr, &eventID, &eventSize, &eventCheck);

		if (goodEvent && eventNum > 0 && !Int32::TryParse(eventInfo[0], numberCheck)) {
			this->displayText(args->Item4, eventInfo[0] + " : " + eventInfo[1] + "\n");
		}

		if (goodEvent && eventNum == ZMQ_EVENT_CONNECTED) {
			this->displayText(args->Item4, "Registering with the server.\n");
			zmq_send(socket, "register", 9, ZMQ_DONTWAIT);

			if (playerEvents) {
				this->statsConnectInfo[args->Item4, 0] = "";
				this->statsConnectInfo[args->Item4, 1] = "";
				this->addComandEntry(args->Item4, "zmq_stats_password");
				this->addComandEntry(args->Item4, "net_port");
				if (this->statsConnectionThread[args->Item4] && this->statsConnectionThread[args->Item4]->IsAlive) {
					this->statsConnectionThread[args->Item4]->Abort();
					System::Threading::Thread::Sleep(TimeSpan(0, 0, 0, 0, 500)); //wait 500 milliseconds
					delete this->statsConnectionThread[args->Item4];
					this->statsConnectionThread[args->Item4] = nullptr;
				}
				this->PlayerEventsThreadTries = 0;
				this->playerEventsProcess(parameters, args->Item4);
			}

			if (status)
				this->addComandEntry(args->Item4, "status");

			registered = true;
		}

		if (registered) {
			try {
				command = this->getNextCommand(args->Item4);
				while (command != nullptr) {
					this->displayText(args->Item4, "Sending command: " + gcnew String(command) + "\n");
					len = strlen(command);
					zmq_send(socket, command, len, ZMQ_DONTWAIT);
					command = this->getNextCommand(args->Item4);
				}

				while (1) {
					try {
						size = zmq_recv(socket, buff, 4095, ZMQ_DONTWAIT);
						if (size > 0) {
							if (size > 4095)
								size = 4095;

							if (buff != NULL) {
								buff[size] = '\0';

								MultiByteToWideChar(CP_UTF8, 0, buff, -1, wstr, size + 1);
								message = gcnew String(wstr);

								message = this->formatMessage(message, index);
								this->buildDisplayLine(args->Item4, message, displayLine, &printEntry);

								if (this->rconBooleans[0] && this->logServer[args->Item4])
									this->buildLogFileLines(args->Item4, message);

								this->getMessageInfo(args->Item4, message, msgArray, &messageInfoNumberCheck);

								delete message;
								message = nullptr;
								delete msgArray;
								msgArray = nullptr;
							}
							else {
								break;
							}
						}
						else {
							break;
						}
					}
					catch (...) {
						break;
					}

					//int more = 0;           //  Multipart detection
					//size_t more_size = sizeof(more);
					//zmq_getsockopt(socket, ZMQ_RCVMORE, &more, &more_size);
					////socket->getsockopt(ZMQ_RCVMORE, &more, &more_size);
					//if (!more)
					//	break;              //  Last message part
				}
			}
			catch (...) {
				break;
			}
		}

	}

	delete[] wstr;
	wstr = NULL;
	delete buff;
	buff = NULL;
	delete monitorBuff;
	monitorBuff = NULL;
	delete monitorWstr;
	monitorWstr = NULL;

	zmq_disconnect(socket, server);
	delete server;
	server = NULL;
	zmq_close(server_mon);
	server_mon = NULL;
	zmq_close(socket);
	socket = NULL;
	zmq_ctx_destroy(context);
	context = NULL;
	delete command;
	command = NULL;
	delete eventInfo;
	//eventInfo = nullptr;
	this->displayText(args->Item4, "Disconnected from the server.\n");
	delete args;
	args = nullptr;
	return;
}

void QuakeLiveRcon::QLRcon::getMessageInfo(int tab, String^ message, array<String^>^ msgArray, Int32 * numberCheck) {
	//"net_port" is:"27960" default:"27960"
	msgArray = message->Split('\"');
	if (msgArray->Length >= 7) {
		msgArray[3] = this->stripColorCodes(msgArray[3]);
		if (Int32::TryParse(msgArray[3], *numberCheck)) {
			this->statsConnectInfo[tab, 0] = msgArray[3];
		}
		else {
			this->statsConnectInfo[tab, 1] = msgArray[3];
		}
	}
}

//Checks the monitor port for a server status message (called in the connectToServer function)
bool QuakeLiveRcon::QLRcon::checkMonitor(void * monitor, Int32 * eventNum, array<String^>^ eventInfo, 
	char * buffer, wchar_t * wstr, Int32 * eventID, Int32 * size, Int32 * eventCheck) {
	*eventNum = -1;
	*eventCheck = 0;
	eventInfo[0] = nullptr;
	eventInfo[1] = nullptr;

	*eventID = NULL;

	while (1) {
		try {
			*size = zmq_recv(monitor, buffer, 255, ZMQ_DONTWAIT);
			if (*size > 255)
				*size = 255;

			if (buffer != NULL && *size > 0) {
				if (*eventID == NULL)
					*eventID = (short)buffer[0];
				buffer[*size] = '\0';

				MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wstr, *size + 1);
				eventInfo[1] = gcnew String(wstr);
			}
			else {
				break;
			}
		}
		catch (...) {
			break;
		}

	}

	while (*eventCheck < EVENT_ARRAY_SIZE) {
		if (*eventID == this->eventKeys[*eventCheck])
			break;
		*eventCheck = *eventCheck + 1;
	}

	if (*eventCheck < EVENT_ARRAY_SIZE)
		eventInfo[0] = gcnew String(this->eventNames[*eventCheck]);
	else
		eventInfo[0] = gcnew String(System::Convert::ToString(*eventID));

	*eventNum = (Int32)*eventID;

	return (*eventNum != -1);
}

void QuakeLiveRcon::QLRcon::playerEventsProcess(Object^ parameters, int tab) {
	if (this->statsConnectionThread[tab] && this->statsConnectionThread[tab]->IsAlive && this->PlayerEventsThreadTries < 10) {
		this->PlayerEventsThreadTries++;
		this->statsConnectionThread[tab]->Abort();
		this->playerEventsProcess(parameters, tab);
	}
	else if (this->PlayerEventsThreadTries >= 10) {
		
	}
	else {
		if (this->tabs[tab] == 1) {
			this->statsConnectionThread[tab] = gcnew Thread(gcnew ParameterizedThreadStart(this, &QuakeLiveRcon::QLRcon::getGameStatsInfo));
			this->statsConnectionThread[tab]->Start(parameters);
		}
	}

}

void QuakeLiveRcon::QLRcon::getGameStatsInfo(Object^ parameters) {
	auto args = safe_cast<Tuple<String^, String^, String^, int> ^>(parameters);

	this->PlayerEventsThreadTries = 0;

	bool foundPass = false;
	this->GameStatsThreadTries = 0;

	while (!foundPass && this->PlayerEventsThreadTries < 1000) {
		this->PlayerEventsThreadTries++;
		if (String::Compare(this->statsConnectInfo[args->Item4, 1], "")) {
			foundPass = true;
		}
		System::Threading::Thread::Sleep(1);
	}
	
	this->PlayerEventsThreadTries = 0;
	bool foundPort = false;

	while (!foundPort && this->PlayerEventsThreadTries < 1000) {
		this->PlayerEventsThreadTries++;
		if (String::Compare(this->statsConnectInfo[args->Item4, 0], "")) {
			foundPort = true;
		}
		System::Threading::Thread::Sleep(1);
	}
	
	if (foundPass && foundPort)
		this->connectToStats(args->Item1, args->Item4);

	delete args;
	args = nullptr;
	
}

void QuakeLiveRcon::QLRcon::connectToStats(String^ ip, int tab) {
	String^ serverString = "tcp://" + ip + ":" + this->statsConnectInfo[tab, 0];
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

	//Json Parsing Variables
	Linq::JObject^ jObject = nullptr;
	Linq::JObject^ data = nullptr;
	Linq::JObject^ killer = nullptr;
	Linq::JObject^ victim = nullptr;

	void * context = zmq_ctx_new();
	void * socket = zmq_socket(context, ZMQ_SUB);
	//MessageBox::Show(this->statsConnectInfo[tab, 0] + " : " + this->statsConnectInfo[tab, 1], "Info", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	if (String::Compare(this->statsConnectInfo[tab, 1], "")) {
		//convert password to char*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(this->statsConnectInfo[tab, 1]);
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
		pass = NULL;
	}

	zmq_connect(socket, server);

	zmq_setsockopt(socket, ZMQ_SUBSCRIBE, "", 0);

	String^ message;
	char * buff = new char[4096];
	wchar_t * wstr = new wchar_t[4096];
	int size;

	while (!this->disconnect[tab]) {
		System::Threading::Thread::Sleep(TimeSpan(0, 0, 0, 0, 300));//wait 300 milliseconds

		try {
			size = zmq_recv(socket, buff, 4095, ZMQ_DONTWAIT);
			if (size == -1 || size == 0) {
				//if (zmq_errno() == EAGAIN) {}
				//else {}
				continue;
			}

			if (buff != NULL && size > 0) {
				if (size > 4095)
					size = 4095;
				buff[size] = '\0';

				MultiByteToWideChar(CP_UTF8, 0, buff, -1, wstr, size + 1);
				message = gcnew String(wstr);
				//MessageBox::Show("Here", "Stats", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				if (this->rconBooleans[5])
					this->parseJson(message, tab, jObject, data, killer, victim);

				delete message;
				message = nullptr;
			}
			else {
				continue;
			}
		}
		catch (...) {}
	}
	delete buff;
	buff = NULL;
	delete[] wstr;
	wstr = NULL;
	zmq_disconnect(socket, server);
	delete server;
	server = NULL;
	zmq_close(socket);
	socket = NULL;
	zmq_ctx_destroy(context);
	context = NULL;
}

void QuakeLiveRcon::QLRcon::parseJson(String^ message, int tab, 
	Newtonsoft::Json::Linq::JObject^ jObject, Newtonsoft::Json::Linq::JObject^ data, 
	Newtonsoft::Json::Linq::JObject^ killer, Newtonsoft::Json::Linq::JObject^ victim) {
	jObject = Linq::JObject::Parse(message);
	String^ playerMsg = "";
	//String^ dataInfo = jObject["DATA"]->ToString();
	data = Linq::JObject::Parse(jObject["DATA"]->ToString());
	//MessageBox::Show("Value: " + data["WARMUP"]->ToObject<bool>(), "Parse", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	bool warmup = data["WARMUP"]->ToObject<bool>();
	if (warmup && !this->rconBooleans[8]) {
		delete jObject;
		jObject = nullptr;
		delete data;
		data = nullptr;
		delete playerMsg;
		playerMsg = nullptr;
		return;
	}
	if (this->rconBooleans[7] && !String::Compare(jObject["TYPE"]->ToString(), "PLAYER_SWITCHTEAM")) {
		killer = Linq::JObject::Parse(data["KILLER"]->ToString());
		String^ team = killer["TEAM"]->ToString();
		String^ oldTeam = killer["OLD_TEAM"]->ToString();
		if (String::Compare(team, oldTeam)) {
			if (!String::Compare(team, "FREE"))
				team = " ^7Joined the ^2Fight^7";
			else if (!String::Compare(team, "SPECTATOR"))
				team = " ^7Joined the ^3Spectators^7";
			else if (!String::Compare(team, "RED"))
				team = " ^7Joined the ^1Red ^7team";
			else if (!String::Compare(team, "BLUE"))
				team = " ^7Joined the ^4Blue ^7team";

			if (!String::Compare(oldTeam, "FREE"))
				oldTeam = "the ^2Fight^7";
			else if (!String::Compare(oldTeam, "SPECTATOR"))
				oldTeam = "the ^3Spectators^7";
			else if (!String::Compare(oldTeam, "RED"))
				oldTeam = "^7the ^1Red ^7team";
			else if (!String::Compare(oldTeam, "BLUE"))
				oldTeam = "^7the ^4Blue ^7team";

			playerMsg = killer["NAME"]->ToString() + team + " from " + oldTeam;
			if (warmup)
				playerMsg += " ^7(^3warmup^7)";
			playerMsg += "\n";
		}

		delete team;
		team = nullptr;
		delete oldTeam;
		oldTeam = nullptr;
		delete killer;
		killer = nullptr;
	}
	else if (this->rconBooleans[6] && !String::Compare(jObject["TYPE"]->ToString(), "PLAYER_DEATH")) {
		victim = Linq::JObject::Parse(data["VICTIM"]->ToString());
		//MessageBox::Show(data["MOD"]->ToString(), "Parse", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		if (this->JTokenIsNullOrEnpty(data["KILLER"])) {
			if (!String::Compare(data["MOD"]->ToString(), "FALLING")) {
				playerMsg = victim["NAME"]->ToString() + " ^1CRATERED^7";
			}
			else if (!String::Compare(data["MOD"]->ToString(), "HURT")) {
				playerMsg = victim["NAME"]->ToString() + " ^1WAS IN THE WRONG PLACE^7";
			}
			else if (!String::Compare(data["MOD"]->ToString(), "LAVA")) {
				playerMsg = victim["NAME"]->ToString() + " ^1DOES A BACKFLIP INTO THE LAVA^7";
			}
			else if (!String::Compare(data["MOD"]->ToString(), "WATER")) {
				playerMsg = victim["NAME"]->ToString() + " ^1SANK LIKE A ROCK^7";
			}
			else if (!String::Compare(data["MOD"]->ToString(), "SLIME")) {
				playerMsg = victim["NAME"]->ToString() + " ^1MELTED^7";
			}
			else if (!String::Compare(data["MOD"]->ToString(), "CRUSH")) {
				playerMsg = victim["NAME"]->ToString() + " ^1WAS CRUSHED^7";
			}
			else {
				playerMsg = victim["NAME"]->ToString() + " ^1DIED FROM A " + data["MOD"]->ToString()  + "^7";
			}
			if (warmup)
				playerMsg += " ^7(^3warmup^7)";
			playerMsg += "\n";
		}
		else {
			killer = Linq::JObject::Parse(data["KILLER"]->ToString());
			if (String::Compare(killer["NAME"]->ToString(), victim["NAME"]->ToString())) {
				String^ killerColor = (!String::Compare(killer["TEAM"]->ToString(), "1") ? "^7(^1RED^7)" : "^7(^4BLUE^7)");
				String^ victimColor = (!String::Compare(victim["TEAM"]->ToString(), "1") ? "^7(^1RED^7)" : "^7(^4BLUE^7)");
				String^ weapon = killer["WEAPON"]->ToString();
				if (!String::Compare(weapon, "ROCKET"))
					weapon = "the Rocket Launcher";
				else if (!String::Compare(weapon, "LIGHTNING"))
					weapon = "the Lightning Gun";
				else if (!String::Compare(weapon, "RAILGUN"))
					weapon = "the Railgun";
				else if (!String::Compare(weapon, "SHOTGUN"))
					weapon = "the Shotgun";
				else if (!String::Compare(weapon, "GAUNTLET"))
					weapon = "the Gauntlet";
				else if (!String::Compare(weapon, "GRENADE"))
					weapon = "the Grenade Launcher";
				playerMsg = killerColor + " " + killer["NAME"]->ToString() + " ^5killed " + victimColor + " " + victim["NAME"]->ToString() + " ^7with " + weapon;
				if (warmup)
					playerMsg += " ^7(^3warmup^7)";
				playerMsg += "\n";
				delete killerColor;
				killerColor = nullptr;
				delete victimColor;
				victimColor = nullptr;
				delete weapon;
				weapon = nullptr;
			}
			else if (String::Compare(killer["WEAPON"]->ToString(), "OTHER_WEAPON")) {
				String^ deathType = "";
				if (!String::Compare(killer["WEAPON"]->ToString(), "ROCKET"))
					deathType = " ^7comitted suicide with the ^1Rocket Launcher";
				else if (!String::Compare(killer["WEAPON"]->ToString(), "PLASMA"))
					deathType = " ^7comitted suicide with the ^1Plasma Gun";
				else
					deathType = " ^7comitted suicide with the ^1" + killer["WEAPON"]->ToString();
				playerMsg = killer["NAME"]->ToString() + deathType;
				if (warmup)
					playerMsg += " ^7(^3warmup^7)";
				playerMsg += "\n";
				delete deathType;
				deathType = nullptr;
			}
			else {
				//playerMsg = killer["NAME"]->ToString() + " ^1CRATERED^7" + "\n";
			}
			delete killer;
			killer = nullptr;
		}

		delete victim;
		victim = nullptr;
	}
	else if (this->rconBooleans[9] && !String::Compare(jObject["TYPE"]->ToString(), "PLAYER_MEDAL")) {
		playerMsg = data["NAME"]->ToString() + " ^7got a ^6" + data["MEDAL"]->ToString() + " ^7medal";
		if (warmup)
			playerMsg += " (^3warmup^7)";
		playerMsg += "\n";
	}


	delete data;
	data = nullptr;
	delete jObject;
	jObject = nullptr;

	if (String::Compare(playerMsg, "")) {
		//Thread^ status = gcnew Thread(gcnew ParameterizedThreadStart(this, &QuakeLiveRcon::QLRcon::displayServerMessage));
		//status->Start(Tuple::Create(tab, playerMsg));
		this->displayServerMessage(tab, playerMsg);
		if (this->rconBooleans[0] && this->logServer[tab]) {
			if (this->rconBooleans[1])
				this->logServerWriter[tab]->storeEntry(this->stripColorCodes(playerMsg));
			else
				this->logServerWriter[tab]->storeEntry(playerMsg);
		}
	}
	delete playerMsg;
	playerMsg = nullptr;
}

bool QuakeLiveRcon::QLRcon::JTokenIsNullOrEnpty(Newtonsoft::Json::Linq::JToken^ token) {
	return (token->Type == Linq::JTokenType::Null ||
		token->Type == Linq::JTokenType::Array && !token->HasValues ||
		token->Type == Linq::JTokenType::Object && !token->HasValues ||
		token->Type == Linq::JTokenType::String && token->ToString()->Empty		
		);
}

//Initial formatting of the messages received by the zmq socket
String^ QuakeLiveRcon::QLRcon::formatMessage(String^ message, Int32 index) {
	//String^ temp = message->Replace("\\n", "");
	message = message->Replace("\\n", "");
	message = message->Replace(Char::ToString((char)25), "");
	message = message->Replace(Char::ToString((char)19), "");
	if (message->StartsWith("broadcast: print \"")) {
		message = message->Substring(18);
		message = message->Remove(message->Length - 2, 2);
		message = "^8Server^7: " + message + "\n";
	}
	else if (message->StartsWith("print \"")) {
		message = "    " + message->Substring(7);
		message = message->Remove(message->Length - 1, 1);
	}
	else if (message->Contains("^7:")) {
		index = message->IndexOf("^7:");
		message = message->Remove(index, 3);
		message = message->Insert(index, "^7:^" + this->settingsArray[42]);
	}
	else if (message->Contains("^7):")) {
		index = message->IndexOf("^7):");
		message = message->Remove(index, 4);
		message = message->Insert(index, "^7):^" + this->settingsArray[43]);
	}

	return message;
}

//prints the messages generated internally by this program to the specified RichTextBox
void QuakeLiveRcon::QLRcon::displayText(int tab, String^ text) {
	try {
		if (this->tabs[tab] != 0 || this->outBox[tab]->Visible) {
			if (this->outBox[tab]->InvokeRequired) {
				this->msgAgain[tab] = gcnew MessageArgReturningVoidDelegate(this, &QLRcon::displayText);
				try {
					this->Invoke(this->msgAgain[tab], gcnew array<Object^> { tab, text });
					delete this->msgAgain[tab];
					this->msgAgain[tab] = nullptr;
				}
				catch (ObjectDisposedException^) { 
					delete this->msgAgain[tab];
					this->msgAgain[tab] = nullptr;
				}
			}
			else {
				int lines = (int)SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_GETLINECOUNT, 0, 0);
				if (lines >= this->maxLines) {
					this->outBox[tab]->Select(0, (int)SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_LINEINDEX, lines - this->maxLines + this->linesRemove + 1, 0));
					this->outBox[tab]->SelectedText = "";
				}
				//Apend text to the richtextbox with or without timestamp
				if (this->rconBooleans[10]) {
					this->outBox[tab]->AppendText(DateTime::Now.ToString(this->settingsArray[41]) + " " + text);
				}
				else
					this->outBox[tab]->AppendText(text);

				if (this->rconBooleans[0] && this->logServer[tab])
					this->logServerWriter[tab]->storeEntry(text);

				if (!this->rconBooleans[2]) {
					//Gets the first visible line number and the line count and scrolls the linecount - the first visible line number - 34 (the smount of lines I counted on the screen)
					int currentLine = (int)SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_GETFIRSTVISIBLELINE, 0, 0);
					int lineCount = (int)SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_GETLINECOUNT, 0, 0);
					SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_LINESCROLL, 0, lineCount - currentLine - 34);
				}
			}
		}
		//Perform Garbage colleciton on inaccessible memory
		GC::Collect();
	}
	catch (ObjectDisposedException^) {}
	catch (NullReferenceException^) {}
	return;
}

//formats and prints the messages recieved from the server to the specified RichTextBox
void QuakeLiveRcon::QLRcon::displayServerMessage(int tab, String^ text) {
	//If accessing the textbox is currently prohibited, call the function again
	if (this->outBox[tab]->InvokeRequired) {
		this->callAgain[tab] = gcnew ObjectArgReturningVoidDelegate(this, &QLRcon::displayServerMessage);
		try {
			this->Invoke(this->callAgain[tab], gcnew array<Object^> { tab, text });
			delete this->callAgain[tab];
			this->callAgain[tab] = nullptr;
		}
		catch (ObjectDisposedException^) {
			delete this->callAgain[tab];
			this->callAgain[tab] = nullptr;
		}
	}
	else {
		//MessageBox::Show(text, "Display", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		this->foundColor[tab] = false;
		this->conversion[tab] = false;

		//Get the positions of all Carats that have numbers 0 thru 8 after them
		//***** Try just checking for "^1", "^2", "^3", "^4", "^5", "^6", "^7", or "^8" when "^" is found if this won't work *****
		//get the position of the first carat
		this->pos[tab] = text->IndexOf('^');
		while (this->pos[tab] != -1 && this->pos[tab] < text->Length - 1) {
			//the Try sections are to catch any problems converting the next character to an integer
			try {
				//Convert the character after the carat to an integer
				this->color[tab] = Int32::Parse(text->Substring(this->pos[tab] + 1, 1));

				if (this->color[tab] >= 0 && this->color[tab] <= 8) {
					//Mark color codes found as true so they are colored in the next section
					this->foundColor[tab] = true;
					//save the start position and color code in the colorIndex Dictionary
					this->colorIndex[tab]->Add(this->pos[tab], this->color[tab]);
					//Remove the color coding from the String
					text = text->Remove(this->pos[tab], 2);
					//Find the position of the next carat
					this->nextPos[tab] = text->IndexOf('^', this->pos[tab]);

					try {
						//Convert the character after the carat to an integer
						this->nextColor[tab] = Int32::Parse(text->Substring(this->nextPos[tab] + 1, 1));
						this->conversion[tab] = true; //Bool to mark the good/bad conversion process of the character after the carat to an integer
					}
					catch (FormatException^) {
						this->conversion[tab] = false;
					}
					while (this->conversion[tab] && this->nextPos[tab] == this->pos[tab]) {
						//save the start position and color code in the colorIndex Dictionary
						this->colorIndex[tab][this->pos[tab]] = this->nextColor[tab];
						//Remove the color coding from the String
						text = text->Remove(this->pos[tab], 2);
						//Find the position of the next carat
						this->nextPos[tab] = text->IndexOf('^', this->pos[tab]);
						//Bool to mark the good/bad conversion process of the character after the carat to an integer
						this->conversion[tab] = false;
						try {
							//Convert the character after the carat to an integer
							this->nextColor[tab] = Int32::Parse(text->Substring(this->nextPos[tab] + 1, 1));
							this->conversion[tab] = true;
						}
						catch (FormatException^) {
							this->conversion[tab] = false;
						}
					}
					//keep looping to the next carat position (until end of String) if color coding is not found
					while (this->nextPos[tab] != -1 && (!this->conversion[tab] || this->nextColor[tab] < 0 || this->nextColor[tab] > 8) && this->nextPos[tab] < text->Length - 1) {
						this->nextPos[tab] = text->IndexOf('^', this->nextPos[tab] + 1);
						try {
							//Convert the character after the carat to an integer
							this->nextColor[tab] = Int32::Parse(text->Substring(this->nextPos[tab] + 1, 1));
							this->conversion[tab] = true;
						}
						catch (FormatException^) {
							this->conversion[tab] = false;
						}
					}
					//Save the start position and length of the color coding to the colorLength Dictionary
					if (this->nextPos[tab] != -1)
						colorLength[tab]->Add(this->pos[tab], this->nextPos[tab] - this->pos[tab]);
					else
						colorLength[tab]->Add(this->pos[tab], text->Length - this->pos[tab]);
					//Set the pos variable to the nextPos variable to process the next color code
					this->pos[tab] = this->nextPos[tab];
				}
				else {
					this->pos[tab] = this->pos[tab] + 1;
				}
			}
			catch (FormatException^) {
				this->pos[tab] = this->pos[tab] + 1;
			}
		}
		//Make sure the amount of lines does not exceed the max and delete lines if max has been reached
		int lines = (int)SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_GETLINECOUNT, 0, 0);
		if (lines >= this->maxLines) {
			this->outBox[tab]->Select(0, (int)SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_LINEINDEX, lines - this->maxLines + this->linesRemove + 1, 0));
			this->outBox[tab]->SelectedText = "";
		}
		//If color codes were found
		if (this->foundColor[tab]) {

			//Append the text without the color code keys to the output box
			//Apend text to the richtextbox with or without timestamp
			if (this->rconBooleans[10]) {
				this->outBox[tab]->AppendText(DateTime::Now.ToString(this->settingsArray[41]) + " " + text);
			}
			else
				this->outBox[tab]->AppendText(text);

			//Enumerate through the Dictionary values and color the text
			for each (KeyValuePair<Int32, Int32> colorCode in colorIndex[tab]) {
				this->outBox[tab]->Select(this->outBox[tab]->Text->Length - text->Length + colorCode.Key, colorLength[tab][colorCode.Key]);

				switch (colorCode.Value) {
				case 0:
					this->outBox[tab]->SelectionColor = ColorTranslator::FromHtml(this->settingsArray[25]); //Color::Black;
					break;
				case 1:
					this->outBox[tab]->SelectionColor = ColorTranslator::FromHtml(this->settingsArray[26]); //Color::Red;
					break;
				case 2:
					this->outBox[tab]->SelectionColor = ColorTranslator::FromHtml(this->settingsArray[27]); //Color::Green;
					break;
				case 3:
					this->outBox[tab]->SelectionColor = ColorTranslator::FromHtml(this->settingsArray[28]); //Color::Yellow;
					break;
				case 4:
					this->outBox[tab]->SelectionColor = ColorTranslator::FromHtml(this->settingsArray[29]); //Color::Blue;
					break;
				case 5:
					this->outBox[tab]->SelectionColor = ColorTranslator::FromHtml(this->settingsArray[30]); //Color::Cyan;
					break;
				case 6:
					this->outBox[tab]->SelectionColor = ColorTranslator::FromHtml(this->settingsArray[31]); //Color::Purple;
					break;
				case 7:
					this->outBox[tab]->SelectionColor = ColorTranslator::FromHtml(this->settingsArray[32]); //Color::White;
					break;
				case 8:
					this->outBox[tab]->SelectionColor = ColorTranslator::FromHtml(this->settingsArray[33]); //Color::Black;
					break;
				default:
					this->outBox[tab]->SelectionColor = ColorTranslator::FromHtml(this->settingsArray[32]); //Color::White;
					break;
				}
			}
		}
		else {
			//Apend text to the richtextbox with or without timestamp
			if (this->rconBooleans[10]) {
				this->outBox[tab]->AppendText(DateTime::Now.ToString(this->settingsArray[41]) + " " + text);
			}
			else
				this->outBox[tab]->AppendText(text);
		}
		this->outBox[tab]->Select(this->outBox[tab]->Text->Length, 0);

		//Scrolls the RichTextBox to the end to keep the last line shown (if scrolling is not disabled)
		if (!this->rconBooleans[2]) {
			try {
				//(commented line below scrolls 1 line at a time)
				//SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_LINESCROLL, 0, 1);
				//Gets the first visible line number and the line count and scrolls the linecount - the first visible line number - 34 (the smount of lines I counted on the screen)
				int currentLine = (int)SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_GETFIRSTVISIBLELINE, 0, 0);
				int lineCount = (int)SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_GETLINECOUNT, 0, 0);
				SendMessage(*reinterpret_cast<HWND *>(&this->outBox[tab]->Handle), EM_LINESCROLL, 0, lineCount - currentLine - 34);
			}
			catch (ObjectDisposedException^) {}
		}
		this->colorIndex[tab]->Clear();
		this->colorLength[tab]->Clear();
		//Perform Garbage colleciton on inaccessible memory
		GC::Collect();
	}
	return;
}

//builds logfile lines to be sent to the LogFile class (if server logging is enabled)
void QuakeLiveRcon::QLRcon::buildDisplayLine(int tab, String^ text, String^ displayLine, bool * printEntry) {
	*printEntry = false;
	//MessageBox::Show(text, "Message", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);

	if (!System::String::Compare(text->Substring(text->Length - 1), (L"\n")) && this->buildDisplayLines[tab]->Count == 0) {
		this->displayServerMessage(tab, text);
	}
	else {
		if (text->Length) {
			if (text->EndsWith("\n") || text->EndsWith("\r") || this->buildDisplayLines[tab]->Count > 25)
				*printEntry = true;

			this->buildDisplayLines[tab]->Add(text);

			if (*printEntry) {
				displayLine = gcnew String("");
				for each (String^ entry in this->buildDisplayLines[tab])
					displayLine += entry;

				this->buildDisplayLines[tab]->Clear();
				this->displayServerMessage(tab, displayLine);
				delete displayLine;
				displayLine = nullptr;
			}

		}
	}
	return;
}

//builds logfile lines to be sent to the LogFile class (if server logging is enabled)
void QuakeLiveRcon::QLRcon::buildLogFileLines(int tab, String^ text) {
	bool storeEntry = false;

	if (this->rconBooleans[1])
		text = this->stripColorCodes(text);

	if (!System::String::Compare(text->Substring(text->Length - 1), (L"\n")) && this->buildLines[tab]->Count == 0) {
		this->logServerWriter[tab]->storeEntry(text);
	}
	else {
		if (text->Length) {
			if (!System::String::Compare(text->Substring(text->Length - 1), (L"\n")) || this->buildLines[tab]->Count > 28)
				storeEntry = true;

			this->buildLines[tab]->Add(text);

			if (storeEntry) {
				String^ saveLine = "";
				for each (String^ entry in this->buildLines[tab])
					saveLine += entry;

				this->buildLines[tab]->Clear();
				this->logServerWriter[tab]->storeEntry(saveLine);
				delete saveLine;
			}

		}
	}
	return;
}

//Stris the Quake Style color codes from messages to be logged (strip color codes for logging is enabled)
String^ QuakeLiveRcon::QLRcon::stripColorCodes(String^ text) {
	String^ temp = text->Replace("^0", "");
	temp = temp->Replace("^1", "");
	temp = temp->Replace("^2", "");
	temp = temp->Replace("^3", "");
	temp = temp->Replace("^4", "");
	temp = temp->Replace("^5", "");
	temp = temp->Replace("^6", "");
	temp = temp->Replace("^7", "");
	temp = temp->Replace("^8", "");
	return temp;
}

void QuakeLiveRcon::QLRcon::serverTabConnection(int tab) {
	if (this->rconTabs->TabCount) {
		//disconnect from the server
		if (this->tabs[tab] == 1) {
			this->serverConnection(tab, L"disconnect");
			//Mark tab as disconnected but leave open
			this->tabs[tab] = -1;
			this->disconnectTab->Text = "Reconnect Current Tab";
		}
		//reconnect to the server
		else if (this->tabs[tab] == -1) {
			this->disconnect[tab] = false;
			this->logServer[tab] = this->ini->isTrue(this->savedServers[tab], "log");
			this->serverConnection(tab, L"connect");
			this->tabs[tab] = 1;
			this->disconnectTab->Text = "Disconnect Current Tab";
		}
	}
}

void QuakeLiveRcon::QLRcon::closeServerTab(int tab) {
	if (this->rconTabs->TabCount) {
		//disconnection from the server
		if (this->tabs[tab] == 1)
			this->serverConnection(tab, L"abort");
		this->commandEntries[tab] = 0;
		this->tabs[tab] = 0;
		this->tabLocation[tab] = -1;
		this->connectedServers[tab] = nullptr;
		this->removeTab(tab);
		this->clearCommandEntries(tab);
		//MessageBox::Show(System::Convert::ToString(this->rconTabs->TabCount), "Tab Count", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		if (this->rconTabs->TabCount) {
			this->updateTabLocations();
			this->activeTab = "{" + this->rconTabs->SelectedTab->Name + "}";
			this->updateServerTabInfo(this->getRconTabNumber(this->activeTab));
		}
		else {
			this->Controls->Remove(this->rconTabs);
			this->Controls->Add(this->notConnectedMessage);
			this->serverName->Text = L"Sever Name";
			this->IPLabel->Text = L"IP:Port";

			//Sets the system sleep settings back to default
			if (this->rconBooleans[4]) {
				SetThreadExecutionState(ES_CONTINUOUS);
				this->rconBooleans[4] = false;
			}
		}
	}
}

void QuakeLiveRcon::QLRcon::checkForOldFiles() {
	if (this->ini->getBoolean("main", "automaticFileDelete:enabled", false)) {
		int days = System::Convert::ToInt32(this->ini->getValue("main", "deleteDays", "30"));

		List<String^>^ exclusions = gcnew List<String^>();
		for each (String^ section in this->savedServers) {
			if (QuakeLiveRcon::ServersEdit::isServerIpPort(section) && this->ini->isTrue(section, "log")) {
				array<String^>^ sectionArray = section->Split(':');
				exclusions->Add(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
			}
		}
		LogFileWriter^ deleteFiles = gcnew LogFileWriter(LOG_FILE_LOCATION);
		deleteFiles->deleteOldFiles(DateTime::Now.AddDays(-(double)days), exclusions);
	}
}

void QuakeLiveRcon::QLRcon::addToSendCommands(int tab, String^ command) {
	currentInstance->addComandEntry(tab, command);
}
