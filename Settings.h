/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.4 on 8/18/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#pragma once

#pragma comment(lib, "Shell32.lib") //Used for ShellExecute

#include "IniEditor.h"
#include "LogFileWriter.h"

#define WEBSITE_URL L"https://github.com/BarelyMiSSeD/Quake-Live-Rcon"
#define MAX_TEXTBOX_LINES 6000 // The max amount of lines allowed in an rcon output window
#define LINES_TO_DELETE 1000 // The amount of lines to delete when the maz textbox lines is reached
#define LOG_FILE_LOCATION L".\\QuakeLiveRconLogs\\"

namespace QuakeLiveRcon {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Settings
	/// </summary>
	public ref class Settings : public System::Windows::Forms::Form	{

	private: IniEditor^ ini; //Use the IniEditor.h to manage the server ini file
	private: System::Windows::Forms::Label^  timeStampLabel;
	private: System::Windows::Forms::CheckBox^  timeStamp;
	private: System::Windows::Forms::Label^  timeStampSelectionLabel;
	private: System::Windows::Forms::ComboBox^  timeStampFormat;


	private: System::Windows::Forms::Label^  teamColorLabel;


	private: System::Windows::Forms::Label^  chatColorLabel;
	private: System::Windows::Forms::NumericUpDown^  chatMessageColor;
	private: System::Windows::Forms::NumericUpDown^  teamMessageColor;
	private: System::Windows::Forms::Label^  messageColorLabel;

	private: List<System::Drawing::Color>^ colorList; //store the colors from the System::Drawing::Color structure

	public:
		Settings(const char *file, String^ version);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Settings();


	private: System::Windows::Forms::LinkLabel^  website;
	private: System::Windows::Forms::CheckBox^  statusCommand;
	private: System::Windows::Forms::Label^  divider1;
	private: System::Windows::Forms::CheckBox^  enableCommand1;
	private: System::Windows::Forms::Label^  cmd1BtnLblLabel;
	private: System::Windows::Forms::TextBox^  cmd1BtnLabel;
	private: System::Windows::Forms::Label^  cmd1BtnCmdLbl;
	private: System::Windows::Forms::TextBox^  cmd1BtnCmd;
	private: System::Windows::Forms::Label^  divider2;
	private: System::Windows::Forms::CheckBox^  enableCommand2;
	private: System::Windows::Forms::Label^  cmd2BtnLblLabel;
	private: System::Windows::Forms::TextBox^  cmd2BtnLabel;
	private: System::Windows::Forms::Label^  cmd2BtnCmdLbl;
	private: System::Windows::Forms::TextBox^  cmd2BtnCmd;
	private: System::Windows::Forms::Label^  divider3;
	private: System::Windows::Forms::CheckBox^  enableCommand3;
	private: System::Windows::Forms::Label^  cmd3BtnCmdLbl;
	private: System::Windows::Forms::TextBox^  cmd3BtnCmd;
	private: System::Windows::Forms::Label^  cmd3BtnLblLabel;
	private: System::Windows::Forms::TextBox^  cmd3BtnLabel;
	private: System::Windows::Forms::Label^  verticalDivider;
	private: System::Windows::Forms::Label^  divider4;
	private: System::Windows::Forms::CheckBox^  enableCommand4;
	private: System::Windows::Forms::Label^  cmd4BtnCmdLbl;
	private: System::Windows::Forms::TextBox^  cmd4BtnCmd;
	private: System::Windows::Forms::Label^  cmd4BtnLblLabel;
	private: System::Windows::Forms::TextBox^  cmd4BtnLabel;
	private: System::Windows::Forms::Label^  divider5;
	private: System::Windows::Forms::CheckBox^  enableCommand5;
	private: System::Windows::Forms::Label^  cmd5BtnCmdLbl;
	private: System::Windows::Forms::TextBox^  cmd5BtnCmd;
	private: System::Windows::Forms::Label^  cmd5BtnLblLabel;
	private: System::Windows::Forms::TextBox^  cmd5BtnLabel;
	private: System::Windows::Forms::Label^  divider6;
	private: System::Windows::Forms::CheckBox^  enableCommand6;
	private: System::Windows::Forms::Label^  cmd6BtnCmdLbl;
	private: System::Windows::Forms::TextBox^  cmd6BtnCmd;
	private: System::Windows::Forms::Label^  cmd6BtnLblLabel;
	private: System::Windows::Forms::TextBox^  cmd6BtnLabel;
	private: System::Windows::Forms::Label^  versionLabel;
	private: System::Windows::Forms::Label^  divider7;
	private: System::Windows::Forms::Label^  divider8;
	private: System::Windows::Forms::Label^  connectGameButtonLabel1;
	private: System::Windows::Forms::CheckBox^  enableConnectToGame;
	private: System::Windows::Forms::Label^  divider9;
	private: System::Windows::Forms::Button^  save;
	private: System::Windows::Forms::Button^  cancel;
	private: System::Windows::Forms::Label^  stripColorsLabel;
	private: System::Windows::Forms::CheckBox^  stripColors;
	private: System::Windows::Forms::Label^  divider0;
	private: System::Windows::Forms::Label^  autoScrollLabel;
	private: System::Windows::Forms::CheckBox^  disableScroll;
	private: System::Windows::Forms::Label^  divider10;
	private: System::Windows::Forms::Label^  maxLinesLabel;
	private: System::Windows::Forms::NumericUpDown^  maxLines;
	private: System::Windows::Forms::Label^  linesRemoveLabel;
	private: System::Windows::Forms::NumericUpDown^  linesRemove;
	private: System::Windows::Forms::Label^  divider11;
	private: System::Windows::Forms::Label^  linesRecommendLabel;
	private: System::Windows::Forms::Button^  reset;
	private: System::Windows::Forms::ListBox^  menuSelection;
	private: System::Windows::Forms::Label^  statusCmdLabel;
	private: System::Windows::Forms::CheckBox^  enableLogging;
	private: System::Windows::Forms::Label^  enableLoggingLabel1;
	private: System::Windows::Forms::Label^  enableLoggingLabel2;
	private: System::Windows::Forms::Label^  connectGameButtonLabel2;
	private: System::Windows::Forms::Label^  autoScrollNoteLabel;
	private: System::Windows::Forms::Label^  color0Label;
	private: System::Windows::Forms::TextBox^  color0Box;
	private: System::Windows::Forms::Button^  color0Button;
	private: System::Windows::Forms::Button^  color1Button;
	private: System::Windows::Forms::TextBox^  color1Box;
	private: System::Windows::Forms::Label^  color1Label;
	private: System::Windows::Forms::Button^  color2Button;
	private: System::Windows::Forms::TextBox^  color2Box;
	private: System::Windows::Forms::Label^  color2Label;
	private: System::Windows::Forms::Button^  color8Button;
	private: System::Windows::Forms::TextBox^  color8Box;
	private: System::Windows::Forms::Label^  color8Label;
	private: System::Windows::Forms::Button^  color3Button;
	private: System::Windows::Forms::TextBox^  color3Box;
	private: System::Windows::Forms::Label^  color3Label;
	private: System::Windows::Forms::Button^  color4Button;
	private: System::Windows::Forms::TextBox^  color4Box;
	private: System::Windows::Forms::Label^  color4Label;
	private: System::Windows::Forms::Button^  color5Button;
	private: System::Windows::Forms::TextBox^  color5Box;
	private: System::Windows::Forms::Label^  color5Label;
	private: System::Windows::Forms::Button^  color7Button;
	private: System::Windows::Forms::TextBox^  color7Box;
	private: System::Windows::Forms::Label^  color7Label;
	private: System::Windows::Forms::Button^  color6Button;
	private: System::Windows::Forms::TextBox^  color6Box;
	private: System::Windows::Forms::Label^  color6Label;
	private: System::Windows::Forms::Label^  colorLabel;
	private: System::Windows::Forms::Label^  divider13;
	private: System::Windows::Forms::Label^  keepAliveLabel;
	private: System::Windows::Forms::CheckBox^  keepAlive;
	private: System::Windows::Forms::Label^  keepAliveNote;
	private: System::Windows::Forms::Label^  colorNote;
	private: System::Windows::Forms::Button^  logFiles;
	private: System::Windows::Forms::Label^  deleteOldLabel;
	private: System::Windows::Forms::CheckBox^  automaticFileDelete;
	private: System::Windows::Forms::NumericUpDown^  deleteDays;
	private: System::Windows::Forms::Label^  leadingDeleteDaysLabel;
	private: System::Windows::Forms::Label^  trailingDeleteDaysLabel;
	private: System::Windows::Forms::Button^  deleteNow;
	private: System::Windows::Forms::Label^  divider14;
	private: System::Windows::Forms::Label^  divider15;
	private: System::Windows::Forms::Label^  gameEventsLabel;
	private: System::Windows::Forms::CheckBox^  gameEvents;
	private: System::Windows::Forms::CheckBox^  killMessages;
	private: System::Windows::Forms::CheckBox^  teamSwitch;
	private: System::Windows::Forms::CheckBox^  warmUp;
	private: System::Windows::Forms::CheckBox^  playerMedals;

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
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Settings::typeid));
			this->website = (gcnew System::Windows::Forms::LinkLabel());
			this->statusCommand = (gcnew System::Windows::Forms::CheckBox());
			this->divider1 = (gcnew System::Windows::Forms::Label());
			this->enableCommand1 = (gcnew System::Windows::Forms::CheckBox());
			this->cmd1BtnLblLabel = (gcnew System::Windows::Forms::Label());
			this->cmd1BtnLabel = (gcnew System::Windows::Forms::TextBox());
			this->cmd1BtnCmdLbl = (gcnew System::Windows::Forms::Label());
			this->cmd1BtnCmd = (gcnew System::Windows::Forms::TextBox());
			this->divider2 = (gcnew System::Windows::Forms::Label());
			this->enableCommand2 = (gcnew System::Windows::Forms::CheckBox());
			this->cmd2BtnLblLabel = (gcnew System::Windows::Forms::Label());
			this->cmd2BtnLabel = (gcnew System::Windows::Forms::TextBox());
			this->cmd2BtnCmdLbl = (gcnew System::Windows::Forms::Label());
			this->cmd2BtnCmd = (gcnew System::Windows::Forms::TextBox());
			this->divider3 = (gcnew System::Windows::Forms::Label());
			this->enableCommand3 = (gcnew System::Windows::Forms::CheckBox());
			this->cmd3BtnCmdLbl = (gcnew System::Windows::Forms::Label());
			this->cmd3BtnCmd = (gcnew System::Windows::Forms::TextBox());
			this->cmd3BtnLblLabel = (gcnew System::Windows::Forms::Label());
			this->cmd3BtnLabel = (gcnew System::Windows::Forms::TextBox());
			this->divider4 = (gcnew System::Windows::Forms::Label());
			this->enableCommand4 = (gcnew System::Windows::Forms::CheckBox());
			this->cmd4BtnCmdLbl = (gcnew System::Windows::Forms::Label());
			this->cmd4BtnCmd = (gcnew System::Windows::Forms::TextBox());
			this->cmd4BtnLblLabel = (gcnew System::Windows::Forms::Label());
			this->cmd4BtnLabel = (gcnew System::Windows::Forms::TextBox());
			this->divider5 = (gcnew System::Windows::Forms::Label());
			this->enableCommand5 = (gcnew System::Windows::Forms::CheckBox());
			this->cmd5BtnCmdLbl = (gcnew System::Windows::Forms::Label());
			this->cmd5BtnCmd = (gcnew System::Windows::Forms::TextBox());
			this->cmd5BtnLblLabel = (gcnew System::Windows::Forms::Label());
			this->cmd5BtnLabel = (gcnew System::Windows::Forms::TextBox());
			this->divider6 = (gcnew System::Windows::Forms::Label());
			this->enableCommand6 = (gcnew System::Windows::Forms::CheckBox());
			this->cmd6BtnCmdLbl = (gcnew System::Windows::Forms::Label());
			this->cmd6BtnCmd = (gcnew System::Windows::Forms::TextBox());
			this->cmd6BtnLblLabel = (gcnew System::Windows::Forms::Label());
			this->cmd6BtnLabel = (gcnew System::Windows::Forms::TextBox());
			this->verticalDivider = (gcnew System::Windows::Forms::Label());
			this->versionLabel = (gcnew System::Windows::Forms::Label());
			this->divider7 = (gcnew System::Windows::Forms::Label());
			this->divider8 = (gcnew System::Windows::Forms::Label());
			this->connectGameButtonLabel1 = (gcnew System::Windows::Forms::Label());
			this->enableConnectToGame = (gcnew System::Windows::Forms::CheckBox());
			this->divider9 = (gcnew System::Windows::Forms::Label());
			this->save = (gcnew System::Windows::Forms::Button());
			this->cancel = (gcnew System::Windows::Forms::Button());
			this->stripColorsLabel = (gcnew System::Windows::Forms::Label());
			this->stripColors = (gcnew System::Windows::Forms::CheckBox());
			this->divider0 = (gcnew System::Windows::Forms::Label());
			this->autoScrollLabel = (gcnew System::Windows::Forms::Label());
			this->disableScroll = (gcnew System::Windows::Forms::CheckBox());
			this->divider10 = (gcnew System::Windows::Forms::Label());
			this->maxLinesLabel = (gcnew System::Windows::Forms::Label());
			this->maxLines = (gcnew System::Windows::Forms::NumericUpDown());
			this->linesRemoveLabel = (gcnew System::Windows::Forms::Label());
			this->linesRemove = (gcnew System::Windows::Forms::NumericUpDown());
			this->divider11 = (gcnew System::Windows::Forms::Label());
			this->linesRecommendLabel = (gcnew System::Windows::Forms::Label());
			this->reset = (gcnew System::Windows::Forms::Button());
			this->menuSelection = (gcnew System::Windows::Forms::ListBox());
			this->statusCmdLabel = (gcnew System::Windows::Forms::Label());
			this->enableLogging = (gcnew System::Windows::Forms::CheckBox());
			this->enableLoggingLabel1 = (gcnew System::Windows::Forms::Label());
			this->enableLoggingLabel2 = (gcnew System::Windows::Forms::Label());
			this->connectGameButtonLabel2 = (gcnew System::Windows::Forms::Label());
			this->autoScrollNoteLabel = (gcnew System::Windows::Forms::Label());
			this->color0Label = (gcnew System::Windows::Forms::Label());
			this->color0Box = (gcnew System::Windows::Forms::TextBox());
			this->color0Button = (gcnew System::Windows::Forms::Button());
			this->color1Button = (gcnew System::Windows::Forms::Button());
			this->color1Box = (gcnew System::Windows::Forms::TextBox());
			this->color1Label = (gcnew System::Windows::Forms::Label());
			this->color2Button = (gcnew System::Windows::Forms::Button());
			this->color2Box = (gcnew System::Windows::Forms::TextBox());
			this->color2Label = (gcnew System::Windows::Forms::Label());
			this->color8Button = (gcnew System::Windows::Forms::Button());
			this->color8Box = (gcnew System::Windows::Forms::TextBox());
			this->color8Label = (gcnew System::Windows::Forms::Label());
			this->color3Button = (gcnew System::Windows::Forms::Button());
			this->color3Box = (gcnew System::Windows::Forms::TextBox());
			this->color3Label = (gcnew System::Windows::Forms::Label());
			this->color4Button = (gcnew System::Windows::Forms::Button());
			this->color4Box = (gcnew System::Windows::Forms::TextBox());
			this->color4Label = (gcnew System::Windows::Forms::Label());
			this->color5Button = (gcnew System::Windows::Forms::Button());
			this->color5Box = (gcnew System::Windows::Forms::TextBox());
			this->color5Label = (gcnew System::Windows::Forms::Label());
			this->color7Button = (gcnew System::Windows::Forms::Button());
			this->color7Box = (gcnew System::Windows::Forms::TextBox());
			this->color7Label = (gcnew System::Windows::Forms::Label());
			this->color6Button = (gcnew System::Windows::Forms::Button());
			this->color6Box = (gcnew System::Windows::Forms::TextBox());
			this->color6Label = (gcnew System::Windows::Forms::Label());
			this->colorLabel = (gcnew System::Windows::Forms::Label());
			this->divider13 = (gcnew System::Windows::Forms::Label());
			this->keepAliveLabel = (gcnew System::Windows::Forms::Label());
			this->keepAlive = (gcnew System::Windows::Forms::CheckBox());
			this->keepAliveNote = (gcnew System::Windows::Forms::Label());
			this->colorNote = (gcnew System::Windows::Forms::Label());
			this->logFiles = (gcnew System::Windows::Forms::Button());
			this->deleteOldLabel = (gcnew System::Windows::Forms::Label());
			this->automaticFileDelete = (gcnew System::Windows::Forms::CheckBox());
			this->deleteDays = (gcnew System::Windows::Forms::NumericUpDown());
			this->leadingDeleteDaysLabel = (gcnew System::Windows::Forms::Label());
			this->trailingDeleteDaysLabel = (gcnew System::Windows::Forms::Label());
			this->deleteNow = (gcnew System::Windows::Forms::Button());
			this->divider14 = (gcnew System::Windows::Forms::Label());
			this->divider15 = (gcnew System::Windows::Forms::Label());
			this->gameEventsLabel = (gcnew System::Windows::Forms::Label());
			this->gameEvents = (gcnew System::Windows::Forms::CheckBox());
			this->killMessages = (gcnew System::Windows::Forms::CheckBox());
			this->teamSwitch = (gcnew System::Windows::Forms::CheckBox());
			this->warmUp = (gcnew System::Windows::Forms::CheckBox());
			this->playerMedals = (gcnew System::Windows::Forms::CheckBox());
			this->timeStampLabel = (gcnew System::Windows::Forms::Label());
			this->timeStamp = (gcnew System::Windows::Forms::CheckBox());
			this->timeStampSelectionLabel = (gcnew System::Windows::Forms::Label());
			this->timeStampFormat = (gcnew System::Windows::Forms::ComboBox());
			this->teamColorLabel = (gcnew System::Windows::Forms::Label());
			this->chatColorLabel = (gcnew System::Windows::Forms::Label());
			this->chatMessageColor = (gcnew System::Windows::Forms::NumericUpDown());
			this->teamMessageColor = (gcnew System::Windows::Forms::NumericUpDown());
			this->messageColorLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->maxLines))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->linesRemove))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->deleteDays))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chatMessageColor))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->teamMessageColor))->BeginInit();
			this->SuspendLayout();
			// 
			// website
			// 
			this->website->AutoSize = true;
			this->website->Location = System::Drawing::Point(260, 14);
			this->website->Name = L"website";
			this->website->Size = System::Drawing::Size(257, 13);
			this->website->TabIndex = 2;
			this->website->TabStop = true;
			this->website->Text = L"https://github.com/BarelyMiSSeD/Quake-Live-Rcon";
			this->website->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Settings::website_LinkClicked);
			// 
			// statusCommand
			// 
			this->statusCommand->AutoSize = true;
			this->statusCommand->Location = System::Drawing::Point(253, 65);
			this->statusCommand->Name = L"statusCommand";
			this->statusCommand->Size = System::Drawing::Size(265, 17);
			this->statusCommand->TabIndex = 3;
			this->statusCommand->Text = L"Send \'status\' Command on Connect to each server";
			this->statusCommand->UseVisualStyleBackColor = true;
			// 
			// divider1
			// 
			this->divider1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider1->Location = System::Drawing::Point(126, 35);
			this->divider1->Name = L"divider1";
			this->divider1->Size = System::Drawing::Size(270, 2);
			this->divider1->TabIndex = 4;
			// 
			// enableCommand1
			// 
			this->enableCommand1->AutoSize = true;
			this->enableCommand1->Location = System::Drawing::Point(151, 41);
			this->enableCommand1->Name = L"enableCommand1";
			this->enableCommand1->Size = System::Drawing::Size(152, 17);
			this->enableCommand1->TabIndex = 5;
			this->enableCommand1->Text = L"Enable Command Button 1";
			this->enableCommand1->UseVisualStyleBackColor = true;
			// 
			// cmd1BtnLblLabel
			// 
			this->cmd1BtnLblLabel->AutoSize = true;
			this->cmd1BtnLblLabel->Location = System::Drawing::Point(145, 67);
			this->cmd1BtnLblLabel->Name = L"cmd1BtnLblLabel";
			this->cmd1BtnLblLabel->Size = System::Drawing::Size(67, 13);
			this->cmd1BtnLblLabel->TabIndex = 6;
			this->cmd1BtnLblLabel->Text = L"Button Label";
			// 
			// cmd1BtnLabel
			// 
			this->cmd1BtnLabel->Location = System::Drawing::Point(213, 64);
			this->cmd1BtnLabel->Name = L"cmd1BtnLabel";
			this->cmd1BtnLabel->Size = System::Drawing::Size(177, 20);
			this->cmd1BtnLabel->TabIndex = 7;
			// 
			// cmd1BtnCmdLbl
			// 
			this->cmd1BtnCmdLbl->AutoSize = true;
			this->cmd1BtnCmdLbl->Location = System::Drawing::Point(124, 96);
			this->cmd1BtnCmdLbl->Name = L"cmd1BtnCmdLbl";
			this->cmd1BtnCmdLbl->Size = System::Drawing::Size(88, 13);
			this->cmd1BtnCmdLbl->TabIndex = 8;
			this->cmd1BtnCmdLbl->Text = L"Button Command";
			// 
			// cmd1BtnCmd
			// 
			this->cmd1BtnCmd->Location = System::Drawing::Point(213, 93);
			this->cmd1BtnCmd->Name = L"cmd1BtnCmd";
			this->cmd1BtnCmd->Size = System::Drawing::Size(177, 20);
			this->cmd1BtnCmd->TabIndex = 9;
			// 
			// divider2
			// 
			this->divider2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider2->Location = System::Drawing::Point(126, 120);
			this->divider2->Name = L"divider2";
			this->divider2->Size = System::Drawing::Size(270, 2);
			this->divider2->TabIndex = 10;
			// 
			// enableCommand2
			// 
			this->enableCommand2->AutoSize = true;
			this->enableCommand2->Location = System::Drawing::Point(151, 126);
			this->enableCommand2->Name = L"enableCommand2";
			this->enableCommand2->Size = System::Drawing::Size(152, 17);
			this->enableCommand2->TabIndex = 11;
			this->enableCommand2->Text = L"Enable Command Button 2";
			this->enableCommand2->UseVisualStyleBackColor = true;
			// 
			// cmd2BtnLblLabel
			// 
			this->cmd2BtnLblLabel->AutoSize = true;
			this->cmd2BtnLblLabel->Location = System::Drawing::Point(145, 150);
			this->cmd2BtnLblLabel->Name = L"cmd2BtnLblLabel";
			this->cmd2BtnLblLabel->Size = System::Drawing::Size(67, 13);
			this->cmd2BtnLblLabel->TabIndex = 12;
			this->cmd2BtnLblLabel->Text = L"Button Label";
			// 
			// cmd2BtnLabel
			// 
			this->cmd2BtnLabel->Location = System::Drawing::Point(213, 147);
			this->cmd2BtnLabel->Name = L"cmd2BtnLabel";
			this->cmd2BtnLabel->Size = System::Drawing::Size(177, 20);
			this->cmd2BtnLabel->TabIndex = 13;
			// 
			// cmd2BtnCmdLbl
			// 
			this->cmd2BtnCmdLbl->AutoSize = true;
			this->cmd2BtnCmdLbl->Location = System::Drawing::Point(124, 179);
			this->cmd2BtnCmdLbl->Name = L"cmd2BtnCmdLbl";
			this->cmd2BtnCmdLbl->Size = System::Drawing::Size(88, 13);
			this->cmd2BtnCmdLbl->TabIndex = 14;
			this->cmd2BtnCmdLbl->Text = L"Button Command";
			// 
			// cmd2BtnCmd
			// 
			this->cmd2BtnCmd->Location = System::Drawing::Point(213, 176);
			this->cmd2BtnCmd->Name = L"cmd2BtnCmd";
			this->cmd2BtnCmd->Size = System::Drawing::Size(177, 20);
			this->cmd2BtnCmd->TabIndex = 15;
			// 
			// divider3
			// 
			this->divider3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider3->Location = System::Drawing::Point(126, 206);
			this->divider3->Name = L"divider3";
			this->divider3->Size = System::Drawing::Size(270, 2);
			this->divider3->TabIndex = 16;
			// 
			// enableCommand3
			// 
			this->enableCommand3->AutoSize = true;
			this->enableCommand3->Location = System::Drawing::Point(151, 212);
			this->enableCommand3->Name = L"enableCommand3";
			this->enableCommand3->Size = System::Drawing::Size(152, 17);
			this->enableCommand3->TabIndex = 17;
			this->enableCommand3->Text = L"Enable Command Button 3";
			this->enableCommand3->UseVisualStyleBackColor = true;
			// 
			// cmd3BtnCmdLbl
			// 
			this->cmd3BtnCmdLbl->AutoSize = true;
			this->cmd3BtnCmdLbl->Location = System::Drawing::Point(124, 265);
			this->cmd3BtnCmdLbl->Name = L"cmd3BtnCmdLbl";
			this->cmd3BtnCmdLbl->Size = System::Drawing::Size(88, 13);
			this->cmd3BtnCmdLbl->TabIndex = 20;
			this->cmd3BtnCmdLbl->Text = L"Button Command";
			// 
			// cmd3BtnCmd
			// 
			this->cmd3BtnCmd->Location = System::Drawing::Point(213, 262);
			this->cmd3BtnCmd->Name = L"cmd3BtnCmd";
			this->cmd3BtnCmd->Size = System::Drawing::Size(177, 20);
			this->cmd3BtnCmd->TabIndex = 21;
			// 
			// cmd3BtnLblLabel
			// 
			this->cmd3BtnLblLabel->AutoSize = true;
			this->cmd3BtnLblLabel->Location = System::Drawing::Point(145, 236);
			this->cmd3BtnLblLabel->Name = L"cmd3BtnLblLabel";
			this->cmd3BtnLblLabel->Size = System::Drawing::Size(67, 13);
			this->cmd3BtnLblLabel->TabIndex = 18;
			this->cmd3BtnLblLabel->Text = L"Button Label";
			// 
			// cmd3BtnLabel
			// 
			this->cmd3BtnLabel->Location = System::Drawing::Point(213, 233);
			this->cmd3BtnLabel->Name = L"cmd3BtnLabel";
			this->cmd3BtnLabel->Size = System::Drawing::Size(177, 20);
			this->cmd3BtnLabel->TabIndex = 19;
			// 
			// divider4
			// 
			this->divider4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider4->Location = System::Drawing::Point(412, 35);
			this->divider4->Name = L"divider4";
			this->divider4->Size = System::Drawing::Size(270, 2);
			this->divider4->TabIndex = 22;
			// 
			// enableCommand4
			// 
			this->enableCommand4->AutoSize = true;
			this->enableCommand4->Location = System::Drawing::Point(437, 41);
			this->enableCommand4->Name = L"enableCommand4";
			this->enableCommand4->Size = System::Drawing::Size(152, 17);
			this->enableCommand4->TabIndex = 23;
			this->enableCommand4->Text = L"Enable Command Button 4";
			this->enableCommand4->UseVisualStyleBackColor = true;
			// 
			// cmd4BtnCmdLbl
			// 
			this->cmd4BtnCmdLbl->AutoSize = true;
			this->cmd4BtnCmdLbl->Location = System::Drawing::Point(410, 96);
			this->cmd4BtnCmdLbl->Name = L"cmd4BtnCmdLbl";
			this->cmd4BtnCmdLbl->Size = System::Drawing::Size(88, 13);
			this->cmd4BtnCmdLbl->TabIndex = 26;
			this->cmd4BtnCmdLbl->Text = L"Button Command";
			// 
			// cmd4BtnCmd
			// 
			this->cmd4BtnCmd->Location = System::Drawing::Point(499, 93);
			this->cmd4BtnCmd->Name = L"cmd4BtnCmd";
			this->cmd4BtnCmd->Size = System::Drawing::Size(177, 20);
			this->cmd4BtnCmd->TabIndex = 27;
			// 
			// cmd4BtnLblLabel
			// 
			this->cmd4BtnLblLabel->AutoSize = true;
			this->cmd4BtnLblLabel->Location = System::Drawing::Point(431, 67);
			this->cmd4BtnLblLabel->Name = L"cmd4BtnLblLabel";
			this->cmd4BtnLblLabel->Size = System::Drawing::Size(67, 13);
			this->cmd4BtnLblLabel->TabIndex = 24;
			this->cmd4BtnLblLabel->Text = L"Button Label";
			// 
			// cmd4BtnLabel
			// 
			this->cmd4BtnLabel->Location = System::Drawing::Point(499, 64);
			this->cmd4BtnLabel->Name = L"cmd4BtnLabel";
			this->cmd4BtnLabel->Size = System::Drawing::Size(177, 20);
			this->cmd4BtnLabel->TabIndex = 25;
			// 
			// divider5
			// 
			this->divider5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider5->Location = System::Drawing::Point(412, 120);
			this->divider5->Name = L"divider5";
			this->divider5->Size = System::Drawing::Size(270, 2);
			this->divider5->TabIndex = 28;
			// 
			// enableCommand5
			// 
			this->enableCommand5->AutoSize = true;
			this->enableCommand5->Location = System::Drawing::Point(437, 126);
			this->enableCommand5->Name = L"enableCommand5";
			this->enableCommand5->Size = System::Drawing::Size(152, 17);
			this->enableCommand5->TabIndex = 29;
			this->enableCommand5->Text = L"Enable Command Button 5";
			this->enableCommand5->UseVisualStyleBackColor = true;
			// 
			// cmd5BtnCmdLbl
			// 
			this->cmd5BtnCmdLbl->AutoSize = true;
			this->cmd5BtnCmdLbl->Location = System::Drawing::Point(410, 179);
			this->cmd5BtnCmdLbl->Name = L"cmd5BtnCmdLbl";
			this->cmd5BtnCmdLbl->Size = System::Drawing::Size(88, 13);
			this->cmd5BtnCmdLbl->TabIndex = 32;
			this->cmd5BtnCmdLbl->Text = L"Button Command";
			// 
			// cmd5BtnCmd
			// 
			this->cmd5BtnCmd->Location = System::Drawing::Point(499, 176);
			this->cmd5BtnCmd->Name = L"cmd5BtnCmd";
			this->cmd5BtnCmd->Size = System::Drawing::Size(177, 20);
			this->cmd5BtnCmd->TabIndex = 33;
			// 
			// cmd5BtnLblLabel
			// 
			this->cmd5BtnLblLabel->AutoSize = true;
			this->cmd5BtnLblLabel->Location = System::Drawing::Point(431, 150);
			this->cmd5BtnLblLabel->Name = L"cmd5BtnLblLabel";
			this->cmd5BtnLblLabel->Size = System::Drawing::Size(67, 13);
			this->cmd5BtnLblLabel->TabIndex = 30;
			this->cmd5BtnLblLabel->Text = L"Button Label";
			// 
			// cmd5BtnLabel
			// 
			this->cmd5BtnLabel->Location = System::Drawing::Point(499, 147);
			this->cmd5BtnLabel->Name = L"cmd5BtnLabel";
			this->cmd5BtnLabel->Size = System::Drawing::Size(177, 20);
			this->cmd5BtnLabel->TabIndex = 31;
			// 
			// divider6
			// 
			this->divider6->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider6->Location = System::Drawing::Point(412, 206);
			this->divider6->Name = L"divider6";
			this->divider6->Size = System::Drawing::Size(270, 2);
			this->divider6->TabIndex = 34;
			// 
			// enableCommand6
			// 
			this->enableCommand6->AutoSize = true;
			this->enableCommand6->Location = System::Drawing::Point(437, 212);
			this->enableCommand6->Name = L"enableCommand6";
			this->enableCommand6->Size = System::Drawing::Size(152, 17);
			this->enableCommand6->TabIndex = 35;
			this->enableCommand6->Text = L"Enable Command Button 6";
			this->enableCommand6->UseVisualStyleBackColor = true;
			// 
			// cmd6BtnCmdLbl
			// 
			this->cmd6BtnCmdLbl->AutoSize = true;
			this->cmd6BtnCmdLbl->Location = System::Drawing::Point(410, 265);
			this->cmd6BtnCmdLbl->Name = L"cmd6BtnCmdLbl";
			this->cmd6BtnCmdLbl->Size = System::Drawing::Size(88, 13);
			this->cmd6BtnCmdLbl->TabIndex = 38;
			this->cmd6BtnCmdLbl->Text = L"Button Command";
			// 
			// cmd6BtnCmd
			// 
			this->cmd6BtnCmd->Location = System::Drawing::Point(499, 262);
			this->cmd6BtnCmd->Name = L"cmd6BtnCmd";
			this->cmd6BtnCmd->Size = System::Drawing::Size(177, 20);
			this->cmd6BtnCmd->TabIndex = 39;
			// 
			// cmd6BtnLblLabel
			// 
			this->cmd6BtnLblLabel->AutoSize = true;
			this->cmd6BtnLblLabel->Location = System::Drawing::Point(431, 236);
			this->cmd6BtnLblLabel->Name = L"cmd6BtnLblLabel";
			this->cmd6BtnLblLabel->Size = System::Drawing::Size(67, 13);
			this->cmd6BtnLblLabel->TabIndex = 36;
			this->cmd6BtnLblLabel->Text = L"Button Label";
			// 
			// cmd6BtnLabel
			// 
			this->cmd6BtnLabel->Location = System::Drawing::Point(499, 233);
			this->cmd6BtnLabel->Name = L"cmd6BtnLabel";
			this->cmd6BtnLabel->Size = System::Drawing::Size(177, 20);
			this->cmd6BtnLabel->TabIndex = 37;
			// 
			// verticalDivider
			// 
			this->verticalDivider->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->verticalDivider->Location = System::Drawing::Point(403, 35);
			this->verticalDivider->Name = L"verticalDivider";
			this->verticalDivider->Size = System::Drawing::Size(2, 255);
			this->verticalDivider->TabIndex = 40;
			// 
			// versionLabel
			// 
			this->versionLabel->AutoSize = true;
			this->versionLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->versionLabel->Location = System::Drawing::Point(12, 9);
			this->versionLabel->Name = L"versionLabel";
			this->versionLabel->Size = System::Drawing::Size(71, 20);
			this->versionLabel->TabIndex = 41;
			this->versionLabel->Text = L"Version: ";
			// 
			// divider7
			// 
			this->divider7->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider7->Location = System::Drawing::Point(126, 292);
			this->divider7->Name = L"divider7";
			this->divider7->Size = System::Drawing::Size(270, 2);
			this->divider7->TabIndex = 44;
			// 
			// divider8
			// 
			this->divider8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider8->Location = System::Drawing::Point(412, 292);
			this->divider8->Name = L"divider8";
			this->divider8->Size = System::Drawing::Size(270, 2);
			this->divider8->TabIndex = 45;
			// 
			// connectGameButtonLabel1
			// 
			this->connectGameButtonLabel1->AutoSize = true;
			this->connectGameButtonLabel1->Location = System::Drawing::Point(176, 94);
			this->connectGameButtonLabel1->Name = L"connectGameButtonLabel1";
			this->connectGameButtonLabel1->Size = System::Drawing::Size(423, 26);
			this->connectGameButtonLabel1->TabIndex = 46;
			this->connectGameButtonLabel1->Text = L"The Connect Game Buton will launch Quake Live through Steam and connect the game\n"
				L"  to the game server, if the RCON connection is established.";
			this->connectGameButtonLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// enableConnectToGame
			// 
			this->enableConnectToGame->AutoSize = true;
			this->enableConnectToGame->Location = System::Drawing::Point(263, 123);
			this->enableConnectToGame->Name = L"enableConnectToGame";
			this->enableConnectToGame->Size = System::Drawing::Size(217, 17);
			this->enableConnectToGame->TabIndex = 47;
			this->enableConnectToGame->Text = L"Enable \'Connect to Game Server\' Button";
			this->enableConnectToGame->UseVisualStyleBackColor = true;
			// 
			// divider9
			// 
			this->divider9->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider9->Location = System::Drawing::Point(126, 232);
			this->divider9->Name = L"divider9";
			this->divider9->Size = System::Drawing::Size(555, 2);
			this->divider9->TabIndex = 48;
			// 
			// save
			// 
			this->save->Location = System::Drawing::Point(272, 303);
			this->save->Name = L"save";
			this->save->Size = System::Drawing::Size(75, 23);
			this->save->TabIndex = 42;
			this->save->Text = L"Save";
			this->save->UseVisualStyleBackColor = true;
			this->save->Click += gcnew System::EventHandler(this, &Settings::save_Click);
			// 
			// cancel
			// 
			this->cancel->Location = System::Drawing::Point(409, 303);
			this->cancel->Name = L"cancel";
			this->cancel->Size = System::Drawing::Size(75, 23);
			this->cancel->TabIndex = 43;
			this->cancel->Text = L"Cancel";
			this->cancel->UseVisualStyleBackColor = true;
			this->cancel->Click += gcnew System::EventHandler(this, &Settings::cancel_Click);
			// 
			// stripColorsLabel
			// 
			this->stripColorsLabel->AutoSize = true;
			this->stripColorsLabel->Location = System::Drawing::Point(246, 247);
			this->stripColorsLabel->Name = L"stripColorsLabel";
			this->stripColorsLabel->Size = System::Drawing::Size(271, 26);
			this->stripColorsLabel->TabIndex = 49;
			this->stripColorsLabel->Text = L"This will strip the color codes from the log file.\nThe log file is still a .txt f"
				L"ile so the text will not be colored.";
			this->stripColorsLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// stripColors
			// 
			this->stripColors->AutoSize = true;
			this->stripColors->Location = System::Drawing::Point(272, 276);
			this->stripColors->Name = L"stripColors";
			this->stripColors->Size = System::Drawing::Size(222, 17);
			this->stripColors->TabIndex = 50;
			this->stripColors->Text = L"Enable stripping color codes from Log File";
			this->stripColors->UseVisualStyleBackColor = true;
			// 
			// divider0
			// 
			this->divider0->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider0->Location = System::Drawing::Point(125, 85);
			this->divider0->Name = L"divider0";
			this->divider0->Size = System::Drawing::Size(555, 2);
			this->divider0->TabIndex = 51;
			// 
			// autoScrollLabel
			// 
			this->autoScrollLabel->AutoSize = true;
			this->autoScrollLabel->Location = System::Drawing::Point(243, 39);
			this->autoScrollLabel->Name = L"autoScrollLabel";
			this->autoScrollLabel->Size = System::Drawing::Size(312, 13);
			this->autoScrollLabel->TabIndex = 52;
			this->autoScrollLabel->Text = L"This will stop the automatic scrolling of the server output window.";
			// 
			// disableScroll
			// 
			this->disableScroll->AutoSize = true;
			this->disableScroll->Location = System::Drawing::Point(330, 55);
			this->disableScroll->Name = L"disableScroll";
			this->disableScroll->Size = System::Drawing::Size(115, 17);
			this->disableScroll->TabIndex = 53;
			this->disableScroll->Text = L"Disable Auto Scroll";
			this->disableScroll->UseVisualStyleBackColor = true;
			// 
			// divider10
			// 
			this->divider10->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider10->Location = System::Drawing::Point(129, 93);
			this->divider10->Name = L"divider10";
			this->divider10->Size = System::Drawing::Size(555, 2);
			this->divider10->TabIndex = 54;
			// 
			// maxLinesLabel
			// 
			this->maxLinesLabel->AutoSize = true;
			this->maxLinesLabel->Location = System::Drawing::Point(261, 107);
			this->maxLinesLabel->Name = L"maxLinesLabel";
			this->maxLinesLabel->Size = System::Drawing::Size(320, 13);
			this->maxLinesLabel->TabIndex = 55;
			this->maxLinesLabel->Text = L"The Maximum Amount of lines allowed in the server output window";
			// 
			// maxLines
			// 
			this->maxLines->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->maxLines->Location = System::Drawing::Point(584, 104);
			this->maxLines->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->maxLines->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 500, 0, 0, 0 });
			this->maxLines->Name = L"maxLines";
			this->maxLines->Size = System::Drawing::Size(83, 20);
			this->maxLines->TabIndex = 56;
			this->maxLines->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->maxLines->ThousandsSeparator = true;
			this->maxLines->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6000, 0, 0, 0 });
			// 
			// linesRemoveLabel
			// 
			this->linesRemoveLabel->AutoSize = true;
			this->linesRemoveLabel->Location = System::Drawing::Point(134, 136);
			this->linesRemoveLabel->Name = L"linesRemoveLabel";
			this->linesRemoveLabel->Size = System::Drawing::Size(448, 13);
			this->linesRemoveLabel->TabIndex = 57;
			this->linesRemoveLabel->Text = L"The amount of lines to remove when the Maximum Amount of lines allowed number is "
				L"reached";
			// 
			// linesRemove
			// 
			this->linesRemove->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->linesRemove->Location = System::Drawing::Point(584, 133);
			this->linesRemove->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->linesRemove->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 50, 0, 0, 0 });
			this->linesRemove->Name = L"linesRemove";
			this->linesRemove->Size = System::Drawing::Size(83, 20);
			this->linesRemove->TabIndex = 58;
			this->linesRemove->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->linesRemove->ThousandsSeparator = true;
			this->linesRemove->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			// 
			// divider11
			// 
			this->divider11->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider11->Location = System::Drawing::Point(126, 194);
			this->divider11->Name = L"divider11";
			this->divider11->Size = System::Drawing::Size(555, 2);
			this->divider11->TabIndex = 59;
			// 
			// linesRecommendLabel
			// 
			this->linesRecommendLabel->AutoSize = true;
			this->linesRecommendLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Italic,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->linesRecommendLabel->Location = System::Drawing::Point(149, 160);
			this->linesRecommendLabel->Name = L"linesRecommendLabel";
			this->linesRecommendLabel->Size = System::Drawing::Size(502, 26);
			this->linesRecommendLabel->TabIndex = 60;
			this->linesRecommendLabel->Text = L"Note: Setting the lines to remove at about 10% of the maximumline amount should b"
				L"e good. If these\nnumbers are edited watch memory consumption and processor usage"
				L" to see if the values are satisfactory.";
			// 
			// reset
			// 
			this->reset->Location = System::Drawing::Point(3, 303);
			this->reset->Name = L"reset";
			this->reset->Size = System::Drawing::Size(132, 23);
			this->reset->TabIndex = 61;
			this->reset->Text = L"Reset Values to Default";
			this->reset->UseVisualStyleBackColor = true;
			this->reset->Click += gcnew System::EventHandler(this, &Settings::reset_Click);
			// 
			// menuSelection
			// 
			this->menuSelection->FormattingEnabled = true;
			this->menuSelection->Location = System::Drawing::Point(3, 35);
			this->menuSelection->Name = L"menuSelection";
			this->menuSelection->Size = System::Drawing::Size(120, 264);
			this->menuSelection->TabIndex = 62;
			this->menuSelection->SelectedIndexChanged += gcnew System::EventHandler(this, &Settings::menuSelection_SelectedIndexChanged);
			// 
			// statusCmdLabel
			// 
			this->statusCmdLabel->AutoSize = true;
			this->statusCmdLabel->Location = System::Drawing::Point(206, 36);
			this->statusCmdLabel->Name = L"statusCmdLabel";
			this->statusCmdLabel->Size = System::Drawing::Size(370, 26);
			this->statusCmdLabel->TabIndex = 63;
			this->statusCmdLabel->Text = L"This will automatically send a status command to the server when connection\nand r"
				L"esgistration has been completed.";
			this->statusCmdLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// enableLogging
			// 
			this->enableLogging->AutoSize = true;
			this->enableLogging->Location = System::Drawing::Point(323, 55);
			this->enableLogging->Name = L"enableLogging";
			this->enableLogging->Size = System::Drawing::Size(100, 17);
			this->enableLogging->TabIndex = 64;
			this->enableLogging->Text = L"Enable Logging";
			this->enableLogging->UseVisualStyleBackColor = true;
			// 
			// enableLoggingLabel1
			// 
			this->enableLoggingLabel1->AutoSize = true;
			this->enableLoggingLabel1->Location = System::Drawing::Point(195, 75);
			this->enableLoggingLabel1->Name = L"enableLoggingLabel1";
			this->enableLoggingLabel1->Size = System::Drawing::Size(399, 13);
			this->enableLoggingLabel1->TabIndex = 65;
			this->enableLoggingLabel1->Text = L"If enabled, the servers that have \'Log RCON info to file\' selected will perform l"
				L"oging.";
			// 
			// enableLoggingLabel2
			// 
			this->enableLoggingLabel2->AutoSize = true;
			this->enableLoggingLabel2->Location = System::Drawing::Point(198, 88);
			this->enableLoggingLabel2->Name = L"enableLoggingLabel2";
			this->enableLoggingLabel2->Size = System::Drawing::Size(392, 13);
			this->enableLoggingLabel2->TabIndex = 66;
			this->enableLoggingLabel2->Text = L"If disabled, logging will not happen even if the individual server logging is ena"
				L"bled.";
			// 
			// connectGameButtonLabel2
			// 
			this->connectGameButtonLabel2->AutoSize = true;
			this->connectGameButtonLabel2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Italic,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->connectGameButtonLabel2->Location = System::Drawing::Point(210, 143);
			this->connectGameButtonLabel2->Name = L"connectGameButtonLabel2";
			this->connectGameButtonLabel2->Size = System::Drawing::Size(329, 13);
			this->connectGameButtonLabel2->TabIndex = 64;
			this->connectGameButtonLabel2->Text = L"Note: The button is only visible when at least one server tab is open.";
			// 
			// autoScrollNoteLabel
			// 
			this->autoScrollNoteLabel->AutoSize = true;
			this->autoScrollNoteLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Italic,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->autoScrollNoteLabel->Location = System::Drawing::Point(180, 72);
			this->autoScrollNoteLabel->Name = L"autoScrollNoteLabel";
			this->autoScrollNoteLabel->Size = System::Drawing::Size(460, 13);
			this->autoScrollNoteLabel->TabIndex = 63;
			this->autoScrollNoteLabel->Text = L"Note: This can be enabled/disabled while connected to a server to allow output wi"
				L"ndow reading";
			// 
			// color0Label
			// 
			this->color0Label->AutoSize = true;
			this->color0Label->Location = System::Drawing::Point(182, 88);
			this->color0Label->Name = L"color0Label";
			this->color0Label->Size = System::Drawing::Size(76, 13);
			this->color0Label->TabIndex = 63;
			this->color0Label->Text = L"Color 0 (Black)";
			// 
			// color0Box
			// 
			this->color0Box->BackColor = System::Drawing::Color::Black;
			this->color0Box->Location = System::Drawing::Point(158, 104);
			this->color0Box->Name = L"color0Box";
			this->color0Box->Size = System::Drawing::Size(100, 20);
			this->color0Box->TabIndex = 64;
			this->color0Box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// color0Button
			// 
			this->color0Button->Location = System::Drawing::Point(260, 105);
			this->color0Button->Name = L"color0Button";
			this->color0Button->Size = System::Drawing::Size(24, 20);
			this->color0Button->TabIndex = 65;
			this->color0Button->Text = L"...";
			this->color0Button->UseVisualStyleBackColor = true;
			this->color0Button->Click += gcnew System::EventHandler(this, &Settings::color0Button_Click);
			// 
			// color1Button
			// 
			this->color1Button->Location = System::Drawing::Point(260, 163);
			this->color1Button->Name = L"color1Button";
			this->color1Button->Size = System::Drawing::Size(24, 20);
			this->color1Button->TabIndex = 68;
			this->color1Button->Text = L"...";
			this->color1Button->UseVisualStyleBackColor = true;
			this->color1Button->Click += gcnew System::EventHandler(this, &Settings::color1Button_Click);
			// 
			// color1Box
			// 
			this->color1Box->BackColor = System::Drawing::Color::Black;
			this->color1Box->Location = System::Drawing::Point(158, 162);
			this->color1Box->Name = L"color1Box";
			this->color1Box->Size = System::Drawing::Size(100, 20);
			this->color1Box->TabIndex = 67;
			this->color1Box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// color1Label
			// 
			this->color1Label->AutoSize = true;
			this->color1Label->Location = System::Drawing::Point(182, 146);
			this->color1Label->Name = L"color1Label";
			this->color1Label->Size = System::Drawing::Size(69, 13);
			this->color1Label->TabIndex = 66;
			this->color1Label->Text = L"Color 1 (Red)";
			// 
			// color2Button
			// 
			this->color2Button->Location = System::Drawing::Point(260, 221);
			this->color2Button->Name = L"color2Button";
			this->color2Button->Size = System::Drawing::Size(24, 20);
			this->color2Button->TabIndex = 71;
			this->color2Button->Text = L"...";
			this->color2Button->UseVisualStyleBackColor = true;
			this->color2Button->Click += gcnew System::EventHandler(this, &Settings::color2Button_Click);
			// 
			// color2Box
			// 
			this->color2Box->BackColor = System::Drawing::Color::Black;
			this->color2Box->Location = System::Drawing::Point(158, 220);
			this->color2Box->Name = L"color2Box";
			this->color2Box->Size = System::Drawing::Size(100, 20);
			this->color2Box->TabIndex = 70;
			this->color2Box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// color2Label
			// 
			this->color2Label->AutoSize = true;
			this->color2Label->Location = System::Drawing::Point(182, 204);
			this->color2Label->Name = L"color2Label";
			this->color2Label->Size = System::Drawing::Size(78, 13);
			this->color2Label->TabIndex = 69;
			this->color2Label->Text = L"Color 2 (Green)";
			// 
			// color8Button
			// 
			this->color8Button->Location = System::Drawing::Point(610, 221);
			this->color8Button->Name = L"color8Button";
			this->color8Button->Size = System::Drawing::Size(24, 20);
			this->color8Button->TabIndex = 89;
			this->color8Button->Text = L"...";
			this->color8Button->UseVisualStyleBackColor = true;
			this->color8Button->Click += gcnew System::EventHandler(this, &Settings::color8Button_Click);
			// 
			// color8Box
			// 
			this->color8Box->BackColor = System::Drawing::Color::Black;
			this->color8Box->Location = System::Drawing::Point(508, 220);
			this->color8Box->Name = L"color8Box";
			this->color8Box->Size = System::Drawing::Size(100, 20);
			this->color8Box->TabIndex = 88;
			this->color8Box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// color8Label
			// 
			this->color8Label->AutoSize = true;
			this->color8Label->Location = System::Drawing::Point(523, 204);
			this->color8Label->Name = L"color8Label";
			this->color8Label->Size = System::Drawing::Size(76, 13);
			this->color8Label->TabIndex = 87;
			this->color8Label->Text = L"Color 8 (Black)";
			// 
			// color3Button
			// 
			this->color3Button->Location = System::Drawing::Point(436, 105);
			this->color3Button->Name = L"color3Button";
			this->color3Button->Size = System::Drawing::Size(24, 20);
			this->color3Button->TabIndex = 74;
			this->color3Button->Text = L"...";
			this->color3Button->UseVisualStyleBackColor = true;
			this->color3Button->Click += gcnew System::EventHandler(this, &Settings::color3Button_Click);
			// 
			// color3Box
			// 
			this->color3Box->BackColor = System::Drawing::Color::Black;
			this->color3Box->Location = System::Drawing::Point(334, 104);
			this->color3Box->Name = L"color3Box";
			this->color3Box->Size = System::Drawing::Size(100, 20);
			this->color3Box->TabIndex = 73;
			this->color3Box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// color3Label
			// 
			this->color3Label->AutoSize = true;
			this->color3Label->Location = System::Drawing::Point(348, 88);
			this->color3Label->Name = L"color3Label";
			this->color3Label->Size = System::Drawing::Size(80, 13);
			this->color3Label->TabIndex = 72;
			this->color3Label->Text = L"Color 3 (Yellow)";
			// 
			// color4Button
			// 
			this->color4Button->Location = System::Drawing::Point(436, 163);
			this->color4Button->Name = L"color4Button";
			this->color4Button->Size = System::Drawing::Size(24, 20);
			this->color4Button->TabIndex = 77;
			this->color4Button->Text = L"...";
			this->color4Button->UseVisualStyleBackColor = true;
			this->color4Button->Click += gcnew System::EventHandler(this, &Settings::color4Button_Click);
			// 
			// color4Box
			// 
			this->color4Box->BackColor = System::Drawing::Color::Black;
			this->color4Box->Location = System::Drawing::Point(334, 162);
			this->color4Box->Name = L"color4Box";
			this->color4Box->Size = System::Drawing::Size(100, 20);
			this->color4Box->TabIndex = 76;
			this->color4Box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// color4Label
			// 
			this->color4Label->AutoSize = true;
			this->color4Label->Location = System::Drawing::Point(358, 146);
			this->color4Label->Name = L"color4Label";
			this->color4Label->Size = System::Drawing::Size(70, 13);
			this->color4Label->TabIndex = 75;
			this->color4Label->Text = L"Color 4 (Blue)";
			// 
			// color5Button
			// 
			this->color5Button->Location = System::Drawing::Point(436, 221);
			this->color5Button->Name = L"color5Button";
			this->color5Button->Size = System::Drawing::Size(24, 20);
			this->color5Button->TabIndex = 80;
			this->color5Button->Text = L"...";
			this->color5Button->UseVisualStyleBackColor = true;
			this->color5Button->Click += gcnew System::EventHandler(this, &Settings::color5Button_Click);
			// 
			// color5Box
			// 
			this->color5Box->BackColor = System::Drawing::Color::Black;
			this->color5Box->Location = System::Drawing::Point(334, 220);
			this->color5Box->Name = L"color5Box";
			this->color5Box->Size = System::Drawing::Size(100, 20);
			this->color5Box->TabIndex = 79;
			this->color5Box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// color5Label
			// 
			this->color5Label->AutoSize = true;
			this->color5Label->Location = System::Drawing::Point(358, 204);
			this->color5Label->Name = L"color5Label";
			this->color5Label->Size = System::Drawing::Size(73, 13);
			this->color5Label->TabIndex = 78;
			this->color5Label->Text = L"Color 5 (Cyan)";
			// 
			// color7Button
			// 
			this->color7Button->Location = System::Drawing::Point(610, 163);
			this->color7Button->Name = L"color7Button";
			this->color7Button->Size = System::Drawing::Size(24, 20);
			this->color7Button->TabIndex = 86;
			this->color7Button->Text = L"...";
			this->color7Button->UseVisualStyleBackColor = true;
			this->color7Button->Click += gcnew System::EventHandler(this, &Settings::color7Button_Click);
			// 
			// color7Box
			// 
			this->color7Box->BackColor = System::Drawing::Color::Black;
			this->color7Box->Location = System::Drawing::Point(509, 162);
			this->color7Box->Name = L"color7Box";
			this->color7Box->Size = System::Drawing::Size(100, 20);
			this->color7Box->TabIndex = 85;
			this->color7Box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// color7Label
			// 
			this->color7Label->AutoSize = true;
			this->color7Label->Location = System::Drawing::Point(523, 146);
			this->color7Label->Name = L"color7Label";
			this->color7Label->Size = System::Drawing::Size(77, 13);
			this->color7Label->TabIndex = 84;
			this->color7Label->Text = L"Color 7 (White)";
			// 
			// color6Button
			// 
			this->color6Button->Location = System::Drawing::Point(610, 105);
			this->color6Button->Name = L"color6Button";
			this->color6Button->Size = System::Drawing::Size(24, 20);
			this->color6Button->TabIndex = 83;
			this->color6Button->Text = L"...";
			this->color6Button->UseVisualStyleBackColor = true;
			this->color6Button->Click += gcnew System::EventHandler(this, &Settings::color6Button_Click);
			// 
			// color6Box
			// 
			this->color6Box->BackColor = System::Drawing::Color::Black;
			this->color6Box->Location = System::Drawing::Point(509, 104);
			this->color6Box->Name = L"color6Box";
			this->color6Box->Size = System::Drawing::Size(100, 20);
			this->color6Box->TabIndex = 82;
			this->color6Box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// color6Label
			// 
			this->color6Label->AutoSize = true;
			this->color6Label->Location = System::Drawing::Point(523, 88);
			this->color6Label->Name = L"color6Label";
			this->color6Label->Size = System::Drawing::Size(79, 13);
			this->color6Label->TabIndex = 81;
			this->color6Label->Text = L"Color 6 (Purple)";
			// 
			// colorLabel
			// 
			this->colorLabel->AutoSize = true;
			this->colorLabel->Location = System::Drawing::Point(247, 35);
			this->colorLabel->Name = L"colorLabel";
			this->colorLabel->Size = System::Drawing::Size(270, 26);
			this->colorLabel->TabIndex = 90;
			this->colorLabel->Text = L"These are the colors that will be shown in the messages\nfrom the serever that use"
				L" Quake Live Color coding.";
			this->colorLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// divider13
			// 
			this->divider13->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider13->Location = System::Drawing::Point(125, 163);
			this->divider13->Name = L"divider13";
			this->divider13->Size = System::Drawing::Size(555, 2);
			this->divider13->TabIndex = 65;
			// 
			// keepAliveLabel
			// 
			this->keepAliveLabel->AutoSize = true;
			this->keepAliveLabel->Location = System::Drawing::Point(206, 171);
			this->keepAliveLabel->Name = L"keepAliveLabel";
			this->keepAliveLabel->Size = System::Drawing::Size(432, 13);
			this->keepAliveLabel->TabIndex = 66;
			this->keepAliveLabel->Text = L"This will keep the computer from going in an inactive state when any server tabs "
				L"are open.";
			// 
			// keepAlive
			// 
			this->keepAlive->AutoSize = true;
			this->keepAlive->Location = System::Drawing::Point(250, 188);
			this->keepAlive->Name = L"keepAlive";
			this->keepAlive->Size = System::Drawing::Size(240, 17);
			this->keepAlive->TabIndex = 67;
			this->keepAlive->Text = L"Keep Computer from entering any sleep mode";
			this->keepAlive->UseVisualStyleBackColor = true;
			// 
			// keepAliveNote
			// 
			this->keepAliveNote->AutoSize = true;
			this->keepAliveNote->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->keepAliveNote->Location = System::Drawing::Point(217, 208);
			this->keepAliveNote->Name = L"keepAliveNote";
			this->keepAliveNote->Size = System::Drawing::Size(312, 13);
			this->keepAliveNote->TabIndex = 68;
			this->keepAliveNote->Text = L"Note: This will still allow the monitor to go into screensaver mode.";
			// 
			// colorNote
			// 
			this->colorNote->AutoSize = true;
			this->colorNote->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->colorNote->Location = System::Drawing::Point(150, 70);
			this->colorNote->Name = L"colorNote";
			this->colorNote->Size = System::Drawing::Size(484, 13);
			this->colorNote->TabIndex = 91;
			this->colorNote->Text = L"Note: The color codes need to be entered in HTML tags (like \'Red\') or in Color Co"
				L"de (like the default).";
			// 
			// logFiles
			// 
			this->logFiles->Location = System::Drawing::Point(313, 104);
			this->logFiles->Name = L"logFiles";
			this->logFiles->Size = System::Drawing::Size(119, 23);
			this->logFiles->TabIndex = 67;
			this->logFiles->Text = L"Open Log File Folder";
			this->logFiles->UseVisualStyleBackColor = true;
			this->logFiles->Click += gcnew System::EventHandler(this, &Settings::logFiles_Click);
			// 
			// deleteOldLabel
			// 
			this->deleteOldLabel->AutoSize = true;
			this->deleteOldLabel->Location = System::Drawing::Point(150, 154);
			this->deleteOldLabel->Name = L"deleteOldLabel";
			this->deleteOldLabel->Size = System::Drawing::Size(399, 13);
			this->deleteOldLabel->TabIndex = 68;
			this->deleteOldLabel->Text = L"Automatically Delete Log Files older than the set days when the Quake Live Rcon p"
				L"rogram starts.";
			// 
			// automaticFileDelete
			// 
			this->automaticFileDelete->AutoSize = true;
			this->automaticFileDelete->Location = System::Drawing::Point(284, 171);
			this->automaticFileDelete->Name = L"automaticFileDelete";
			this->automaticFileDelete->Size = System::Drawing::Size(191, 17);
			this->automaticFileDelete->TabIndex = 69;
			this->automaticFileDelete->Text = L"Enable Automatic Log File Deleting";
			this->automaticFileDelete->UseVisualStyleBackColor = true;
			// 
			// deleteDays
			// 
			this->deleteDays->Location = System::Drawing::Point(347, 198);
			this->deleteDays->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->deleteDays->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->deleteDays->Name = L"deleteDays";
			this->deleteDays->Size = System::Drawing::Size(64, 20);
			this->deleteDays->TabIndex = 70;
			this->deleteDays->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->deleteDays->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
			// 
			// leadingDeleteDaysLabel
			// 
			this->leadingDeleteDaysLabel->AutoSize = true;
			this->leadingDeleteDaysLabel->Location = System::Drawing::Point(151, 201);
			this->leadingDeleteDaysLabel->Name = L"leadingDeleteDaysLabel";
			this->leadingDeleteDaysLabel->Size = System::Drawing::Size(196, 13);
			this->leadingDeleteDaysLabel->TabIndex = 71;
			this->leadingDeleteDaysLabel->Text = L"Delete files in log file directory older than";
			// 
			// trailingDeleteDaysLabel
			// 
			this->trailingDeleteDaysLabel->AutoSize = true;
			this->trailingDeleteDaysLabel->Location = System::Drawing::Point(417, 201);
			this->trailingDeleteDaysLabel->Name = L"trailingDeleteDaysLabel";
			this->trailingDeleteDaysLabel->Size = System::Drawing::Size(34, 13);
			this->trailingDeleteDaysLabel->TabIndex = 72;
			this->trailingDeleteDaysLabel->Text = L"Days.";
			// 
			// deleteNow
			// 
			this->deleteNow->Location = System::Drawing::Point(469, 196);
			this->deleteNow->Name = L"deleteNow";
			this->deleteNow->Size = System::Drawing::Size(121, 23);
			this->deleteNow->TabIndex = 73;
			this->deleteNow->Text = L"Delete Old Files Now";
			this->deleteNow->UseVisualStyleBackColor = true;
			this->deleteNow->Click += gcnew System::EventHandler(this, &Settings::deleteNow_Click);
			// 
			// divider14
			// 
			this->divider14->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider14->Location = System::Drawing::Point(126, 139);
			this->divider14->Name = L"divider14";
			this->divider14->Size = System::Drawing::Size(555, 2);
			this->divider14->TabIndex = 74;
			// 
			// divider15
			// 
			this->divider15->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->divider15->Location = System::Drawing::Point(129, 83);
			this->divider15->Name = L"divider15";
			this->divider15->Size = System::Drawing::Size(555, 2);
			this->divider15->TabIndex = 69;
			// 
			// gameEventsLabel
			// 
			this->gameEventsLabel->AutoSize = true;
			this->gameEventsLabel->Location = System::Drawing::Point(250, 46);
			this->gameEventsLabel->Name = L"gameEventsLabel";
			this->gameEventsLabel->Size = System::Drawing::Size(293, 13);
			this->gameEventsLabel->TabIndex = 70;
			this->gameEventsLabel->Text = L"This is the Global enable/disable for the events on this page.";
			// 
			// gameEvents
			// 
			this->gameEvents->AutoSize = true;
			this->gameEvents->Location = System::Drawing::Point(321, 63);
			this->gameEvents->Name = L"gameEvents";
			this->gameEvents->Size = System::Drawing::Size(126, 17);
			this->gameEvents->TabIndex = 71;
			this->gameEvents->Text = L"Enable Game Events";
			this->gameEvents->UseVisualStyleBackColor = true;
			// 
			// killMessages
			// 
			this->killMessages->AutoSize = true;
			this->killMessages->Location = System::Drawing::Point(197, 97);
			this->killMessages->Name = L"killMessages";
			this->killMessages->Size = System::Drawing::Size(185, 17);
			this->killMessages->TabIndex = 72;
			this->killMessages->Text = L"Show Player Kill/Death messages";
			this->killMessages->UseVisualStyleBackColor = true;
			// 
			// teamSwitch
			// 
			this->teamSwitch->AutoSize = true;
			this->teamSwitch->Location = System::Drawing::Point(197, 121);
			this->teamSwitch->Name = L"teamSwitch";
			this->teamSwitch->Size = System::Drawing::Size(168, 17);
			this->teamSwitch->TabIndex = 73;
			this->teamSwitch->Text = L"Show Team Switch messages";
			this->teamSwitch->UseVisualStyleBackColor = true;
			// 
			// warmUp
			// 
			this->warmUp->AutoSize = true;
			this->warmUp->Location = System::Drawing::Point(416, 97);
			this->warmUp->Name = L"warmUp";
			this->warmUp->Size = System::Drawing::Size(171, 17);
			this->warmUp->TabIndex = 74;
			this->warmUp->Text = L"Display Messages in \'WarmUp\'";
			this->warmUp->UseVisualStyleBackColor = true;
			// 
			// playerMedals
			// 
			this->playerMedals->AutoSize = true;
			this->playerMedals->Location = System::Drawing::Point(197, 145);
			this->playerMedals->Name = L"playerMedals";
			this->playerMedals->Size = System::Drawing::Size(122, 17);
			this->playerMedals->TabIndex = 75;
			this->playerMedals->Text = L"Show Player Medals";
			this->playerMedals->UseVisualStyleBackColor = true;
			// 
			// timeStampLabel
			// 
			this->timeStampLabel->AutoSize = true;
			this->timeStampLabel->Location = System::Drawing::Point(199, 202);
			this->timeStampLabel->Name = L"timeStampLabel";
			this->timeStampLabel->Size = System::Drawing::Size(377, 13);
			this->timeStampLabel->TabIndex = 64;
			this->timeStampLabel->Text = L"This will enable time stamping of each line output in the RCON Output Window";
			// 
			// timeStamp
			// 
			this->timeStamp->AutoSize = true;
			this->timeStamp->Location = System::Drawing::Point(272, 219);
			this->timeStamp->Name = L"timeStamp";
			this->timeStamp->Size = System::Drawing::Size(195, 17);
			this->timeStamp->TabIndex = 65;
			this->timeStamp->Text = L"Enable Output Window Time Stamp";
			this->timeStamp->UseVisualStyleBackColor = true;
			// 
			// timeStampSelectionLabel
			// 
			this->timeStampSelectionLabel->AutoSize = true;
			this->timeStampSelectionLabel->Location = System::Drawing::Point(292, 238);
			this->timeStampSelectionLabel->Name = L"timeStampSelectionLabel";
			this->timeStampSelectionLabel->Size = System::Drawing::Size(146, 13);
			this->timeStampSelectionLabel->TabIndex = 66;
			this->timeStampSelectionLabel->Text = L"Select the Time Stamp format";
			// 
			// timeStampFormat
			// 
			this->timeStampFormat->FormattingEnabled = true;
			this->timeStampFormat->Location = System::Drawing::Point(272, 253);
			this->timeStampFormat->Name = L"timeStampFormat";
			this->timeStampFormat->Size = System::Drawing::Size(212, 21);
			this->timeStampFormat->TabIndex = 67;
			this->timeStampFormat->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Settings::timeStampFormat_KeyPress);
			// 
			// teamColorLabel
			// 
			this->teamColorLabel->AutoSize = true;
			this->teamColorLabel->Location = System::Drawing::Point(391, 270);
			this->teamColorLabel->Name = L"teamColorLabel";
			this->teamColorLabel->Size = System::Drawing::Size(107, 13);
			this->teamColorLabel->TabIndex = 95;
			this->teamColorLabel->Text = L"Team Message Color";
			// 
			// chatColorLabel
			// 
			this->chatColorLabel->AutoSize = true;
			this->chatColorLabel->Location = System::Drawing::Point(219, 270);
			this->chatColorLabel->Name = L"chatColorLabel";
			this->chatColorLabel->Size = System::Drawing::Size(102, 13);
			this->chatColorLabel->TabIndex = 92;
			this->chatColorLabel->Text = L"Chat Message Color";
			// 
			// chatMessageColor
			// 
			this->chatMessageColor->Location = System::Drawing::Point(327, 270);
			this->chatMessageColor->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 8, 0, 0, 0 });
			this->chatMessageColor->Name = L"chatMessageColor";
			this->chatMessageColor->Size = System::Drawing::Size(30, 20);
			this->chatMessageColor->TabIndex = 96;
			// 
			// teamMessageColor
			// 
			this->teamMessageColor->Location = System::Drawing::Point(503, 270);
			this->teamMessageColor->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 8, 0, 0, 0 });
			this->teamMessageColor->Name = L"teamMessageColor";
			this->teamMessageColor->Size = System::Drawing::Size(30, 20);
			this->teamMessageColor->TabIndex = 97;
			// 
			// messageColorLabel
			// 
			this->messageColorLabel->AutoSize = true;
			this->messageColorLabel->Location = System::Drawing::Point(204, 253);
			this->messageColorLabel->Name = L"messageColorLabel";
			this->messageColorLabel->Size = System::Drawing::Size(355, 13);
			this->messageColorLabel->TabIndex = 98;
			this->messageColorLabel->Text = L"(Pick a Quake Live color number from 0 to 8 for Chat and Team Mesages)";
			// 
			// Settings
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DarkGray;
			this->ClientSize = System::Drawing::Size(687, 330);
			this->Controls->Add(this->menuSelection);
			this->Controls->Add(this->reset);
			this->Controls->Add(this->cancel);
			this->Controls->Add(this->save);
			this->Controls->Add(this->versionLabel);
			this->Controls->Add(this->website);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Settings";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Quake Live RCON Settings";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->maxLines))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->linesRemove))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->deleteDays))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chatMessageColor))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->teamMessageColor))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void save_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void cancel_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void reset_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void website_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e);
		private: System::Void menuSelection_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		private: System::Void color0Button_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void color1Button_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void color2Button_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void color3Button_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void color4Button_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void color5Button_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void color6Button_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void color7Button_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void color8Button_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void timeStampFormat_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		private: System::Void logFiles_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void deleteNow_Click(System::Object^  sender, System::EventArgs^  e);
		
		private: void loadMenuSelection();
		private: void loadWindowInfo();
		private: void clearWindow();
		private: void showSettingsControls(int index);
		private: void fillTimeStampFormatCombobox();
};
}
