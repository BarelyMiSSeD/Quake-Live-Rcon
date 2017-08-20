/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.4 on 8/18/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#include "Settings.h"

QuakeLiveRcon::Settings::Settings(const char *file, String^ version) {
	InitializeComponent();
	//
	//TODO: Add the constructor code here
	//

	this->ini = gcnew IniEditor(file);
	this->website->Text = WEBSITE_URL;
	this->versionLabel->Text += version;
	this->loadMenuSelection();
	this->loadWindowInfo();
}

QuakeLiveRcon::Settings::~Settings() {
	if (components)	{
		delete components;
	}
}

System::Void QuakeLiveRcon::Settings::menuSelection_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	this->showSettingsControls(this->menuSelection->SelectedIndex);
}

System::Void QuakeLiveRcon::Settings::color0Button_Click(System::Object^  sender, System::EventArgs^  e) {
	ColorDialog^ colors = gcnew ColorDialog;
	//Allow selecting a custom color
	colors->AllowFullOpen = true;
	//Allow the user to get help
	colors->ShowHelp = true;
	//Sets the initial color select to the current setting
	colors->Color = ColorTranslator::FromHtml(color0Box->Text);

	if (colors->ShowDialog() == ::System::Windows::Forms::DialogResult::OK) {
		color0Box->ForeColor = colors->Color;
		color0Box->Text = "#" + colors->Color.R.ToString("X2") + colors->Color.G.ToString("X2") + colors->Color.B.ToString("X2");
	}
	delete colors;
}

System::Void QuakeLiveRcon::Settings::color1Button_Click(System::Object^  sender, System::EventArgs^  e) {
	ColorDialog^ colors = gcnew ColorDialog;
	//Allow selecting a custom color
	colors->AllowFullOpen = true;
	//Allow the user to get help
	colors->ShowHelp = true;
	//Sets the initial color select to the current setting
	colors->Color = ColorTranslator::FromHtml(color0Box->Text);

	if (colors->ShowDialog() == ::System::Windows::Forms::DialogResult::OK) {
		color1Box->ForeColor = colors->Color;
		color1Box->Text = "#" + colors->Color.R.ToString("X2") + colors->Color.G.ToString("X2") + colors->Color.B.ToString("X2");
	}
	delete colors;
}

System::Void QuakeLiveRcon::Settings::color2Button_Click(System::Object^  sender, System::EventArgs^  e) {
	ColorDialog^ colors = gcnew ColorDialog;
	//Allow selecting a custom color
	colors->AllowFullOpen = true;
	//Allow the user to get help
	colors->ShowHelp = true;
	//Sets the initial color select to the current setting
	colors->Color = ColorTranslator::FromHtml(color0Box->Text);

	if (colors->ShowDialog() == ::System::Windows::Forms::DialogResult::OK) {
		color2Box->ForeColor = colors->Color;
		color2Box->Text = "#" + colors->Color.R.ToString("X2") + colors->Color.G.ToString("X2") + colors->Color.B.ToString("X2");
	}
	delete colors;
}

System::Void QuakeLiveRcon::Settings::color3Button_Click(System::Object^  sender, System::EventArgs^  e) {
	ColorDialog^ colors = gcnew ColorDialog;
	//Allow selecting a custom color
	colors->AllowFullOpen = true;
	//Allow the user to get help
	colors->ShowHelp = true;
	//Sets the initial color select to the current setting
	colors->Color = ColorTranslator::FromHtml(color0Box->Text);

	if (colors->ShowDialog() == ::System::Windows::Forms::DialogResult::OK) {
		color3Box->ForeColor = colors->Color;
		color3Box->Text = "#" + colors->Color.R.ToString("X2") + colors->Color.G.ToString("X2") + colors->Color.B.ToString("X2");
	}
	delete colors;
}

System::Void QuakeLiveRcon::Settings::color4Button_Click(System::Object^  sender, System::EventArgs^  e) {
	ColorDialog^ colors = gcnew ColorDialog;
	//Allow selecting a custom color
	colors->AllowFullOpen = true;
	//Allow the user to get help
	colors->ShowHelp = true;
	//Sets the initial color select to the current setting
	colors->Color = ColorTranslator::FromHtml(color0Box->Text);

	if (colors->ShowDialog() == ::System::Windows::Forms::DialogResult::OK) {
		color4Box->ForeColor = colors->Color;
		color4Box->Text = "#" + colors->Color.R.ToString("X2") + colors->Color.G.ToString("X2") + colors->Color.B.ToString("X2");
	}
	delete colors;
}

System::Void QuakeLiveRcon::Settings::color5Button_Click(System::Object^  sender, System::EventArgs^  e) {
	ColorDialog^ colors = gcnew ColorDialog;
	//Allow selecting a custom color
	colors->AllowFullOpen = true;
	//Allow the user to get help
	colors->ShowHelp = true;
	//Sets the initial color select to the current setting
	colors->Color = ColorTranslator::FromHtml(color0Box->Text);

	if (colors->ShowDialog() == ::System::Windows::Forms::DialogResult::OK) {
		color5Box->ForeColor = colors->Color;
		color5Box->Text = "#" + colors->Color.R.ToString("X2") + colors->Color.G.ToString("X2") + colors->Color.B.ToString("X2");
	}
	delete colors;
}

System::Void QuakeLiveRcon::Settings::color6Button_Click(System::Object^  sender, System::EventArgs^  e) {
	ColorDialog^ colors = gcnew ColorDialog;
	//Allow selecting a custom color
	colors->AllowFullOpen = true;
	//Allow the user to get help
	colors->ShowHelp = true;
	//Sets the initial color select to the current setting
	colors->Color = ColorTranslator::FromHtml(color0Box->Text);

	if (colors->ShowDialog() == ::System::Windows::Forms::DialogResult::OK) {
		color6Box->ForeColor = colors->Color;
		color6Box->Text = "#" + colors->Color.R.ToString("X2") + colors->Color.G.ToString("X2") + colors->Color.B.ToString("X2");
	}
	delete colors;
}

System::Void QuakeLiveRcon::Settings::color7Button_Click(System::Object^  sender, System::EventArgs^  e) {
	ColorDialog^ colors = gcnew ColorDialog;
	//Allow selecting a custom color
	colors->AllowFullOpen = true;
	//Allow the user to get help
	colors->ShowHelp = true;
	//Sets the initial color select to the current setting
	colors->Color = ColorTranslator::FromHtml(color0Box->Text);

	if (colors->ShowDialog() == ::System::Windows::Forms::DialogResult::OK) {
		color7Box->ForeColor = colors->Color;
		color7Box->Text = "#" + colors->Color.R.ToString("X2") + colors->Color.G.ToString("X2") + colors->Color.B.ToString("X2");
	}
	delete colors;
}

System::Void QuakeLiveRcon::Settings::color8Button_Click(System::Object^  sender, System::EventArgs^  e) {
	ColorDialog^ colors = gcnew ColorDialog;
	//Allow selecting a custom color
	colors->AllowFullOpen = true;
	//Allow the user to get help
	colors->ShowHelp = true;
	//Sets the initial color select to the current setting
	colors->Color = ColorTranslator::FromHtml(color0Box->Text);

	if (colors->ShowDialog() == ::System::Windows::Forms::DialogResult::OK) {
		color8Box->ForeColor = colors->Color;
		color8Box->Text = "#" + colors->Color.R.ToString("X2") + colors->Color.G.ToString("X2") + colors->Color.B.ToString("X2");
	}
	delete colors;
}

System::Void QuakeLiveRcon::Settings::timeStampFormat_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	e->Handled = true;
}

void QuakeLiveRcon::Settings::loadWindowInfo() {
	//get the status command on connect status
	this->statusCommand->Checked = this->ini->isTrue("main", "sendStatus");
	//get the command 1 enable status
	this->enableCommand1->Checked = this->ini->isTrue("main", "command1:enabled");
	//get the command 1 button label
	this->cmd1BtnLabel->Text = this->ini->getValue("main", "command1:label");
	//get the command 1 button command
	this->cmd1BtnCmd->Text = this->ini->getValue("main", "command1:command");
	//get the command 2 enable status
	this->enableCommand2->Checked = this->ini->isTrue("main", "command2:enabled");
	//get the command 2 button label	  
	this->cmd2BtnLabel->Text = this->ini->getValue("main", "command2:label");
	//get the command 2 button command	  
	this->cmd2BtnCmd->Text = this->ini->getValue("main", "command2:command");
	//get the command 3 enable status
	this->enableCommand3->Checked = this->ini->isTrue("main", "command3:enabled");
	//get the command 3 button label	  
	this->cmd3BtnLabel->Text = this->ini->getValue("main", "command3:label");
	//get the command 3 button command	  
	this->cmd3BtnCmd->Text = this->ini->getValue("main", "command3:command");
	//get the command 4 enable status
	this->enableCommand4->Checked = this->ini->isTrue("main", "command4:enabled");
	//get the command 4 button label	  
	this->cmd4BtnLabel->Text = this->ini->getValue("main", "command4:label");
	//get the command 4 button command	  
	this->cmd4BtnCmd->Text = this->ini->getValue("main", "command4:command");
	//get the command 5 enable status
	this->enableCommand5->Checked = this->ini->isTrue("main", "command5:enabled");
	//get the command 5 button label	  
	this->cmd5BtnLabel->Text = this->ini->getValue("main", "command5:label");
	//get the command 5 button command	  
	this->cmd5BtnCmd->Text = this->ini->getValue("main", "command5:command");
	//get the command 6 enable status
	this->enableCommand6->Checked = this->ini->isTrue("main", "command6:enabled");
	//get the command 6 button label	  
	this->cmd6BtnLabel->Text = this->ini->getValue("main", "command6:label");
	//get the command 6 button command	  
	this->cmd6BtnCmd->Text = this->ini->getValue("main", "command6:command");
	//get the connect to game server button enable status
	this->enableConnectToGame->Checked = this->ini->isTrue("main", "connectToGame:enabled");
	//get the strip colors for log file enable status
	this->stripColors->Checked = this->ini->isTrue("main", "stripLogColors:enabled");
	//get the scoll lines disable status
	this->disableScroll->Checked = this->ini->isTrue("main", "scroll:disabled");
	//get the scoll lines disable status
	this->enableLogging->Checked = this->ini->getBoolean("main", "logging:enabled", true);
	//get the keep alive status
	this->keepAlive->Checked = this->ini->getBoolean("main", "keepAlive", true);
	//get the gameEvents:enabled field
	this->gameEvents->Checked = this->ini->getBoolean("main", "gameEvents:enabled", true);
	//get the killMessages:enabled field
	this->killMessages->Checked = this->ini->getBoolean("main", "killMessages:enabled", true);
	//get the teamSwitch:enabled field
	this->teamSwitch->Checked = this->ini->getBoolean("main", "teamSwitch:enabled", true);
	//get the warmUp:enabled field
	this->warmUp->Checked = this->ini->getBoolean("main", "warmUp:enabled", true);
	//get the playerMedals:enabled field
	this->playerMedals->Checked = this->ini->getBoolean("main", "playerMedals:enabled", true);
	//get the timeStamp:enabled field
	this->timeStamp->Checked = this->ini->getBoolean("main", "timeStamp:enabled", false);
	//get the timeStampFormat
	this->timeStampFormat->SelectedIndex = this->timeStampFormat->FindStringExact(this->ini->getValue("main", "timeStampFormat", "11:45:30 AM"));

	//get the max lines displayed
	String^ value = this->ini->getValue("main", "maxLines");
	if (String::Compare(value, ""))
		this->maxLines->Text = value;
	else
		this->maxLines->Text = System::Convert::ToString(MAX_TEXTBOX_LINES);

	//get the lines to remove
	value = this->ini->getValue("main", "removeLines");
	if (String::Compare(value, ""))
		this->linesRemove->Text = value;
	else
		this->linesRemove->Text = System::Convert::ToString(LINES_TO_DELETE);

	//get color 0 (Black)
	this->color0Box->Text = this->ini->getValue("main", "color0", "#73879B");
	this->color0Box->ForeColor = ColorTranslator::FromHtml(this->color0Box->Text);
	//get color 1 (Red)	
	this->color1Box->Text = this->ini->getValue("main", "color1", "#FF0000");
	this->color1Box->ForeColor = ColorTranslator::FromHtml(this->color1Box->Text);
	//get color 2 (Green)	
	this->color2Box->Text = this->ini->getValue("main", "color2", "#00FF00");
	this->color2Box->ForeColor = ColorTranslator::FromHtml(this->color2Box->Text);
	//get color 3 (Yellow)	
	this->color3Box->Text = this->ini->getValue("main", "color3", "#FFFF00");
	this->color3Box->ForeColor = ColorTranslator::FromHtml(this->color3Box->Text);
	//get color 4 (Blue)	
	this->color4Box->Text = this->ini->getValue("main", "color4", "#306EFF");
	this->color4Box->ForeColor = ColorTranslator::FromHtml(this->color4Box->Text);
	//get color 5 (Cyan)	
	this->color5Box->Text = this->ini->getValue("main", "color5", "#53DCCD");
	this->color5Box->ForeColor = ColorTranslator::FromHtml(this->color5Box->Text);
	//get color 6 (Purple)	
	this->color6Box->Text = this->ini->getValue("main", "color6", "#B041FF");
	this->color6Box->ForeColor = ColorTranslator::FromHtml(this->color6Box->Text);
	//get color 7 (White)	
	this->color7Box->Text = this->ini->getValue("main", "color7", "#FFFFFF");
	this->color7Box->ForeColor = ColorTranslator::FromHtml(this->color7Box->Text);
	//get color 8 (Black)	
	this->color8Box->Text = this->ini->getValue("main", "color8", "#73879B");
	this->color8Box->ForeColor = ColorTranslator::FromHtml(this->color8Box->Text);
	//get chatColorBox (Green)
	this->chatMessageColor->Text = this->ini->getValue("main", "chatColor", "2");
	//get teamColorBox (Cyan)
	this->teamMessageColor->Text = this->ini->getValue("main", "teamColor", "5");

	//get the deleteDays field
	this->deleteDays->Text = this->ini->getValue("main", "deleteDays", "30");
	//get the automaticFileDelete:enabled field
	this->automaticFileDelete->Checked = this->ini->getBoolean("main", "automaticFileDelete:enabled", false);
}

System::Void QuakeLiveRcon::Settings::save_Click(System::Object^  sender, System::EventArgs^  e) {
	//save the status command on connect status
	this->ini->writeValue("main", "sendStatus", this->statusCommand->Checked);
	//save the command 1 enable status
	this->ini->writeValue("main", "command1:enabled", this->enableCommand1->Checked);
	//save the command 1 button label
	this->ini->writeValue("main", "command1:label", this->cmd1BtnLabel->Text);
	//save the command 1 button command
	this->ini->writeValue("main", "command1:command", this->cmd1BtnCmd->Text);
	//save the command 2 enable status
	this->ini->writeValue("main", "command2:enabled", this->enableCommand2->Checked);
	//save the command 2 button label	  
	this->ini->writeValue("main", "command2:label", this->cmd2BtnLabel->Text);
	//save the command 2 button command	  
	this->ini->writeValue("main", "command2:command", this->cmd2BtnCmd->Text);
	//save the command 3 enable status
	this->ini->writeValue("main", "command3:enabled", this->enableCommand3->Checked);
	//save the command 3 button label	  
	this->ini->writeValue("main", "command3:label", this->cmd3BtnLabel->Text);
	//save the command 3 button command	  
	this->ini->writeValue("main", "command3:command", this->cmd3BtnCmd->Text);
	//save the command 4 enable status
	this->ini->writeValue("main", "command4:enabled", this->enableCommand4->Checked);
	//save the command 4 button label
	this->ini->writeValue("main", "command4:label", this->cmd4BtnLabel->Text);
	//save the command 4 button command
	this->ini->writeValue("main", "command4:command", this->cmd4BtnCmd->Text);
	//save the command 5 enable status
	this->ini->writeValue("main", "command5:enabled", this->enableCommand5->Checked);
	//save the command 5 button label
	this->ini->writeValue("main", "command5:label", this->cmd5BtnLabel->Text);
	//save the command 5 button command
	this->ini->writeValue("main", "command5:command", this->cmd5BtnCmd->Text);
	//save the command 6 enable status
	this->ini->writeValue("main", "command6:enabled", this->enableCommand6->Checked);
	//save the command 6 button label
	this->ini->writeValue("main", "command6:label", this->cmd6BtnLabel->Text);
	//save the command 6 button command
	this->ini->writeValue("main", "command6:command", this->cmd6BtnCmd->Text);
	//save the connect to game server button enable status
	this->ini->writeValue("main", "connectToGame:enabled", this->enableConnectToGame->Checked);
	//save the strip colors for log file enable status
	this->ini->writeValue("main", "stripLogColors:enabled", this->stripColors->Checked);
	//save the scoll lines disable status
	this->ini->writeValue("main", "scroll:disabled", this->disableScroll->Checked);
	//save the scoll lines disable status
	this->ini->writeValue("main", "logging:enabled", this->enableLogging->Checked);
	//save the keep alive status
	this->ini->writeValue("main", "keepAlive", this->keepAlive->Checked);
	//save the deleteDays field
	this->ini->writeValue("main", "deleteDays", this->deleteDays->Text);
	//save the automaticFileDelete:enabled field
	this->ini->writeValue("main", "automaticFileDelete:enabled", this->automaticFileDelete->Checked);
	//save the gameEvents:enabled field
	this->ini->writeValue("main", "gameEvents:enabled", this->gameEvents->Checked);
	//save the killMessages:enabled field
	this->ini->writeValue("main", "killMessages:enabled", this->killMessages->Checked);
	//save the teamSwitch:enabled field
	this->ini->writeValue("main", "teamSwitch:enabled", this->teamSwitch->Checked);
	//save the warmUp:enabled field
	this->ini->writeValue("main", "warmUp:enabled", this->warmUp->Checked);
	//save the playerMedals:enabled field
	this->ini->writeValue("main", "playerMedals:enabled", this->playerMedals->Checked);
	//save the timeStamp:enabled field
	this->ini->writeValue("main", "timeStamp:enabled", this->timeStamp->Checked);
	//save the timeStampFormat
	this->ini->writeValue("main", "timeStampFormat", this->timeStampFormat->Text);

	//save the selected setting index
	this->ini->writeValue("main", "settingIndex", System::Convert::ToInt32(this->menuSelection->SelectedIndex));

	//save color 0 (Black)
	this->ini->writeValue("main", "color0", this->color0Box->Text);
	//save color 1 (Red)
	this->ini->writeValue("main", "color1", this->color1Box->Text);
	//save color 2 (Green)
	this->ini->writeValue("main", "color2", this->color2Box->Text);
	//save color 3 (Yellow)
	this->ini->writeValue("main", "color3", this->color3Box->Text);
	//save color 4 (Blue)
	this->ini->writeValue("main", "color4", this->color4Box->Text);
	//save color 5 (Cyan)
	this->ini->writeValue("main", "color5", this->color5Box->Text);
	//save color 6 (Purple)
	this->ini->writeValue("main", "color6", this->color6Box->Text);
	//save color 7 (White)
	this->ini->writeValue("main", "color7", this->color7Box->Text);
	//save color 8 (Black)
	this->ini->writeValue("main", "color8", this->color8Box->Text);
	//save chatColorBox color
	this->ini->writeValue("main", "chatColor", this->chatMessageColor->Text);
	//save teamColorBox color
	this->ini->writeValue("main", "teamColor", this->teamMessageColor->Text);

	int max = System::Convert::ToInt32(this->maxLines->Value);
	int remove = System::Convert::ToInt32(this->linesRemove->Value);
	//MessageBox::Show("Max: " + max + ":" + INT_MAX + " Remove: " + remove + ":" + INT_MIN, "Values not Allowed",
	//MessageBoxButtons::OK, MessageBoxIcon::Exclamation);

	if (max >= remove) {
		if (max != MAX_TEXTBOX_LINES || String::Compare(this->ini->getValue("main", "maxLines"), ""))
			//save the max lines displayed
			this->ini->writeValue("main", "maxLines", this->maxLines->Text);
		if (remove != LINES_TO_DELETE || String::Compare(this->ini->getValue("main", "removeLines"), ""))
			//save the lines to remove
			this->ini->writeValue("main", "removeLines", this->linesRemove->Text);

		//close the settings form
		this->Close();
	}
	else {
		MessageBox::Show("The lines to remove can't be greater than the max lines displayed.", "Values not Allowed", 
			MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
}

System::Void QuakeLiveRcon::Settings::cancel_Click(System::Object^  sender, System::EventArgs^  e) {
	//close the settings form
	this->Close();
}

System::Void QuakeLiveRcon::Settings::reset_Click(System::Object^  sender, System::EventArgs^  e) {
	if (MessageBox::Show("Are you sure that you would like to reset all values to default? This will not change your custom buttons.",
		"Reset to Default?", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == ::System::Windows::Forms::DialogResult::Yes) {

		//save the status command on connect status
		this->ini->writeValue("main", "sendStatus", false);
		this->statusCommand->Checked = false;
		//save the connect to game server button enable status
		this->ini->writeValue("main", "connectToGame:enabled", false);
		this->enableConnectToGame->Checked = false;
		//save the strip colors for log file enable status
		this->ini->writeValue("main", "stripLogColors:enabled", false);
		this->stripColors->Checked = false;
		//save the scoll lines disable status
		this->ini->writeValue("main", "scroll:disabled", false);
		this->disableScroll->Checked = false;
		//remove the max lines displayed field
		this->ini->deleteKey("main", "maxLines");
		this->maxLines->Text = System::Convert::ToString(MAX_TEXTBOX_LINES);
		//remove the lines to remove field
		this->ini->deleteKey("main", "removeLines");
		this->linesRemove->Text = System::Convert::ToString(LINES_TO_DELETE);
		//remove the logging:enabled field
		this->ini->deleteKey("main", "logging:enabled");
		this->enableLogging->Checked = true;
		//save the keep alive status
		this->ini->writeValue("main", "keepAlive", true);
		//remove the deleteDays field
		this->ini->deleteKey("main", "deleteDays");
		this->deleteDays->Text = "30";
		//remove the automaticFileDelete:enabled field
		this->ini->deleteKey("main", "automaticFileDelete:enabled");
		this->automaticFileDelete->Checked = false;
		//remove the gameEvents:enabled field
		this->ini->deleteKey("main", "gameEvents:enabled");
		this->gameEvents->Checked = true;
		//remove the killMessages:enabled field
		this->ini->deleteKey("main", "killMessages:enabled");
		this->killMessages->Checked = true;
		//remove the teamSwitch:enabled field
		this->ini->deleteKey("main", "teamSwitch:enabled");
		this->teamSwitch->Checked = true;
		//remove the warmUp:enabled field
		this->ini->deleteKey("main", "warmUp:enabled");
		this->warmUp->Checked = true;
		//remove the playerMedals:enabled field
		this->ini->deleteKey("main", "playerMedals:enabled");
		this->playerMedals->Checked = true;
		//remove the timeStamp:enabled field
		this->ini->deleteKey("main", "timeStamp:enabled");
		this->timeStamp->Checked = false;
		//remove the timeStampFormat
		this->ini->deleteKey("main", "timeStampFormat");
		this->timeStampFormat->SelectedIndex = this->timeStampFormat->FindStringExact("11:45:30 AM");

		//save color 0 (Black)
		this->ini->writeValue("main", "color0", "#73879B");
		this->color0Box->Text = "#73879B";
		this->color0Box->ForeColor = ColorTranslator::FromHtml("#73879B");
		//save color 1 (Red)
		this->ini->writeValue("main", "color1", "#FF0000");
		this->color1Box->Text = "#FF0000";
		this->color1Box->ForeColor = ColorTranslator::FromHtml("#FF0000");
		//save color 2 (Green)
		this->ini->writeValue("main", "color2", "#00FF00");
		this->color2Box->Text = "#00FF00";
		this->color2Box->ForeColor = ColorTranslator::FromHtml("#00FF00");
		//save color 3 (Yellow)
		this->ini->writeValue("main", "color3", "#FFFF00");
		this->color3Box->Text = "#FFFF00";
		this->color3Box->ForeColor = ColorTranslator::FromHtml("#FFFF00");
		//save color 4 (Blue)
		this->ini->writeValue("main", "color4", "#306EFF");
		this->color4Box->Text = "#306EFF";
		this->color4Box->ForeColor = ColorTranslator::FromHtml("#306EFF");
		//save color 5 (Cyan)
		this->ini->writeValue("main", "color5", "#53DCCD");
		this->color5Box->Text = "#53DCCD";
		this->color5Box->ForeColor = ColorTranslator::FromHtml("#53DCCD");
		//save color 6 (Purple)
		this->ini->writeValue("main", "color6", "#B041FF");
		this->color6Box->Text = "#B041FF";
		this->color6Box->ForeColor = ColorTranslator::FromHtml("#B041FF");
		//save color 7 (White)
		this->ini->writeValue("main", "color7", "#FFFFFF");
		this->color7Box->Text = "#FFFFFF";
		this->color7Box->ForeColor = ColorTranslator::FromHtml("#FFFFFF");
		//save color 8 (Black)
		this->ini->writeValue("main", "color8", "#73879B");
		this->color8Box->Text = "#73879B";
		this->color8Box->ForeColor = ColorTranslator::FromHtml("#73879B");
		//save chatColor (Green)
		this->ini->writeValue("main", "chatColor", "2");
		this->chatMessageColor->Text = "5";
		//save teamColor (Cyan)
		this->ini->writeValue("main", "teamColor", "5");
		this->teamMessageColor->Text = "5";

	}
}

System::Void QuakeLiveRcon::Settings::website_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
	ShellExecuteW(NULL, L"open", WEBSITE_URL, NULL, NULL, SW_SHOWDEFAULT);
}

System::Void QuakeLiveRcon::Settings::logFiles_Click(System::Object^  sender, System::EventArgs^  e) {
	if (System::IO::Directory::Exists(LOG_FILE_LOCATION))
		System::Diagnostics::Process::Start(LOG_FILE_LOCATION);
	else
		MessageBox::Show("There is no directory for storing log files.", "No log file directory exists.", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
}

System::Void QuakeLiveRcon::Settings::deleteNow_Click(System::Object^  sender, System::EventArgs^  e) {
	List<String^>^ sections = gcnew List<String^>();
	List<String^>^ exclusions = gcnew List<String^>();

	this->ini->getSectionNames(sections);
	for each (String^ section in sections) {
		if (String::Compare(section, "main") && this->ini->isTrue(section, "log")) {
			array<String^>^ sectionArray = section->Split(':');
			exclusions->Add(sectionArray[0] + "_" + sectionArray[1] + "_log.txt");
			//MessageBox::Show(sectionArray[0] + "_" + sectionArray[1] + "_log.txt", "Exceptions", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		}
	}

	int days = this->ini->getInt("main", "deleteDays", 30);
	//MessageBox::Show("Date: " + DateTime::Now.AddDays(-(double)days), "Days old", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	LogFileWriter^ deleteFiles = gcnew LogFileWriter(LOG_FILE_LOCATION);
	MessageBox::Show("Old Log File deletion proecess completed. There were " + deleteFiles->deleteOldFiles(DateTime::Now.AddDays(-(double)days), exclusions) +
		" files deleted that were at least " + days + " days old.", "Log Files Deleted", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
}

void QuakeLiveRcon::Settings::loadMenuSelection() {
	this->menuSelection->BeginUpdate();

	this->menuSelection->Items->Add("General");
	this->menuSelection->Items->Add("Command Buttons");
	this->menuSelection->Items->Add("RCON Window");
	this->menuSelection->Items->Add("Quake Live Colors");
	this->menuSelection->Items->Add("Logging");
	this->menuSelection->Items->Add("Game Status Messages");

	this->menuSelection->EndUpdate();

	this->fillTimeStampFormatCombobox();

	String^ indexString = this->ini->getValue("main", "settingIndex");
	int index;
	if (String::Compare(indexString, "") && int::TryParse(indexString, index))
		this->menuSelection->SetSelected(index, true);
	else
		this->menuSelection->SetSelected(0, true);
}

void QuakeLiveRcon::Settings::showSettingsControls(int index) {
	this->clearWindow();

	switch (index) {
	case 0:
		this->Controls->Add(this->keepAliveNote);
		this->Controls->Add(this->keepAlive);
		this->Controls->Add(this->keepAliveLabel);
		this->Controls->Add(this->divider13);
		this->Controls->Add(this->statusCmdLabel);
		this->Controls->Add(this->statusCommand);
		this->Controls->Add(this->divider0);
		this->Controls->Add(this->connectGameButtonLabel1);
		this->Controls->Add(this->enableConnectToGame);
		this->Controls->Add(this->connectGameButtonLabel2);
		break;
	case 1:
		this->Controls->Add(this->divider1);
		this->Controls->Add(this->enableCommand1);
		this->Controls->Add(this->cmd1BtnCmdLbl);
		this->Controls->Add(this->cmd1BtnCmd);
		this->Controls->Add(this->cmd1BtnLblLabel);
		this->Controls->Add(this->cmd1BtnLabel);
		this->Controls->Add(this->divider2);
		this->Controls->Add(this->enableCommand2);
		this->Controls->Add(this->cmd2BtnCmdLbl);
		this->Controls->Add(this->cmd2BtnCmd);
		this->Controls->Add(this->cmd2BtnLblLabel);
		this->Controls->Add(this->cmd2BtnLabel);
		this->Controls->Add(this->divider3);
		this->Controls->Add(this->enableCommand3);
		this->Controls->Add(this->cmd3BtnCmdLbl);
		this->Controls->Add(this->cmd3BtnCmd);
		this->Controls->Add(this->cmd3BtnLblLabel);
		this->Controls->Add(this->cmd3BtnLabel);
		this->Controls->Add(this->divider4);
		this->Controls->Add(this->enableCommand4);
		this->Controls->Add(this->cmd4BtnCmdLbl);
		this->Controls->Add(this->cmd4BtnCmd);
		this->Controls->Add(this->cmd4BtnLblLabel);
		this->Controls->Add(this->cmd4BtnLabel);
		this->Controls->Add(this->divider5);
		this->Controls->Add(this->enableCommand5);
		this->Controls->Add(this->cmd5BtnCmdLbl);
		this->Controls->Add(this->cmd5BtnCmd);
		this->Controls->Add(this->cmd5BtnLblLabel);
		this->Controls->Add(this->cmd5BtnLabel);
		this->Controls->Add(this->divider6);
		this->Controls->Add(this->enableCommand6);
		this->Controls->Add(this->cmd6BtnCmdLbl);
		this->Controls->Add(this->cmd6BtnCmd);
		this->Controls->Add(this->cmd6BtnLblLabel);
		this->Controls->Add(this->cmd6BtnLabel);
		this->Controls->Add(this->divider7);
		this->Controls->Add(this->divider8);
		this->Controls->Add(this->verticalDivider);
		break;
	case 2:
		this->Controls->Add(this->autoScrollNoteLabel);
		this->Controls->Add(this->linesRecommendLabel);
		this->Controls->Add(this->divider11);
		this->Controls->Add(this->linesRemove);
		this->Controls->Add(this->linesRemoveLabel);
		this->Controls->Add(this->maxLines);
		this->Controls->Add(this->maxLinesLabel);
		this->Controls->Add(this->divider10);
		this->Controls->Add(this->disableScroll);
		this->Controls->Add(this->autoScrollLabel);
		this->Controls->Add(this->timeStampFormat);
		this->Controls->Add(this->timeStampSelectionLabel);
		this->Controls->Add(this->timeStamp);
		this->Controls->Add(this->timeStampLabel);
		break;
	case 3:
		this->Controls->Add(this->colorNote);
		this->Controls->Add(this->colorLabel);
		this->Controls->Add(this->color6Button);
		this->Controls->Add(this->color6Box);
		this->Controls->Add(this->color6Label);
		this->Controls->Add(this->color7Button);
		this->Controls->Add(this->color7Box);
		this->Controls->Add(this->color7Label);
		this->Controls->Add(this->color5Button);
		this->Controls->Add(this->color5Box);
		this->Controls->Add(this->color5Label);
		this->Controls->Add(this->color4Button);
		this->Controls->Add(this->color4Box);
		this->Controls->Add(this->color4Label);
		this->Controls->Add(this->color3Button);
		this->Controls->Add(this->color3Box);
		this->Controls->Add(this->color3Label);
		this->Controls->Add(this->color8Button);
		this->Controls->Add(this->color8Box);
		this->Controls->Add(this->color8Label);
		this->Controls->Add(this->color2Button);
		this->Controls->Add(this->color2Box);
		this->Controls->Add(this->color2Label);
		this->Controls->Add(this->color1Button);
		this->Controls->Add(this->color1Box);
		this->Controls->Add(this->color1Label);
		this->Controls->Add(this->color0Button);
		this->Controls->Add(this->color0Box);
		this->Controls->Add(this->color0Label);
		this->Controls->Add(this->teamColorLabel);
		this->Controls->Add(this->chatColorLabel);
		this->Controls->Add(this->messageColorLabel);
		this->Controls->Add(this->teamMessageColor);
		this->Controls->Add(this->chatMessageColor);
		break;
	case 4:
		this->Controls->Add(this->divider14);
		this->Controls->Add(this->deleteNow);
		this->Controls->Add(this->trailingDeleteDaysLabel);
		this->Controls->Add(this->leadingDeleteDaysLabel);
		this->Controls->Add(this->deleteDays);
		this->Controls->Add(this->automaticFileDelete);
		this->Controls->Add(this->deleteOldLabel);
		this->Controls->Add(this->logFiles);
		this->Controls->Add(this->enableLogging);
		this->Controls->Add(this->enableLoggingLabel1);
		this->Controls->Add(this->enableLoggingLabel2);
		this->Controls->Add(this->divider9);
		this->Controls->Add(this->stripColorsLabel);
		this->Controls->Add(this->stripColors);
		break;
	case 5:
		this->Controls->Add(this->gameEvents);
		this->Controls->Add(this->gameEventsLabel);
		this->Controls->Add(this->divider15);
		this->Controls->Add(this->teamSwitch);
		this->Controls->Add(this->killMessages);
		this->Controls->Add(this->warmUp);
		this->Controls->Add(this->playerMedals);
	}

}

void QuakeLiveRcon::Settings::fillTimeStampFormatCombobox() {
	this->timeStampFormat->Items->Add("Friday, August 4, 2017 11:45 AM"); //"f"
	this->timeStampFormat->Items->Add("Friday, August 4, 2017 11:45:30 AM"); //"F"
	this->timeStampFormat->Items->Add("8/4/2017 11:45 AM"); //"g"
	this->timeStampFormat->Items->Add("8/4/2017 11:45:30 AM"); //"G"
	this->timeStampFormat->Items->Add("11:45 AM"); //"t"
	this->timeStampFormat->Items->Add("11:45:30 AM"); //"T"
	//this->timeStampFormat->Items->Add("");
}

void QuakeLiveRcon::Settings::clearWindow() {
	this->Controls->Remove(this->keepAliveNote);
	this->Controls->Remove(this->keepAlive);
	this->Controls->Remove(this->keepAliveLabel);
	this->Controls->Remove(this->divider13);
	this->Controls->Remove(this->linesRecommendLabel);
	this->Controls->Remove(this->divider10);
	this->Controls->Remove(this->linesRemove);
	this->Controls->Remove(this->linesRemoveLabel);
	this->Controls->Remove(this->maxLines);
	this->Controls->Remove(this->maxLinesLabel);
	this->Controls->Remove(this->divider11);
	this->Controls->Remove(this->disableScroll);
	this->Controls->Remove(this->autoScrollLabel);
	this->Controls->Remove(this->divider0);
	this->Controls->Remove(this->stripColors);
	this->Controls->Remove(this->stripColorsLabel);
	this->Controls->Remove(this->divider9);
	this->Controls->Remove(this->enableConnectToGame);
	this->Controls->Remove(this->connectGameButtonLabel1);
	this->Controls->Remove(this->connectGameButtonLabel2);
	this->Controls->Remove(this->divider8);
	this->Controls->Remove(this->divider7);
	this->Controls->Remove(this->verticalDivider);
	this->Controls->Remove(this->divider4);
	this->Controls->Remove(this->enableCommand4);
	this->Controls->Remove(this->cmd4BtnCmdLbl);
	this->Controls->Remove(this->cmd4BtnCmd);
	this->Controls->Remove(this->cmd4BtnLblLabel);
	this->Controls->Remove(this->cmd4BtnLabel);
	this->Controls->Remove(this->divider5);
	this->Controls->Remove(this->enableCommand5);
	this->Controls->Remove(this->cmd5BtnCmdLbl);
	this->Controls->Remove(this->cmd5BtnCmd);
	this->Controls->Remove(this->cmd5BtnLblLabel);
	this->Controls->Remove(this->cmd5BtnLabel);
	this->Controls->Remove(this->divider6);
	this->Controls->Remove(this->enableCommand6);
	this->Controls->Remove(this->cmd6BtnCmdLbl);
	this->Controls->Remove(this->cmd6BtnCmd);
	this->Controls->Remove(this->cmd6BtnLblLabel);
	this->Controls->Remove(this->cmd6BtnLabel);
	this->Controls->Remove(this->statusCommand);
	this->Controls->Remove(this->divider1);
	this->Controls->Remove(this->enableCommand1);
	this->Controls->Remove(this->cmd1BtnCmdLbl);
	this->Controls->Remove(this->cmd1BtnCmd);
	this->Controls->Remove(this->cmd1BtnLblLabel);
	this->Controls->Remove(this->cmd1BtnLabel);
	this->Controls->Remove(this->divider2);
	this->Controls->Remove(this->enableCommand2);
	this->Controls->Remove(this->cmd2BtnCmdLbl);
	this->Controls->Remove(this->cmd2BtnCmd);
	this->Controls->Remove(this->cmd2BtnLblLabel);
	this->Controls->Remove(this->cmd2BtnLabel);
	this->Controls->Remove(this->divider3);
	this->Controls->Remove(this->enableCommand3);
	this->Controls->Remove(this->cmd3BtnCmdLbl);
	this->Controls->Remove(this->cmd3BtnCmd);
	this->Controls->Remove(this->cmd3BtnLblLabel);
	this->Controls->Remove(this->cmd3BtnLabel);
	this->Controls->Remove(this->enableLogging);
	this->Controls->Remove(this->enableLoggingLabel1);
	this->Controls->Remove(this->enableLoggingLabel2);
	this->Controls->Remove(this->statusCmdLabel);
	this->Controls->Remove(this->autoScrollNoteLabel);
	this->Controls->Remove(this->color6Button);
	this->Controls->Remove(this->color6Box);
	this->Controls->Remove(this->color6Label);
	this->Controls->Remove(this->color7Button);
	this->Controls->Remove(this->color7Box);
	this->Controls->Remove(this->color7Label);
	this->Controls->Remove(this->color5Button);
	this->Controls->Remove(this->color5Box);
	this->Controls->Remove(this->color5Label);
	this->Controls->Remove(this->color4Button);
	this->Controls->Remove(this->color4Box);
	this->Controls->Remove(this->color4Label);
	this->Controls->Remove(this->color3Button);
	this->Controls->Remove(this->color3Box);
	this->Controls->Remove(this->color3Label);
	this->Controls->Remove(this->color8Button);
	this->Controls->Remove(this->color8Box);
	this->Controls->Remove(this->color8Label);
	this->Controls->Remove(this->color2Button);
	this->Controls->Remove(this->color2Box);
	this->Controls->Remove(this->color2Label);
	this->Controls->Remove(this->color1Button);
	this->Controls->Remove(this->color1Box);
	this->Controls->Remove(this->color1Label);
	this->Controls->Remove(this->color0Button);
	this->Controls->Remove(this->color0Box);
	this->Controls->Remove(this->color0Label);
	this->Controls->Remove(this->colorLabel);
	this->Controls->Remove(this->colorNote);
	this->Controls->Remove(this->logFiles);
	this->Controls->Remove(this->divider14);
	this->Controls->Remove(this->deleteNow);
	this->Controls->Remove(this->trailingDeleteDaysLabel);
	this->Controls->Remove(this->leadingDeleteDaysLabel);
	this->Controls->Remove(this->deleteDays);
	this->Controls->Remove(this->automaticFileDelete);
	this->Controls->Remove(this->deleteOldLabel);
	this->Controls->Remove(this->gameEvents);
	this->Controls->Remove(this->gameEventsLabel);
	this->Controls->Remove(this->divider15);
	this->Controls->Remove(this->teamSwitch);
	this->Controls->Remove(this->killMessages);
	this->Controls->Remove(this->warmUp);
	this->Controls->Remove(this->playerMedals);
	this->Controls->Remove(this->timeStampFormat);
	this->Controls->Remove(this->timeStampSelectionLabel);
	this->Controls->Remove(this->timeStamp);
	this->Controls->Remove(this->timeStampLabel);
	this->Controls->Remove(this->messageColorLabel);
	this->Controls->Remove(this->teamMessageColor);
	this->Controls->Remove(this->chatMessageColor);
	this->Controls->Remove(this->teamColorLabel);
	this->Controls->Remove(this->chatColorLabel);
}
