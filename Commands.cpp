/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.5 on 8/20/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#include "Commands.h"

QuakeLiveRcon::Commands::Commands(const char *file, int tab) {
	InitializeComponent();
	
	this->ini = gcnew IniEditor(file);
	this->tab = tab;
}

QuakeLiveRcon::Commands::~Commands() {
	if (components)
	{
		delete components;
	}
}

System::Void QuakeLiveRcon::Commands::Window_Shown(System::Object^  sender, System::EventArgs^  e) {
	this->fillCommandBox();
}

System::Void QuakeLiveRcon::Commands::close_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Close();
}

System::Void QuakeLiveRcon::Commands::commandList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	this->selectedLine = this->commandList->SelectedIndex;
	this->commandText = this->commandList->Text;
}

System::Void QuakeLiveRcon::Commands::addCommand_Click(System::Object^  sender, System::EventArgs^  e) {
	this->lineNum = -1;
	this->entryLabel = gcnew String("Enter the command you wish to save");
	this->editText = gcnew String("");
	this->addNewCommand(this->commandEntry());
}

System::Void QuakeLiveRcon::Commands::editCommand_Click(System::Object^  sender, System::EventArgs^  e) {
	this->lineNum = this->selectedLine;
	this->entryLabel = gcnew String("Edit the stored command");
	this->editText = this->commandList->Text;
	this->editSelectedCommand(this->lineNum, this->commandEntry());
}

System::Void QuakeLiveRcon::Commands::deleteCommand_Click(System::Object^  sender, System::EventArgs^  e) {
	this->deleteSelectedCommand(this->selectedLine);
}

System::Void QuakeLiveRcon::Commands::sendCommand_Click(System::Object^  sender, System::EventArgs^  e) {
	if (System::String::Compare(this->commandText, "")) {
		QuakeLiveRcon::QLRcon::addToSendCommands(this->tab, this->commandText);
	}
	else {
		MessageBox::Show("There is no command entry text selected.", "No Command to Send", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
}

System::Void QuakeLiveRcon::Commands::moveUp_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->selectedLine > 0) {
		this->swapCommands(this->selectedLine, this->commandList->Items[this->selectedLine]->ToString(),
			(this->selectedLine - 1), this->commandList->Items[this->selectedLine - 1]->ToString());
		int tempLineNum = this->selectedLine;
		this->commandList->ClearSelected();
		this->fillCommandBox();
		this->commandList->SetSelected(tempLineNum - 1, true);
	}
}

System::Void QuakeLiveRcon::Commands::moveDown_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->selectedLine < this->commandList->Items->Count - 1) {
		this->swapCommands(this->selectedLine, this->commandList->Items[this->selectedLine]->ToString(),
			(this->selectedLine + 1), this->commandList->Items[this->selectedLine + 1]->ToString());
		int tempLineNum = this->selectedLine;
		this->commandList->ClearSelected();
		this->fillCommandBox();
		this->commandList->SetSelected(tempLineNum + 1, true);
	}
}

System::Void QuakeLiveRcon::Commands::addNewCommand(String^ command) {
	if (String::Compare(command, "")) {
		int cmdNumber = this->commandList->Items->Count;
		this->ini->writeValue("commands", System::Convert::ToString(cmdNumber), command);
		this->fillCommandBox();
		this->commandList->SetSelected(this->commandList->Items->Count - 1, true);
	}
}

System::Void QuakeLiveRcon::Commands::deleteSelectedCommand(int num) {
	if (this->selectedLine != -1) {
		int cmdCount = this->commandList->Items->Count;

		this->ini->deleteKey("commands", System::Convert::ToString(this->selectedLine));

		for (int i = this->selectedLine; i < cmdCount - 1; i++) {
			this->ini->writeValue("commands", System::Convert::ToString(i), this->ini->getValue("commands", System::Convert::ToString(i + 1)));
			this->ini->deleteKey("commands", System::Convert::ToString(i + 1));
		}
		this->fillCommandBox();
	}
}

System::Void QuakeLiveRcon::Commands::editSelectedCommand(int num, String^ command) {
	if (String::Compare(command, "")) {
		this->ini->writeValue("commands", System::Convert::ToString(num), command);
		this->fillCommandBox();
		this->commandList->SetSelected(this->lineNum, true);
	}
}

System::Void QuakeLiveRcon::Commands::fillCommandBox() {

	this->commandList->BeginUpdate();

	List<String^>^ sectionData = gcnew List<String^>();

	if (this->ini->getSectionData("commands", sectionData)) {
		this->commandList->Items->Clear();
	
		//iterate through the sectionKeys and put the commands in the comboBox
		for each (String^ item in sectionData) {
			array<String^>^ keyValue = item->Split('=');
			this->commandList->Items->Add(keyValue[1]);
		}
	}
	this->commandList->EndUpdate();
	this->selectedLine = -1;
}

System::String^ QuakeLiveRcon::Commands::commandEntry() {
	TextEntry^ entryDialog = gcnew TextEntry(this->entryLabel, this->editText);
	String^ entry = "";

	// Show entryDialog as a modal dialog and determine if DialogResult = OK.
	if (entryDialog->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		// Read the contents of entryDialog's text TextBox.
		entry = entryDialog->text->Text;
	}

	delete entryDialog;
	return entry;
}

System::Void QuakeLiveRcon::Commands::swapCommands(int from, String^ fromString, int to, String^ toString) {
	this->ini->writeValue("commands", System::Convert::ToString(from), toString);
	this->ini->writeValue("commands", System::Convert::ToString(to), fromString);
}
