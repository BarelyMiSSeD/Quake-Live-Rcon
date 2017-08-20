/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.5 on 8/20/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#pragma once

#pragma comment(lib, "rpcrt4.lib")  // UuidCreate - Minimum supported OS Win 2000
#pragma comment(lib, "user32.lib") //Used for ShellExecute
#include <winsock2.h>
#include <windows.h>

#include "ServersEdit.h"
#include "LogFileWriter.h"
#include "IniEditor.h"
#include "Settings.h"
#include "Status.h"
#include "Commands.h"
#include <zmq.h>
#include "msclr\marshal.h"

#define POLL_TIMEOUT 1
#define EVENT_ARRAY_SIZE 11

#define iniFile "QuakeLiveServers.ini"
#define MAX_SERVERS 20 //Amount of servers that can be connected at once (changing this requires more tabs to be created)
#define STORED_COMMANDS 10 //Amount of commands to be stored for each server tab (only requires changing this value here)
#define SETTINGS_ARRAY_SIZE 44 // amount of values stored from the ini file 'main' section
#define RCON_BOOLEANS 11 //Amount of Rcon Booleans used

ref class LogFileWriter;


namespace QuakeLiveRcon {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::ComponentModel;
	using namespace Newtonsoft::Json;

	/// <summary>
	/// Summary for QLRcon
	/// </summary>
	public ref class QLRcon : public System::Windows::Forms::Form {


	public: delegate void ObjectArgReturningVoidDelegate(int tab, String^ text);
	public: delegate void MessageArgReturningVoidDelegate(int tab, String^ text);

	private:
		//Variables
		String^ uuid;
		array<int>^ tabs; //will be used to track which tabs are in use (0 = not used, 1 = connected, -1 = not connected)
		array<int>^ tabLocation; //used to know what each tab page's index is
		array<int>^ commandEntries; //used to konw when an entry has been made in a tab command box
		array<String^>^ connectedServers; //store connected server names
		array<String^>^ serverNames; //store the names of the connected servers
		array<bool>^ logServer; //Stores logging state of server
		IniEditor^ ini; //Use the IniEditor.h to manage the server ini file
		List<String^>^ savedServers; // used to store the servers section IP:PORT of the ini file
		List<String^>^ keys; //used to store the keys of a section
		String^ activeTab; // store the active tab name
		array<String^, 2>^ commands; //used to store entered server commands on each tab
		array<String^, 2>^ sendCommands; //used to store the commands issued by the user on each tab
		array<char*>^ command; //used to store the next command from the sendCommands array
		array<String^>^ settingsArray; //used to store the programs settings in ini file 'main' settings
		static array<int, 1>^ eventKeys; //used for server zmq communication monitor status messages
		static array<String^, 1>^ eventNames; //used for server zmq communication monitor status messages
		array<bool>^ disconnect; //used to tell the zmq server communications loop when to exit
		array<System::Windows::Forms::TabPage^>^ serverTabs; //Rcon Tabs
		array<System::Windows::Forms::RichTextBox^>^ outBox; //Output text boxes
		array<System::Windows::Forms::TextBox^>^ inBox; //Input text boxes
		array<List<String^>^>^ buildDisplayLines; //used to build lines from the socket response before sending to get logged
		array<List<String^>^>^ buildLines; //used to build lines from the socket response before sending to get logged
		array<LogFileWriter^>^ logServerWriter; //used to store the LogFileWriter instances for the servers
		array<Thread^>^ serverConnectionThread; //used to store the threads for the active server connections
		int GamePortThreadTries; //used to make sure the killing of the game port thread does not go on indefinately (max of 10 tries)
		Thread^ GamePortThread; //Thread used to get the game port and call the Steam game launch link
		int maxLines; //used to store the max lines displayed value
		int linesRemove; //used to store the lines to remove from the display value
		String^ logFileName; //used to store logfile name for the r-mouse click Context Menu
		int rClickTab; //stores the tab number where the mouse r-click menu is being used
		int GameStatsThreadTries; //used to make sure the killing of the game port thread does not go on indefinately (max of 10 tries)
		Thread^ GameStatsThread; //Thread used to get the game port and call the Steam game launch link
		array<Thread^>^ statsConnectionThread; //used to store the threads for the active server stats connections
		int PlayerEventsThreadTries; //used to make sure the killing of the game port thread does not go on indefinately (max of 10 tries)
		array<String^, 2>^ statsConnectInfo; //used to store the server game port and stats password
		array<bool>^ rconBooleans; //Used to store all the enable/disable status
		/* RconBooleans Usage:
		0: Enable/Disable Logging
		1: Enable/Disable Strip Color codes for logging
		2: Enable/Disable auto scroll
		3: Enable/Disable Keep Alive
		4: Used to keep track of when the system is being 'kept alive'
		5: Enable/Disable gameEvents
		6: Enable/Disable Game killMessages
		7: Enable/Disable Game teamSwitch messages
		8: Enable/Disable Game Status Messages during Warmip
		9: Enable/Disable Game Player Medals Recieved Messages
		10: Enable/Disable Time Stamping of each line in the RCON Output window
		*/

		array<Dictionary<Int32, Int32>^>^ colorIndex; //array of dictionaries used to store color code locations on the output windows
		array<Dictionary<Int32, Int32>^>^ colorLength; //array of dictionaries used to store color code lengths on the output windows
		array<bool>^ foundColor; //used to store the status of the color code search for each tab		
		array<bool>^ conversion; //used to store the status of the color code conversion for each tab
		array<int>^ color;
		array<int>^ pos;
		array<int>^ nextPos;
		array<int>^ nextColor;
		array<QuakeLiveRcon::QLRcon::ObjectArgReturningVoidDelegate^>^ callAgain;
		array<QuakeLiveRcon::QLRcon::MessageArgReturningVoidDelegate^>^ msgAgain;

		///Context Menu shown on mouse r-click in server output windows
		System::Windows::Forms::ContextMenuStrip^ outputRClick;
		ToolStripMenuItem^ rClickItem1;
		ToolStripMenuItem^ rClickItem2;
		ToolStripMenuItem^ rClickItem3;
		ToolStripMenuItem^ rClickItem4;
		ToolStripMenuItem^ rClickItem5;
		ToolStripMenuItem^ rClickItem6;
		//ToolStripMenuItem^ rClickItem7;

		static QLRcon^ currentInstance; //keep instance of the main form


	public: QLRcon(void);

			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
	protected: ~QLRcon();

	private: System::Windows::Forms::TabControl^  rconTabs;
	private: System::Windows::Forms::TabPage^  rcon0;
	private: System::Windows::Forms::RichTextBox^  output0;
	private: System::Windows::Forms::TextBox^  input0;
	private: System::Windows::Forms::TabPage^  rcon1;
	private: System::Windows::Forms::RichTextBox^  output1;
	private: System::Windows::Forms::TextBox^  input1;
	private: System::Windows::Forms::TabPage^  rcon2;
	private: System::Windows::Forms::RichTextBox^  output2;
	private: System::Windows::Forms::TextBox^  input2;
	private: System::Windows::Forms::TabPage^  rcon3;
	private: System::Windows::Forms::RichTextBox^  output3;
	private: System::Windows::Forms::TextBox^  input3;
	private: System::Windows::Forms::TabPage^  rcon4;
	private: System::Windows::Forms::RichTextBox^  output4;
	private: System::Windows::Forms::TextBox^  input4;
	private: System::Windows::Forms::TabPage^  rcon5;
	private: System::Windows::Forms::RichTextBox^  output5;
	private: System::Windows::Forms::TextBox^  input5;
	private: System::Windows::Forms::TabPage^  rcon6;
	private: System::Windows::Forms::RichTextBox^  output6;
	private: System::Windows::Forms::TextBox^  input6;
	private: System::Windows::Forms::TabPage^  rcon7;
	private: System::Windows::Forms::RichTextBox^  output7;
	private: System::Windows::Forms::TextBox^  input7;
	private: System::Windows::Forms::TabPage^  rcon8;
	private: System::Windows::Forms::RichTextBox^  output8;
	private: System::Windows::Forms::TextBox^  input8;
	private: System::Windows::Forms::TabPage^  rcon9;
	private: System::Windows::Forms::RichTextBox^  output9;
	private: System::Windows::Forms::TextBox^  input9;
	private: System::Windows::Forms::TabPage^  rcon10;
	private: System::Windows::Forms::RichTextBox^  output10;
	private: System::Windows::Forms::TextBox^  input10;
	private: System::Windows::Forms::TabPage^  rcon11;
	private: System::Windows::Forms::RichTextBox^  output11;
	private: System::Windows::Forms::TextBox^  input11;
	private: System::Windows::Forms::TabPage^  rcon12;
	private: System::Windows::Forms::RichTextBox^  output12;
	private: System::Windows::Forms::TextBox^  input12;
	private: System::Windows::Forms::TabPage^  rcon13;
	private: System::Windows::Forms::RichTextBox^  output13;
	private: System::Windows::Forms::TextBox^  input13;
	private: System::Windows::Forms::TabPage^  rcon14;
	private: System::Windows::Forms::RichTextBox^  output14;
	private: System::Windows::Forms::TextBox^  input14;
	private: System::Windows::Forms::TabPage^  rcon15;
	private: System::Windows::Forms::RichTextBox^  output15;
	private: System::Windows::Forms::TextBox^  input15;
	private: System::Windows::Forms::TabPage^  rcon16;
	private: System::Windows::Forms::RichTextBox^  output16;
	private: System::Windows::Forms::TextBox^  input16;
	private: System::Windows::Forms::TabPage^  rcon17;
	private: System::Windows::Forms::RichTextBox^  output17;
	private: System::Windows::Forms::TextBox^  input17;
	private: System::Windows::Forms::TabPage^  rcon18;
	private: System::Windows::Forms::RichTextBox^  output18;
	private: System::Windows::Forms::TextBox^  input18;
	private: System::Windows::Forms::TabPage^  rcon19;
	private: System::Windows::Forms::RichTextBox^  output19;
	private: System::Windows::Forms::TextBox^  input19;
	private: System::Windows::Forms::Button^  editServers;
	private: System::Windows::Forms::ComboBox^  serverList;
	private: System::Windows::Forms::Button^  connect;
	private: System::Windows::Forms::Button^  disconnectTab;
	private: System::Windows::Forms::Button^  closeTab;
	private: System::Windows::Forms::Button^  exit;
	private: System::Windows::Forms::Label^  serverName;
	private: System::Windows::Forms::Label^  IPLabel;
	private: System::Windows::Forms::TextBox^  notConnectedMessage;
	private: System::Windows::Forms::Button^  settings;
	private: System::Windows::Forms::Button^  command1;
	private: System::Windows::Forms::Button^  command2;
	private: System::Windows::Forms::Button^  command3;
	private: System::Windows::Forms::Button^  command4;
	private: System::Windows::Forms::Button^  command5;
	private: System::Windows::Forms::Button^  command6;
	private: System::Windows::Forms::Button^  connectGame;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void) {
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(QLRcon::typeid));
			this->rconTabs = (gcnew System::Windows::Forms::TabControl());
			this->rcon0 = (gcnew System::Windows::Forms::TabPage());
			this->output0 = (gcnew System::Windows::Forms::RichTextBox());
			this->input0 = (gcnew System::Windows::Forms::TextBox());
			this->rcon1 = (gcnew System::Windows::Forms::TabPage());
			this->output1 = (gcnew System::Windows::Forms::RichTextBox());
			this->input1 = (gcnew System::Windows::Forms::TextBox());
			this->rcon2 = (gcnew System::Windows::Forms::TabPage());
			this->output2 = (gcnew System::Windows::Forms::RichTextBox());
			this->input2 = (gcnew System::Windows::Forms::TextBox());
			this->rcon3 = (gcnew System::Windows::Forms::TabPage());
			this->output3 = (gcnew System::Windows::Forms::RichTextBox());
			this->input3 = (gcnew System::Windows::Forms::TextBox());
			this->rcon4 = (gcnew System::Windows::Forms::TabPage());
			this->output4 = (gcnew System::Windows::Forms::RichTextBox());
			this->input4 = (gcnew System::Windows::Forms::TextBox());
			this->rcon5 = (gcnew System::Windows::Forms::TabPage());
			this->output5 = (gcnew System::Windows::Forms::RichTextBox());
			this->input5 = (gcnew System::Windows::Forms::TextBox());
			this->rcon6 = (gcnew System::Windows::Forms::TabPage());
			this->output6 = (gcnew System::Windows::Forms::RichTextBox());
			this->input6 = (gcnew System::Windows::Forms::TextBox());
			this->rcon7 = (gcnew System::Windows::Forms::TabPage());
			this->output7 = (gcnew System::Windows::Forms::RichTextBox());
			this->input7 = (gcnew System::Windows::Forms::TextBox());
			this->rcon8 = (gcnew System::Windows::Forms::TabPage());
			this->output8 = (gcnew System::Windows::Forms::RichTextBox());
			this->input8 = (gcnew System::Windows::Forms::TextBox());
			this->rcon9 = (gcnew System::Windows::Forms::TabPage());
			this->output9 = (gcnew System::Windows::Forms::RichTextBox());
			this->input9 = (gcnew System::Windows::Forms::TextBox());
			this->rcon10 = (gcnew System::Windows::Forms::TabPage());
			this->output10 = (gcnew System::Windows::Forms::RichTextBox());
			this->input10 = (gcnew System::Windows::Forms::TextBox());
			this->rcon11 = (gcnew System::Windows::Forms::TabPage());
			this->output11 = (gcnew System::Windows::Forms::RichTextBox());
			this->input11 = (gcnew System::Windows::Forms::TextBox());
			this->rcon12 = (gcnew System::Windows::Forms::TabPage());
			this->output12 = (gcnew System::Windows::Forms::RichTextBox());
			this->input12 = (gcnew System::Windows::Forms::TextBox());
			this->rcon13 = (gcnew System::Windows::Forms::TabPage());
			this->output13 = (gcnew System::Windows::Forms::RichTextBox());
			this->input13 = (gcnew System::Windows::Forms::TextBox());
			this->rcon14 = (gcnew System::Windows::Forms::TabPage());
			this->output14 = (gcnew System::Windows::Forms::RichTextBox());
			this->input14 = (gcnew System::Windows::Forms::TextBox());
			this->rcon15 = (gcnew System::Windows::Forms::TabPage());
			this->output15 = (gcnew System::Windows::Forms::RichTextBox());
			this->input15 = (gcnew System::Windows::Forms::TextBox());
			this->rcon16 = (gcnew System::Windows::Forms::TabPage());
			this->output16 = (gcnew System::Windows::Forms::RichTextBox());
			this->input16 = (gcnew System::Windows::Forms::TextBox());
			this->rcon17 = (gcnew System::Windows::Forms::TabPage());
			this->output17 = (gcnew System::Windows::Forms::RichTextBox());
			this->input17 = (gcnew System::Windows::Forms::TextBox());
			this->rcon18 = (gcnew System::Windows::Forms::TabPage());
			this->output18 = (gcnew System::Windows::Forms::RichTextBox());
			this->input18 = (gcnew System::Windows::Forms::TextBox());
			this->rcon19 = (gcnew System::Windows::Forms::TabPage());
			this->output19 = (gcnew System::Windows::Forms::RichTextBox());
			this->input19 = (gcnew System::Windows::Forms::TextBox());
			this->editServers = (gcnew System::Windows::Forms::Button());
			this->serverList = (gcnew System::Windows::Forms::ComboBox());
			this->connect = (gcnew System::Windows::Forms::Button());
			this->disconnectTab = (gcnew System::Windows::Forms::Button());
			this->closeTab = (gcnew System::Windows::Forms::Button());
			this->exit = (gcnew System::Windows::Forms::Button());
			this->serverName = (gcnew System::Windows::Forms::Label());
			this->IPLabel = (gcnew System::Windows::Forms::Label());
			this->notConnectedMessage = (gcnew System::Windows::Forms::TextBox());
			this->settings = (gcnew System::Windows::Forms::Button());
			this->command1 = (gcnew System::Windows::Forms::Button());
			this->command2 = (gcnew System::Windows::Forms::Button());
			this->command3 = (gcnew System::Windows::Forms::Button());
			this->command4 = (gcnew System::Windows::Forms::Button());
			this->command5 = (gcnew System::Windows::Forms::Button());
			this->command6 = (gcnew System::Windows::Forms::Button());
			this->connectGame = (gcnew System::Windows::Forms::Button());
			this->rcon0->SuspendLayout();
			this->rcon1->SuspendLayout();
			this->rcon2->SuspendLayout();
			this->rcon3->SuspendLayout();
			this->rcon4->SuspendLayout();
			this->rcon5->SuspendLayout();
			this->rcon6->SuspendLayout();
			this->rcon7->SuspendLayout();
			this->rcon8->SuspendLayout();
			this->rcon9->SuspendLayout();
			this->rcon10->SuspendLayout();
			this->rcon11->SuspendLayout();
			this->rcon12->SuspendLayout();
			this->rcon13->SuspendLayout();
			this->rcon14->SuspendLayout();
			this->rcon15->SuspendLayout();
			this->rcon16->SuspendLayout();
			this->rcon17->SuspendLayout();
			this->rcon18->SuspendLayout();
			this->rcon19->SuspendLayout();
			this->SuspendLayout();
			// 
			// rconTabs
			// 
			this->rconTabs->Location = System::Drawing::Point(0, 92);
			this->rconTabs->Name = L"rconTabs";
			this->rconTabs->SelectedIndex = 0;
			this->rconTabs->Size = System::Drawing::Size(1083, 600);
			this->rconTabs->TabIndex = 0;
			this->rconTabs->Click += gcnew System::EventHandler(this, &QLRcon::rconTabs_Click);
			// 
			// rcon0
			// 
			this->rcon0->Controls->Add(this->output0);
			this->rcon0->Controls->Add(this->input0);
			this->rcon0->Location = System::Drawing::Point(4, 22);
			this->rcon0->Name = L"rcon0";
			this->rcon0->Size = System::Drawing::Size(1075, 574);
			this->rcon0->TabIndex = 0;
			this->rcon0->Text = L"rcon0";
			this->rcon0->UseVisualStyleBackColor = true;
			// 
			// output0
			// 
			this->output0->BackColor = System::Drawing::Color::Black;
			this->output0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output0->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output0->Location = System::Drawing::Point(0, 0);
			this->output0->Name = L"output0";
			this->output0->Size = System::Drawing::Size(1075, 551);
			this->output0->TabIndex = 1;
			this->output0->Text = L"";
			this->output0->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output0_KeyDown);
			this->output0->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output0_KeyPress);
			this->output0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output0_MouseDown);
			// 
			// input0
			// 
			this->input0->AcceptsReturn = true;
			this->input0->BackColor = System::Drawing::Color::Black;
			this->input0->ForeColor = System::Drawing::Color::White;
			this->input0->Location = System::Drawing::Point(0, 554);
			this->input0->Name = L"input0";
			this->input0->Size = System::Drawing::Size(1075, 20);
			this->input0->TabIndex = 0;
			this->input0->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input0->WordWrap = false;
			this->input0->Click += gcnew System::EventHandler(this, &QLRcon::input0_Click);
			this->input0->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input0_KeyDown);
			this->input0->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input0_KeyPress);
			// 
			// rcon1
			// 
			this->rcon1->Controls->Add(this->output1);
			this->rcon1->Controls->Add(this->input1);
			this->rcon1->ForeColor = System::Drawing::Color::Gray;
			this->rcon1->Location = System::Drawing::Point(4, 22);
			this->rcon1->Name = L"rcon1";
			this->rcon1->Padding = System::Windows::Forms::Padding(3);
			this->rcon1->Size = System::Drawing::Size(1075, 574);
			this->rcon1->TabIndex = 1;
			this->rcon1->Text = L"rcon1";
			// 
			// output1
			// 
			this->output1->BackColor = System::Drawing::Color::Black;
			this->output1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output1->Location = System::Drawing::Point(0, 0);
			this->output1->Name = L"output1";
			this->output1->Size = System::Drawing::Size(1075, 551);
			this->output1->TabIndex = 1;
			this->output1->Text = L"";
			this->output1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output1_KeyDown);
			this->output1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output1_KeyPress);
			this->output1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output1_MouseDown);
			// 
			// input1
			// 
			this->input1->AcceptsReturn = true;
			this->input1->BackColor = System::Drawing::Color::Black;
			this->input1->ForeColor = System::Drawing::Color::White;
			this->input1->Location = System::Drawing::Point(0, 554);
			this->input1->Name = L"input1";
			this->input1->Size = System::Drawing::Size(1075, 20);
			this->input1->TabIndex = 1;
			this->input1->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input1->Click += gcnew System::EventHandler(this, &QLRcon::input1_Click);
			this->input1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input1_KeyDown);
			this->input1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input1_KeyPress);
			// 
			// rcon2
			// 
			this->rcon2->Controls->Add(this->output2);
			this->rcon2->Controls->Add(this->input2);
			this->rcon2->Location = System::Drawing::Point(4, 22);
			this->rcon2->Name = L"rcon2";
			this->rcon2->Padding = System::Windows::Forms::Padding(3);
			this->rcon2->Size = System::Drawing::Size(1075, 574);
			this->rcon2->TabIndex = 2;
			this->rcon2->Text = L"rcon2";
			this->rcon2->UseVisualStyleBackColor = true;
			// 
			// output2
			// 
			this->output2->BackColor = System::Drawing::Color::Black;
			this->output2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output2->Location = System::Drawing::Point(0, 0);
			this->output2->Name = L"output2";
			this->output2->Size = System::Drawing::Size(1075, 551);
			this->output2->TabIndex = 2;
			this->output2->Text = L"";
			this->output2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output2_KeyDown);
			this->output2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output2_KeyPress);
			this->output2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output2_MouseDown);
			// 
			// input2
			// 
			this->input2->AcceptsReturn = true;
			this->input2->BackColor = System::Drawing::Color::Black;
			this->input2->ForeColor = System::Drawing::Color::White;
			this->input2->Location = System::Drawing::Point(0, 554);
			this->input2->Name = L"input2";
			this->input2->Size = System::Drawing::Size(1075, 20);
			this->input2->TabIndex = 2;
			this->input2->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input2->Click += gcnew System::EventHandler(this, &QLRcon::input2_Click);
			this->input2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input2_KeyDown);
			this->input2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input2_KeyPress);
			// 
			// rcon3
			// 
			this->rcon3->Controls->Add(this->output3);
			this->rcon3->Controls->Add(this->input3);
			this->rcon3->Location = System::Drawing::Point(4, 22);
			this->rcon3->Name = L"rcon3";
			this->rcon3->Size = System::Drawing::Size(1075, 574);
			this->rcon3->TabIndex = 3;
			this->rcon3->Text = L"rcon3";
			this->rcon3->UseVisualStyleBackColor = true;
			// 
			// output3
			// 
			this->output3->BackColor = System::Drawing::Color::Black;
			this->output3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output3->Location = System::Drawing::Point(0, 0);
			this->output3->Name = L"output3";
			this->output3->Size = System::Drawing::Size(1075, 551);
			this->output3->TabIndex = 3;
			this->output3->Text = L"";
			this->output3->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output3_KeyDown);
			this->output3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output3_KeyPress);
			this->output3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output3_MouseDown);
			// 
			// input3
			// 
			this->input3->AcceptsReturn = true;
			this->input3->BackColor = System::Drawing::Color::Black;
			this->input3->ForeColor = System::Drawing::Color::White;
			this->input3->Location = System::Drawing::Point(0, 554);
			this->input3->Name = L"input3";
			this->input3->Size = System::Drawing::Size(1075, 20);
			this->input3->TabIndex = 3;
			this->input3->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input3->Click += gcnew System::EventHandler(this, &QLRcon::input3_Click);
			this->input3->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input3_KeyDown);
			this->input3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input3_KeyPress);
			// 
			// rcon4
			// 
			this->rcon4->Controls->Add(this->output4);
			this->rcon4->Controls->Add(this->input4);
			this->rcon4->Location = System::Drawing::Point(4, 22);
			this->rcon4->Name = L"rcon4";
			this->rcon4->Size = System::Drawing::Size(1075, 574);
			this->rcon4->TabIndex = 4;
			this->rcon4->Text = L"rcon4";
			this->rcon4->UseVisualStyleBackColor = true;
			// 
			// output4
			// 
			this->output4->BackColor = System::Drawing::Color::Black;
			this->output4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output4->Location = System::Drawing::Point(0, 0);
			this->output4->Name = L"output4";
			this->output4->Size = System::Drawing::Size(1075, 551);
			this->output4->TabIndex = 4;
			this->output4->Text = L"";
			this->output4->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output4_KeyDown);
			this->output4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output4_KeyPress);
			this->output4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output4_MouseDown);
			// 
			// input4
			// 
			this->input4->AcceptsReturn = true;
			this->input4->BackColor = System::Drawing::Color::Black;
			this->input4->ForeColor = System::Drawing::Color::White;
			this->input4->Location = System::Drawing::Point(0, 554);
			this->input4->Name = L"input4";
			this->input4->Size = System::Drawing::Size(1075, 20);
			this->input4->TabIndex = 4;
			this->input4->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input4->Click += gcnew System::EventHandler(this, &QLRcon::input4_Click);
			this->input4->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input4_KeyDown);
			this->input4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input4_KeyPress);
			// 
			// rcon5
			// 
			this->rcon5->Controls->Add(this->output5);
			this->rcon5->Controls->Add(this->input5);
			this->rcon5->Location = System::Drawing::Point(4, 22);
			this->rcon5->Name = L"rcon5";
			this->rcon5->Size = System::Drawing::Size(1075, 574);
			this->rcon5->TabIndex = 5;
			this->rcon5->Text = L"rcon5";
			this->rcon5->UseVisualStyleBackColor = true;
			// 
			// output5
			// 
			this->output5->BackColor = System::Drawing::Color::Black;
			this->output5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output5->Location = System::Drawing::Point(0, 0);
			this->output5->Name = L"output5";
			this->output5->Size = System::Drawing::Size(1075, 551);
			this->output5->TabIndex = 5;
			this->output5->Text = L"";
			this->output5->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output5_KeyDown);
			this->output5->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output5_KeyPress);
			this->output5->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output5_MouseDown);
			// 
			// input5
			// 
			this->input5->AcceptsReturn = true;
			this->input5->BackColor = System::Drawing::Color::Black;
			this->input5->ForeColor = System::Drawing::Color::White;
			this->input5->Location = System::Drawing::Point(0, 554);
			this->input5->Name = L"input5";
			this->input5->Size = System::Drawing::Size(1075, 20);
			this->input5->TabIndex = 5;
			this->input5->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input5->Click += gcnew System::EventHandler(this, &QLRcon::input5_Click);
			this->input5->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input5_KeyDown);
			this->input5->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input5_KeyPress);
			// 
			// rcon6
			// 
			this->rcon6->Controls->Add(this->output6);
			this->rcon6->Controls->Add(this->input6);
			this->rcon6->Location = System::Drawing::Point(4, 22);
			this->rcon6->Name = L"rcon6";
			this->rcon6->Size = System::Drawing::Size(1075, 574);
			this->rcon6->TabIndex = 6;
			this->rcon6->Text = L"rcon6";
			this->rcon6->UseVisualStyleBackColor = true;
			// 
			// output6
			// 
			this->output6->BackColor = System::Drawing::Color::Black;
			this->output6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output6->Location = System::Drawing::Point(0, 0);
			this->output6->Name = L"output6";
			this->output6->Size = System::Drawing::Size(1075, 551);
			this->output6->TabIndex = 6;
			this->output6->Text = L"";
			this->output6->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output6_KeyDown);
			this->output6->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output6_KeyPress);
			this->output6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output6_MouseDown);
			// 
			// input6
			// 
			this->input6->AcceptsReturn = true;
			this->input6->BackColor = System::Drawing::Color::Black;
			this->input6->ForeColor = System::Drawing::Color::White;
			this->input6->Location = System::Drawing::Point(0, 554);
			this->input6->Name = L"input6";
			this->input6->Size = System::Drawing::Size(1075, 20);
			this->input6->TabIndex = 6;
			this->input6->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input6->Click += gcnew System::EventHandler(this, &QLRcon::input6_Click);
			this->input6->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input6_KeyDown);
			this->input6->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input6_KeyPress);
			// 
			// rcon7
			// 
			this->rcon7->Controls->Add(this->output7);
			this->rcon7->Controls->Add(this->input7);
			this->rcon7->Location = System::Drawing::Point(4, 22);
			this->rcon7->Name = L"rcon7";
			this->rcon7->Size = System::Drawing::Size(1075, 574);
			this->rcon7->TabIndex = 7;
			this->rcon7->Text = L"rcon7";
			this->rcon7->UseVisualStyleBackColor = true;
			// 
			// output7
			// 
			this->output7->BackColor = System::Drawing::Color::Black;
			this->output7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output7->Location = System::Drawing::Point(0, 0);
			this->output7->Name = L"output7";
			this->output7->Size = System::Drawing::Size(1075, 551);
			this->output7->TabIndex = 7;
			this->output7->Text = L"";
			this->output7->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output7_KeyDown);
			this->output7->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output7_KeyPress);
			this->output7->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output7_MouseDown);
			// 
			// input7
			// 
			this->input7->AcceptsReturn = true;
			this->input7->BackColor = System::Drawing::Color::Black;
			this->input7->ForeColor = System::Drawing::Color::White;
			this->input7->Location = System::Drawing::Point(0, 554);
			this->input7->Name = L"input7";
			this->input7->Size = System::Drawing::Size(1075, 20);
			this->input7->TabIndex = 7;
			this->input7->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input7->Click += gcnew System::EventHandler(this, &QLRcon::input7_Click);
			this->input7->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input7_KeyDown);
			this->input7->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input7_KeyPress);
			// 
			// rcon8
			// 
			this->rcon8->Controls->Add(this->output8);
			this->rcon8->Controls->Add(this->input8);
			this->rcon8->Location = System::Drawing::Point(4, 22);
			this->rcon8->Name = L"rcon8";
			this->rcon8->Size = System::Drawing::Size(1075, 574);
			this->rcon8->TabIndex = 8;
			this->rcon8->Text = L"rcon8";
			this->rcon8->UseVisualStyleBackColor = true;
			// 
			// output8
			// 
			this->output8->BackColor = System::Drawing::Color::Black;
			this->output8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output8->Location = System::Drawing::Point(0, 0);
			this->output8->Name = L"output8";
			this->output8->Size = System::Drawing::Size(1075, 551);
			this->output8->TabIndex = 8;
			this->output8->Text = L"";
			this->output8->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output8_KeyDown);
			this->output8->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output8_KeyPress);
			this->output8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output8_MouseDown);
			// 
			// input8
			// 
			this->input8->AcceptsReturn = true;
			this->input8->BackColor = System::Drawing::Color::Black;
			this->input8->ForeColor = System::Drawing::Color::White;
			this->input8->Location = System::Drawing::Point(0, 554);
			this->input8->Name = L"input8";
			this->input8->Size = System::Drawing::Size(1075, 20);
			this->input8->TabIndex = 8;
			this->input8->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input8->Click += gcnew System::EventHandler(this, &QLRcon::input8_Click);
			this->input8->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input8_KeyDown);
			this->input8->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input8_KeyPress);
			// 
			// rcon9
			// 
			this->rcon9->Controls->Add(this->output9);
			this->rcon9->Controls->Add(this->input9);
			this->rcon9->Location = System::Drawing::Point(4, 22);
			this->rcon9->Name = L"rcon9";
			this->rcon9->Size = System::Drawing::Size(1075, 574);
			this->rcon9->TabIndex = 9;
			this->rcon9->Text = L"rcon9";
			this->rcon9->UseVisualStyleBackColor = true;
			// 
			// output9
			// 
			this->output9->BackColor = System::Drawing::Color::Black;
			this->output9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output9->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output9->Location = System::Drawing::Point(0, 0);
			this->output9->Name = L"output9";
			this->output9->Size = System::Drawing::Size(1075, 551);
			this->output9->TabIndex = 9;
			this->output9->Text = L"";
			this->output9->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output9_KeyDown);
			this->output9->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output9_KeyPress);
			this->output9->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output9_MouseDown);
			// 
			// input9
			// 
			this->input9->AcceptsReturn = true;
			this->input9->BackColor = System::Drawing::Color::Black;
			this->input9->ForeColor = System::Drawing::Color::White;
			this->input9->Location = System::Drawing::Point(0, 554);
			this->input9->Name = L"input9";
			this->input9->Size = System::Drawing::Size(1075, 20);
			this->input9->TabIndex = 9;
			this->input9->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input9->Click += gcnew System::EventHandler(this, &QLRcon::input9_Click);
			this->input9->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input9_KeyDown);
			this->input9->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input9_KeyPress);
			// 
			// rcon10
			// 
			this->rcon10->Controls->Add(this->output10);
			this->rcon10->Controls->Add(this->input10);
			this->rcon10->Location = System::Drawing::Point(4, 22);
			this->rcon10->Name = L"rcon10";
			this->rcon10->Size = System::Drawing::Size(1075, 574);
			this->rcon10->TabIndex = 10;
			this->rcon10->Text = L"rcon10";
			this->rcon10->UseVisualStyleBackColor = true;
			// 
			// output10
			// 
			this->output10->BackColor = System::Drawing::Color::Black;
			this->output10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output10->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output10->Location = System::Drawing::Point(0, 0);
			this->output10->Name = L"output10";
			this->output10->Size = System::Drawing::Size(1075, 551);
			this->output10->TabIndex = 10;
			this->output10->Text = L"";
			this->output10->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output10_KeyDown);
			this->output10->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output10_KeyPress);
			this->output10->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output10_MouseDown);
			// 
			// input10
			// 
			this->input10->AcceptsReturn = true;
			this->input10->BackColor = System::Drawing::Color::Black;
			this->input10->ForeColor = System::Drawing::Color::White;
			this->input10->Location = System::Drawing::Point(0, 554);
			this->input10->Name = L"input10";
			this->input10->Size = System::Drawing::Size(1075, 20);
			this->input10->TabIndex = 10;
			this->input10->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input10->Click += gcnew System::EventHandler(this, &QLRcon::input10_Click);
			this->input10->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input10_KeyDown);
			this->input10->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input10_KeyPress);
			// 
			// rcon11
			// 
			this->rcon11->Controls->Add(this->output11);
			this->rcon11->Controls->Add(this->input11);
			this->rcon11->Location = System::Drawing::Point(4, 22);
			this->rcon11->Name = L"rcon11";
			this->rcon11->Size = System::Drawing::Size(1075, 574);
			this->rcon11->TabIndex = 11;
			this->rcon11->Text = L"rcon11";
			this->rcon11->UseVisualStyleBackColor = true;
			// 
			// output11
			// 
			this->output11->BackColor = System::Drawing::Color::Black;
			this->output11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output11->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output11->Location = System::Drawing::Point(0, 0);
			this->output11->Name = L"output11";
			this->output11->Size = System::Drawing::Size(1075, 551);
			this->output11->TabIndex = 11;
			this->output11->Text = L"";
			this->output11->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output11_KeyDown);
			this->output11->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output11_KeyPress);
			this->output11->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output11_MouseDown);
			// 
			// input11
			// 
			this->input11->AcceptsReturn = true;
			this->input11->BackColor = System::Drawing::Color::Black;
			this->input11->ForeColor = System::Drawing::Color::White;
			this->input11->Location = System::Drawing::Point(0, 554);
			this->input11->Name = L"input11";
			this->input11->Size = System::Drawing::Size(1075, 20);
			this->input11->TabIndex = 11;
			this->input11->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input11->Click += gcnew System::EventHandler(this, &QLRcon::input11_Click);
			this->input11->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input11_KeyDown);
			this->input11->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input11_KeyPress);
			// 
			// rcon12
			// 
			this->rcon12->Controls->Add(this->output12);
			this->rcon12->Controls->Add(this->input12);
			this->rcon12->Location = System::Drawing::Point(4, 22);
			this->rcon12->Name = L"rcon12";
			this->rcon12->Size = System::Drawing::Size(1075, 574);
			this->rcon12->TabIndex = 12;
			this->rcon12->Text = L"rcon12";
			this->rcon12->UseVisualStyleBackColor = true;
			// 
			// output12
			// 
			this->output12->BackColor = System::Drawing::Color::Black;
			this->output12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output12->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output12->Location = System::Drawing::Point(0, 0);
			this->output12->Name = L"output12";
			this->output12->Size = System::Drawing::Size(1075, 551);
			this->output12->TabIndex = 12;
			this->output12->Text = L"";
			this->output12->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output12_KeyDown);
			this->output12->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output12_KeyPress);
			this->output12->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output12_MouseDown);
			// 
			// input12
			// 
			this->input12->AcceptsReturn = true;
			this->input12->BackColor = System::Drawing::Color::Black;
			this->input12->ForeColor = System::Drawing::Color::White;
			this->input12->Location = System::Drawing::Point(0, 554);
			this->input12->Name = L"input12";
			this->input12->Size = System::Drawing::Size(1075, 20);
			this->input12->TabIndex = 12;
			this->input12->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input12->Click += gcnew System::EventHandler(this, &QLRcon::input12_Click);
			this->input12->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input12_KeyDown);
			this->input12->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input12_KeyPress);
			// 
			// rcon13
			// 
			this->rcon13->Controls->Add(this->output13);
			this->rcon13->Controls->Add(this->input13);
			this->rcon13->Location = System::Drawing::Point(4, 22);
			this->rcon13->Name = L"rcon13";
			this->rcon13->Size = System::Drawing::Size(1075, 574);
			this->rcon13->TabIndex = 13;
			this->rcon13->Text = L"rcon13";
			this->rcon13->UseVisualStyleBackColor = true;
			// 
			// output13
			// 
			this->output13->BackColor = System::Drawing::Color::Black;
			this->output13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output13->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output13->Location = System::Drawing::Point(0, 0);
			this->output13->Name = L"output13";
			this->output13->Size = System::Drawing::Size(1075, 551);
			this->output13->TabIndex = 13;
			this->output13->Text = L"";
			this->output13->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output13_KeyDown);
			this->output13->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output13_KeyPress);
			this->output13->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output13_MouseDown);
			// 
			// input13
			// 
			this->input13->AcceptsReturn = true;
			this->input13->BackColor = System::Drawing::Color::Black;
			this->input13->ForeColor = System::Drawing::Color::White;
			this->input13->Location = System::Drawing::Point(0, 554);
			this->input13->Name = L"input13";
			this->input13->Size = System::Drawing::Size(1075, 20);
			this->input13->TabIndex = 13;
			this->input13->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input13->Click += gcnew System::EventHandler(this, &QLRcon::input13_Click);
			this->input13->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input13_KeyDown);
			this->input13->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input13_KeyPress);
			// 
			// rcon14
			// 
			this->rcon14->Controls->Add(this->output14);
			this->rcon14->Controls->Add(this->input14);
			this->rcon14->Location = System::Drawing::Point(4, 22);
			this->rcon14->Name = L"rcon14";
			this->rcon14->Size = System::Drawing::Size(1075, 574);
			this->rcon14->TabIndex = 14;
			this->rcon14->Text = L"rcon14";
			this->rcon14->UseVisualStyleBackColor = true;
			// 
			// output14
			// 
			this->output14->BackColor = System::Drawing::Color::Black;
			this->output14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output14->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output14->Location = System::Drawing::Point(0, 0);
			this->output14->Name = L"output14";
			this->output14->Size = System::Drawing::Size(1075, 551);
			this->output14->TabIndex = 14;
			this->output14->Text = L"";
			this->output14->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output14_KeyDown);
			this->output14->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output14_KeyPress);
			this->output14->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output14_MouseDown);
			// 
			// input14
			// 
			this->input14->AcceptsReturn = true;
			this->input14->BackColor = System::Drawing::Color::Black;
			this->input14->ForeColor = System::Drawing::Color::White;
			this->input14->Location = System::Drawing::Point(0, 554);
			this->input14->Name = L"input14";
			this->input14->Size = System::Drawing::Size(1075, 20);
			this->input14->TabIndex = 14;
			this->input14->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input14->Click += gcnew System::EventHandler(this, &QLRcon::input14_Click);
			this->input14->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input14_KeyDown);
			this->input14->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input14_KeyPress);
			// 
			// rcon15
			// 
			this->rcon15->Controls->Add(this->output15);
			this->rcon15->Controls->Add(this->input15);
			this->rcon15->Location = System::Drawing::Point(4, 22);
			this->rcon15->Name = L"rcon15";
			this->rcon15->Size = System::Drawing::Size(1075, 574);
			this->rcon15->TabIndex = 15;
			this->rcon15->Text = L"rcon15";
			this->rcon15->UseVisualStyleBackColor = true;
			// 
			// output15
			// 
			this->output15->BackColor = System::Drawing::Color::Black;
			this->output15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output15->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output15->Location = System::Drawing::Point(0, 0);
			this->output15->Name = L"output15";
			this->output15->Size = System::Drawing::Size(1075, 551);
			this->output15->TabIndex = 15;
			this->output15->Text = L"";
			this->output15->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output15_KeyDown);
			this->output15->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output15_KeyPress);
			this->output15->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output15_MouseDown);
			// 
			// input15
			// 
			this->input15->AcceptsReturn = true;
			this->input15->BackColor = System::Drawing::Color::Black;
			this->input15->ForeColor = System::Drawing::Color::White;
			this->input15->Location = System::Drawing::Point(0, 554);
			this->input15->Name = L"input15";
			this->input15->Size = System::Drawing::Size(1075, 20);
			this->input15->TabIndex = 15;
			this->input15->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input15->Click += gcnew System::EventHandler(this, &QLRcon::input15_Click);
			this->input15->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input15_KeyDown);
			this->input15->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input15_KeyPress);
			// 
			// rcon16
			// 
			this->rcon16->Controls->Add(this->output16);
			this->rcon16->Controls->Add(this->input16);
			this->rcon16->Location = System::Drawing::Point(4, 22);
			this->rcon16->Name = L"rcon16";
			this->rcon16->Size = System::Drawing::Size(1075, 574);
			this->rcon16->TabIndex = 16;
			this->rcon16->Text = L"rcon16";
			this->rcon16->UseVisualStyleBackColor = true;
			// 
			// output16
			// 
			this->output16->BackColor = System::Drawing::Color::Black;
			this->output16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output16->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output16->Location = System::Drawing::Point(0, 0);
			this->output16->Name = L"output16";
			this->output16->Size = System::Drawing::Size(1075, 551);
			this->output16->TabIndex = 16;
			this->output16->Text = L"";
			this->output16->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output16_KeyDown);
			this->output16->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output16_KeyPress);
			this->output16->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output16_MouseDown);
			// 
			// input16
			// 
			this->input16->AcceptsReturn = true;
			this->input16->BackColor = System::Drawing::Color::Black;
			this->input16->ForeColor = System::Drawing::Color::White;
			this->input16->Location = System::Drawing::Point(0, 554);
			this->input16->Name = L"input16";
			this->input16->Size = System::Drawing::Size(1075, 20);
			this->input16->TabIndex = 16;
			this->input16->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input16->Click += gcnew System::EventHandler(this, &QLRcon::input16_Click);
			this->input16->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input16_KeyDown);
			this->input16->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input16_KeyPress);
			// 
			// rcon17
			// 
			this->rcon17->Controls->Add(this->output17);
			this->rcon17->Controls->Add(this->input17);
			this->rcon17->Location = System::Drawing::Point(4, 22);
			this->rcon17->Name = L"rcon17";
			this->rcon17->Size = System::Drawing::Size(1075, 574);
			this->rcon17->TabIndex = 17;
			this->rcon17->Text = L"rcon17";
			this->rcon17->UseVisualStyleBackColor = true;
			// 
			// output17
			// 
			this->output17->BackColor = System::Drawing::Color::Black;
			this->output17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output17->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output17->Location = System::Drawing::Point(0, 0);
			this->output17->Name = L"output17";
			this->output17->Size = System::Drawing::Size(1075, 551);
			this->output17->TabIndex = 17;
			this->output17->Text = L"";
			this->output17->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output17_KeyDown);
			this->output17->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output17_KeyPress);
			this->output17->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output17_MouseDown);
			// 
			// input17
			// 
			this->input17->AcceptsReturn = true;
			this->input17->BackColor = System::Drawing::Color::Black;
			this->input17->ForeColor = System::Drawing::Color::White;
			this->input17->Location = System::Drawing::Point(0, 554);
			this->input17->Name = L"input17";
			this->input17->Size = System::Drawing::Size(1075, 20);
			this->input17->TabIndex = 17;
			this->input17->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input17->Click += gcnew System::EventHandler(this, &QLRcon::input17_Click);
			this->input17->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input17_KeyDown);
			this->input17->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input17_KeyPress);
			// 
			// rcon18
			// 
			this->rcon18->Controls->Add(this->output18);
			this->rcon18->Controls->Add(this->input18);
			this->rcon18->Location = System::Drawing::Point(4, 22);
			this->rcon18->Name = L"rcon18";
			this->rcon18->Size = System::Drawing::Size(1075, 574);
			this->rcon18->TabIndex = 18;
			this->rcon18->Text = L"rcon18";
			this->rcon18->UseVisualStyleBackColor = true;
			// 
			// output18
			// 
			this->output18->BackColor = System::Drawing::Color::Black;
			this->output18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output18->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output18->Location = System::Drawing::Point(0, 0);
			this->output18->Name = L"output18";
			this->output18->Size = System::Drawing::Size(1075, 551);
			this->output18->TabIndex = 18;
			this->output18->Text = L"";
			this->output18->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output18_KeyDown);
			this->output18->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output18_KeyPress);
			this->output18->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output18_MouseDown);
			// 
			// input18
			// 
			this->input18->AcceptsReturn = true;
			this->input18->BackColor = System::Drawing::Color::Black;
			this->input18->ForeColor = System::Drawing::Color::White;
			this->input18->Location = System::Drawing::Point(0, 554);
			this->input18->Name = L"input18";
			this->input18->Size = System::Drawing::Size(1075, 20);
			this->input18->TabIndex = 18;
			this->input18->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input18->Click += gcnew System::EventHandler(this, &QLRcon::input18_Click);
			this->input18->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input18_KeyDown);
			this->input18->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input18_KeyPress);
			// 
			// rcon19
			// 
			this->rcon19->Controls->Add(this->output19);
			this->rcon19->Controls->Add(this->input19);
			this->rcon19->Location = System::Drawing::Point(4, 22);
			this->rcon19->Name = L"rcon19";
			this->rcon19->Size = System::Drawing::Size(1075, 574);
			this->rcon19->TabIndex = 19;
			this->rcon19->Text = L"rcon19";
			this->rcon19->UseVisualStyleBackColor = true;
			// 
			// output19
			// 
			this->output19->BackColor = System::Drawing::Color::Black;
			this->output19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output19->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(226)), static_cast<System::Int32>(static_cast<System::Byte>(226)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->output19->Location = System::Drawing::Point(0, 0);
			this->output19->Name = L"output19";
			this->output19->Size = System::Drawing::Size(1075, 551);
			this->output19->TabIndex = 19;
			this->output19->Text = L"";
			this->output19->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::output19_KeyDown);
			this->output19->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::output19_KeyPress);
			this->output19->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &QLRcon::output19_MouseDown);
			// 
			// input19
			// 
			this->input19->AcceptsReturn = true;
			this->input19->BackColor = System::Drawing::Color::Black;
			this->input19->ForeColor = System::Drawing::Color::White;
			this->input19->Location = System::Drawing::Point(0, 554);
			this->input19->Name = L"input19";
			this->input19->Size = System::Drawing::Size(1075, 20);
			this->input19->TabIndex = 19;
			this->input19->Text = L"Enter Command Here ... <Enter to send> ...";
			this->input19->Click += gcnew System::EventHandler(this, &QLRcon::input19_Click);
			this->input19->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &QLRcon::input19_KeyDown);
			this->input19->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::input19_KeyPress);
			// 
			// editServers
			// 
			this->editServers->ForeColor = System::Drawing::Color::Black;
			this->editServers->Location = System::Drawing::Point(213, 12);
			this->editServers->Name = L"editServers";
			this->editServers->Size = System::Drawing::Size(75, 23);
			this->editServers->TabIndex = 1;
			this->editServers->Text = L"Edit Servers";
			this->editServers->UseVisualStyleBackColor = true;
			this->editServers->Click += gcnew System::EventHandler(this, &QLRcon::editServers_Click);
			// 
			// serverList
			// 
			this->serverList->BackColor = System::Drawing::SystemColors::Menu;
			this->serverList->FormattingEnabled = true;
			this->serverList->Location = System::Drawing::Point(295, 13);
			this->serverList->Name = L"serverList";
			this->serverList->Size = System::Drawing::Size(249, 21);
			this->serverList->TabIndex = 2;
			this->serverList->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &QLRcon::serverList_KeyPress);
			// 
			// connect
			// 
			this->connect->ForeColor = System::Drawing::Color::Black;
			this->connect->Location = System::Drawing::Point(551, 12);
			this->connect->Name = L"connect";
			this->connect->Size = System::Drawing::Size(75, 23);
			this->connect->TabIndex = 3;
			this->connect->Text = L"Connect";
			this->connect->UseVisualStyleBackColor = true;
			this->connect->Click += gcnew System::EventHandler(this, &QLRcon::connect_Click);
			// 
			// disconnectTab
			// 
			this->disconnectTab->ForeColor = System::Drawing::Color::Black;
			this->disconnectTab->Location = System::Drawing::Point(660, 12);
			this->disconnectTab->Name = L"disconnectTab";
			this->disconnectTab->Size = System::Drawing::Size(137, 23);
			this->disconnectTab->TabIndex = 4;
			this->disconnectTab->Text = L"Disconnect Current Tab";
			this->disconnectTab->UseVisualStyleBackColor = true;
			this->disconnectTab->Click += gcnew System::EventHandler(this, &QLRcon::disconnectTab_Click);
			// 
			// closeTab
			// 
			this->closeTab->ForeColor = System::Drawing::Color::Black;
			this->closeTab->Location = System::Drawing::Point(813, 12);
			this->closeTab->Name = L"closeTab";
			this->closeTab->Size = System::Drawing::Size(118, 23);
			this->closeTab->TabIndex = 7;
			this->closeTab->Text = L"Close Current Tab";
			this->closeTab->UseVisualStyleBackColor = true;
			this->closeTab->Click += gcnew System::EventHandler(this, &QLRcon::closeTab_Click);
			// 
			// exit
			// 
			this->exit->ForeColor = System::Drawing::Color::Black;
			this->exit->Location = System::Drawing::Point(991, 12);
			this->exit->Name = L"exit";
			this->exit->Size = System::Drawing::Size(75, 23);
			this->exit->TabIndex = 5;
			this->exit->Text = L"Exit";
			this->exit->UseVisualStyleBackColor = true;
			this->exit->Click += gcnew System::EventHandler(this, &QLRcon::exit_Click);
			// 
			// serverName
			// 
			this->serverName->AutoSize = true;
			this->serverName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->serverName->ForeColor = System::Drawing::Color::Black;
			this->serverName->Location = System::Drawing::Point(207, 38);
			this->serverName->Name = L"serverName";
			this->serverName->Size = System::Drawing::Size(237, 31);
			this->serverName->TabIndex = 6;
			this->serverName->Text = L"Server Information";
			// 
			// IPLabel
			// 
			this->IPLabel->AutoSize = true;
			this->IPLabel->ForeColor = System::Drawing::Color::Black;
			this->IPLabel->Location = System::Drawing::Point(213, 73);
			this->IPLabel->Name = L"IPLabel";
			this->IPLabel->Size = System::Drawing::Size(39, 13);
			this->IPLabel->TabIndex = 8;
			this->IPLabel->Text = L"IP:Port";
			// 
			// notConnectedMessage
			// 
			this->notConnectedMessage->BackColor = System::Drawing::SystemColors::HotTrack;
			this->notConnectedMessage->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 65, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->notConnectedMessage->Location = System::Drawing::Point(37, 118);
			this->notConnectedMessage->Multiline = true;
			this->notConnectedMessage->Name = L"notConnectedMessage";
			this->notConnectedMessage->ReadOnly = true;
			this->notConnectedMessage->Size = System::Drawing::Size(993, 434);
			this->notConnectedMessage->TabIndex = 9;
			this->notConnectedMessage->Text = L"You are not connected to any servers. This area will show you the connected serve"
				L"rs.";
			this->notConnectedMessage->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// settings
			// 
			this->settings->ForeColor = System::Drawing::Color::Black;
			this->settings->Location = System::Drawing::Point(37, 12);
			this->settings->Name = L"settings";
			this->settings->Size = System::Drawing::Size(75, 23);
			this->settings->TabIndex = 10;
			this->settings->Text = L"Settings";
			this->settings->UseVisualStyleBackColor = true;
			this->settings->Click += gcnew System::EventHandler(this, &QLRcon::settings_Click);
			// 
			// command1
			// 
			this->command1->ForeColor = System::Drawing::Color::Black;
			this->command1->Location = System::Drawing::Point(12, 699);
			this->command1->Name = L"command1";
			this->command1->Size = System::Drawing::Size(155, 23);
			this->command1->TabIndex = 11;
			this->command1->Text = L"Command 1";
			this->command1->UseVisualStyleBackColor = true;
			this->command1->Click += gcnew System::EventHandler(this, &QLRcon::command1_Click);
			// 
			// command2
			// 
			this->command2->ForeColor = System::Drawing::Color::Black;
			this->command2->Location = System::Drawing::Point(192, 699);
			this->command2->Name = L"command2";
			this->command2->Size = System::Drawing::Size(155, 23);
			this->command2->TabIndex = 12;
			this->command2->Text = L"Command 2";
			this->command2->UseVisualStyleBackColor = true;
			this->command2->Click += gcnew System::EventHandler(this, &QLRcon::command2_Click);
			// 
			// command3
			// 
			this->command3->ForeColor = System::Drawing::Color::Black;
			this->command3->Location = System::Drawing::Point(372, 699);
			this->command3->Name = L"command3";
			this->command3->Size = System::Drawing::Size(155, 23);
			this->command3->TabIndex = 13;
			this->command3->Text = L"Command 3";
			this->command3->UseVisualStyleBackColor = true;
			this->command3->Click += gcnew System::EventHandler(this, &QLRcon::command3_Click);
			// 
			// command4
			// 
			this->command4->ForeColor = System::Drawing::Color::Black;
			this->command4->Location = System::Drawing::Point(552, 699);
			this->command4->Name = L"command4";
			this->command4->Size = System::Drawing::Size(155, 23);
			this->command4->TabIndex = 14;
			this->command4->Text = L"Command 4";
			this->command4->UseVisualStyleBackColor = true;
			this->command4->Click += gcnew System::EventHandler(this, &QLRcon::command4_Click);
			// 
			// command5
			// 
			this->command5->ForeColor = System::Drawing::Color::Black;
			this->command5->Location = System::Drawing::Point(732, 699);
			this->command5->Name = L"command5";
			this->command5->Size = System::Drawing::Size(155, 23);
			this->command5->TabIndex = 15;
			this->command5->Text = L"Command 5";
			this->command5->UseVisualStyleBackColor = true;
			this->command5->Click += gcnew System::EventHandler(this, &QLRcon::command5_Click);
			// 
			// command6
			// 
			this->command6->ForeColor = System::Drawing::Color::Black;
			this->command6->Location = System::Drawing::Point(912, 699);
			this->command6->Name = L"command6";
			this->command6->Size = System::Drawing::Size(155, 23);
			this->command6->TabIndex = 16;
			this->command6->Text = L"Command 6";
			this->command6->UseVisualStyleBackColor = true;
			this->command6->Click += gcnew System::EventHandler(this, &QLRcon::command6_Click);
			// 
			// connectGame
			// 
			this->connectGame->ForeColor = System::Drawing::Color::Black;
			this->connectGame->Location = System::Drawing::Point(37, 43);
			this->connectGame->Name = L"connectGame";
			this->connectGame->Size = System::Drawing::Size(147, 23);
			this->connectGame->TabIndex = 17;
			this->connectGame->Text = L"Connect to Game Server";
			this->connectGame->UseVisualStyleBackColor = true;
			this->connectGame->Click += gcnew System::EventHandler(this, &QLRcon::connectGame_Click);
			// 
			// QLRcon
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->ClientSize = System::Drawing::Size(1080, 731);
			this->Controls->Add(this->connectGame);
			this->Controls->Add(this->command6);
			this->Controls->Add(this->command5);
			this->Controls->Add(this->command4);
			this->Controls->Add(this->command3);
			this->Controls->Add(this->command2);
			this->Controls->Add(this->command1);
			this->Controls->Add(this->settings);
			this->Controls->Add(this->notConnectedMessage);
			this->Controls->Add(this->IPLabel);
			this->Controls->Add(this->closeTab);
			this->Controls->Add(this->serverName);
			this->Controls->Add(this->exit);
			this->Controls->Add(this->disconnectTab);
			this->Controls->Add(this->connect);
			this->Controls->Add(this->serverList);
			this->Controls->Add(this->editServers);
			this->ForeColor = System::Drawing::Color::White;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"QLRcon";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Quake Live Remote Console";
			this->Load += gcnew System::EventHandler(this, &QLRcon::Window_Load);
			this->Shown += gcnew System::EventHandler(this, &QLRcon::Window_Shown);
			this->rcon0->ResumeLayout(false);
			this->rcon0->PerformLayout();
			this->rcon1->ResumeLayout(false);
			this->rcon1->PerformLayout();
			this->rcon2->ResumeLayout(false);
			this->rcon2->PerformLayout();
			this->rcon3->ResumeLayout(false);
			this->rcon3->PerformLayout();
			this->rcon4->ResumeLayout(false);
			this->rcon4->PerformLayout();
			this->rcon5->ResumeLayout(false);
			this->rcon5->PerformLayout();
			this->rcon6->ResumeLayout(false);
			this->rcon6->PerformLayout();
			this->rcon7->ResumeLayout(false);
			this->rcon7->PerformLayout();
			this->rcon8->ResumeLayout(false);
			this->rcon8->PerformLayout();
			this->rcon9->ResumeLayout(false);
			this->rcon9->PerformLayout();
			this->rcon10->ResumeLayout(false);
			this->rcon10->PerformLayout();
			this->rcon11->ResumeLayout(false);
			this->rcon11->PerformLayout();
			this->rcon12->ResumeLayout(false);
			this->rcon12->PerformLayout();
			this->rcon13->ResumeLayout(false);
			this->rcon13->PerformLayout();
			this->rcon14->ResumeLayout(false);
			this->rcon14->PerformLayout();
			this->rcon15->ResumeLayout(false);
			this->rcon15->PerformLayout();
			this->rcon16->ResumeLayout(false);
			this->rcon16->PerformLayout();
			this->rcon17->ResumeLayout(false);
			this->rcon17->PerformLayout();
			this->rcon18->ResumeLayout(false);
			this->rcon18->PerformLayout();
			this->rcon19->ResumeLayout(false);
			this->rcon19->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	///Form User Interface Functions
	private: System::Void Window_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Window_Shown(System::Object^  sender, System::EventArgs^  e);
	private: System::Void rconTabs_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void exit_Click(System::Object^  sender, System::EventArgs^  e);
	//loads the settings Form
	private: System::Void settings_Click(System::Object^  sender, System::EventArgs^  e);
	//Executes when the edit servers form is closed
	private: void OnSettingsFormClosed(Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);
	//loads the edit servers Form
	private: System::Void editServers_Click(System::Object^  sender, System::EventArgs^  e);
	//Executes when the edit servers form is closed
	private: void OnEditServersFormClosed(Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);
	//Executes when the status form is closed
	private: void OnStatusFormClosed(Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);

	private: void input0_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input0_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input0_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input1_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input2_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input2_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input2_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input3_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input3_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input3_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input4_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input4_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input4_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input5_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input5_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input5_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input6_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input6_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input6_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input7_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input7_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input7_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input8_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input8_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input8_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input9_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input9_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input9_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input10_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input10_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input10_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input11_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input11_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input11_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input12_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input12_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input12_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input13_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input13_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input13_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input14_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input14_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input14_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input15_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input15_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input15_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input16_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input16_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input16_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input17_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input17_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input17_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input18_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input18_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input18_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: void input19_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void input19_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void input19_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void connect_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void disconnectTab_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void closeTab_Click(System::Object^  sender, System::EventArgs^  e);
			 
	private: System::Void serverList_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);

	private: System::Void command1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void command2_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void command3_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void command4_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void command5_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void command6_Click(System::Object^  sender, System::EventArgs^  e);

	private: System::Void connectGame_Click(System::Object^  sender, System::EventArgs^  e);

	private: System::Void output0_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output0_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output0_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output2_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output2_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output3_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output3_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output3_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output4_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output4_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output4_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output5_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output5_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output5_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output6_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output6_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output6_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output7_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output7_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output7_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output8_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output8_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output8_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output9_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output9_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output9_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output10_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output10_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output10_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output11_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output11_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output11_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output12_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output12_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output12_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output13_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output13_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output13_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output14_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output14_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output14_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output15_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output15_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output15_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output16_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output16_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output16_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output17_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output17_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output17_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output18_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output18_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output18_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void output19_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void output19_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void output19_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Void rClickItem1_MouseDown(System::Object^  sender, EventArgs^  e);
	private: System::Void rClickItem2_MouseDown(System::Object^  sender, EventArgs^  e);
	private: System::Void rClickItem3_MouseDown(System::Object^  sender, EventArgs^  e);
	private: System::Void rClickItem4_MouseDown(System::Object^  sender, EventArgs^  e);
	private: System::Void rClickItem5_MouseDown(System::Object^  sender, EventArgs^  e);
	private: System::Void rClickItem6_MouseDown(System::Object^  sender, EventArgs^  e);
	//private: System::Void rClickItem7_MouseDown(System::Object^  sender, EventArgs^  e);

	///Utility Functions
	//fills the Server Selection combo box
	private: void loadServersToComboBox();
	//auto connects to the auto connect enabled servers at startup
	private: void autoConectServers();
	//checks to see if the selected server is already connected or calls the serverConnection command
	private: bool conectServer(String^ server);
	//used for the arrow keys to show previously entered commands
	private: String^ getCommandEntry(int tab, String^ line, String^ direction);
	//adds commands to the comands to send and the stored command (for arrow keys) arrays
	protected: void addComandEntry(int tab, String^ command);
	//clears the command entry arrays
	private: void clearCommandEntries(int tab);
	//gets the next comand to send to the server
	private: char* getNextCommand(int tab);
	//connects/disconnects the server to/from the specified tab
	private: void serverConnection(int server, String^ action);
	//closes the server conneciton on the specified tab
	private: void exitConnection(int server);
	//updates the displayed information for the selected server tab
	private: void updateServerTabInfo(int selectedTab);
	//returns the tab number of the supplied tab name
	private: int getRconTabNumber(String^ tabName);
	//UUID generation
	private: void generateUUID();
	//Udates the tabPage index number location for visible/active rconTab pages
	private: void updateTabLocations();
	private: void addTab(int add);
	private: void removeTab(int remove);
	private: void loadSettings();
	private: void buildDisplayLine(int tab, String^ text, String^ displayLine, bool * printEntry);
	private: void buildLogFileLines(int tab, String^ text);
	private: String^ stripColorCodes(String^ text);
	private: void connectToServer(Object^ parameters);
	private: bool checkMonitor(void *monitor, Int32 * eventNum, array<String^>^ eventInfo, 
		char* buffer, wchar_t * wstr, Int32 * eventID, Int32 * size, Int32 * eventCheck);
	private: String^ formatMessage(String^ message, Int32 index);
	private: void displayText(int tab, String^ text);
	private: void displayServerMessage(int tab, String^ text);
	//private: void displayServerMessage(Object^ line);
	private: void connectToGame();
	private: void connectToGameServer(Object^ tab);
	private: void viewServerTabButtons();
	private: void serverTabConnection(int tab);
	private: void closeServerTab(int tab);
	private: void checkForOldFiles();
	private: bool closeOut();
	private: void startStatusWindowProcess();
	private: void openStatusWindow(Object^ tab);
	private: void getMessageInfo(int tab, String^ message, array<String^>^ msgArray, Int32 * numberCheck);
	private: void playerEventsProcess(Object^ parameters, int tab);
	private: void getGameStatsInfo(Object^ parameters);
	private: void connectToStats(String^ ip, int tab);
	private: void parseJson(String^ message, int tab, 
		Newtonsoft::Json::Linq::JObject^ jObject, Newtonsoft::Json::Linq::JObject^ data, 
		Newtonsoft::Json::Linq::JObject^ killer, Newtonsoft::Json::Linq::JObject^ victim);
	private: bool JTokenIsNullOrEnpty(Newtonsoft::Json::Linq::JToken^ token);

	public: static void addToSendCommands(int tab, String^ command);
};
}

