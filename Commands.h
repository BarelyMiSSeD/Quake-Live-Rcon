/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.4 on 8/18/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#pragma once

#include <winsock2.h>
//#include <windows.h>
#include "IniEditor.h"
#include "TextEntry.h"
#include "QLRcon.h"

namespace QuakeLiveRcon {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Commands
	/// </summary>
	public ref class Commands : public System::Windows::Forms::Form	{
	private: IniEditor^ ini; //Use the IniEditor.h to manage the server ini file
	private: int tab; //used to track the tab number so the command is sent to the correct server
	private: int lineNum; //used to store the selected line in the commandList listbox
	private: int selectedLine; //used to store the selected index of the commandList listbox
	private: String^ commandText; //store the selected command text
	private: String^ entryLabel; //used to store the label sent to the TextEntry Form
	private: String^ editText; //used to pass the command to edit
	private: System::Windows::Forms::Button^  moveUp;
	private: System::Windows::Forms::Button^  moveDown;
	private: String^ entryText; //used to store the text input by the user from the TextEntry Form

	public:
		Commands(const char *file, int tab);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Commands();

	private: System::Windows::Forms::Label^  serverCommandsLabel;
	private: System::Windows::Forms::ListBox^  commandList;
	private: System::Windows::Forms::Button^  addCommand;
	private: System::Windows::Forms::Button^  editCommand;
	private: System::Windows::Forms::Button^  deleteCommand;
	private: System::Windows::Forms::Button^  sendCommand;
	private: System::Windows::Forms::Button^  close;
	protected:

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Commands::typeid));
			this->serverCommandsLabel = (gcnew System::Windows::Forms::Label());
			this->commandList = (gcnew System::Windows::Forms::ListBox());
			this->editCommand = (gcnew System::Windows::Forms::Button());
			this->deleteCommand = (gcnew System::Windows::Forms::Button());
			this->sendCommand = (gcnew System::Windows::Forms::Button());
			this->addCommand = (gcnew System::Windows::Forms::Button());
			this->close = (gcnew System::Windows::Forms::Button());
			this->moveUp = (gcnew System::Windows::Forms::Button());
			this->moveDown = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// serverCommandsLabel
			// 
			this->serverCommandsLabel->AutoSize = true;
			this->serverCommandsLabel->Location = System::Drawing::Point(47, 14);
			this->serverCommandsLabel->Name = L"serverCommandsLabel";
			this->serverCommandsLabel->Size = System::Drawing::Size(124, 13);
			this->serverCommandsLabel->TabIndex = 0;
			this->serverCommandsLabel->Text = L"Saved server commands";
			// 
			// commandList
			// 
			this->commandList->FormattingEnabled = true;
			this->commandList->Location = System::Drawing::Point(4, 30);
			this->commandList->Name = L"commandList";
			this->commandList->Size = System::Drawing::Size(291, 212);
			this->commandList->TabIndex = 1;
			this->commandList->SelectedIndexChanged += gcnew System::EventHandler(this, &Commands::commandList_SelectedIndexChanged);
			// 
			// editCommand
			// 
			this->editCommand->Location = System::Drawing::Point(109, 277);
			this->editCommand->Name = L"editCommand";
			this->editCommand->Size = System::Drawing::Size(75, 23);
			this->editCommand->TabIndex = 4;
			this->editCommand->Text = L"Edit";
			this->editCommand->UseVisualStyleBackColor = true;
			this->editCommand->Click += gcnew System::EventHandler(this, &Commands::editCommand_Click);
			// 
			// deleteCommand
			// 
			this->deleteCommand->Location = System::Drawing::Point(190, 277);
			this->deleteCommand->Name = L"deleteCommand";
			this->deleteCommand->Size = System::Drawing::Size(75, 23);
			this->deleteCommand->TabIndex = 5;
			this->deleteCommand->Text = L"Delete";
			this->deleteCommand->UseVisualStyleBackColor = true;
			this->deleteCommand->Click += gcnew System::EventHandler(this, &Commands::deleteCommand_Click);
			// 
			// sendCommand
			// 
			this->sendCommand->Location = System::Drawing::Point(60, 248);
			this->sendCommand->Name = L"sendCommand";
			this->sendCommand->Size = System::Drawing::Size(75, 23);
			this->sendCommand->TabIndex = 6;
			this->sendCommand->Text = L"Send";
			this->sendCommand->UseVisualStyleBackColor = true;
			this->sendCommand->Click += gcnew System::EventHandler(this, &Commands::sendCommand_Click);
			// 
			// addCommand
			// 
			this->addCommand->Location = System::Drawing::Point(28, 277);
			this->addCommand->Name = L"addCommand";
			this->addCommand->Size = System::Drawing::Size(75, 23);
			this->addCommand->TabIndex = 7;
			this->addCommand->Text = L"Add";
			this->addCommand->UseVisualStyleBackColor = true;
			this->addCommand->Click += gcnew System::EventHandler(this, &Commands::addCommand_Click);
			// 
			// close
			// 
			this->close->Location = System::Drawing::Point(153, 248);
			this->close->Name = L"close";
			this->close->Size = System::Drawing::Size(75, 23);
			this->close->TabIndex = 8;
			this->close->Text = L"Close";
			this->close->UseVisualStyleBackColor = true;
			this->close->Click += gcnew System::EventHandler(this, &Commands::close_Click);
			// 
			// moveUp
			// 
			this->moveUp->Location = System::Drawing::Point(296, 69);
			this->moveUp->Name = L"moveUp";
			this->moveUp->Size = System::Drawing::Size(45, 23);
			this->moveUp->TabIndex = 9;
			this->moveUp->Text = L"Up";
			this->moveUp->UseVisualStyleBackColor = true;
			this->moveUp->Click += gcnew System::EventHandler(this, &Commands::moveUp_Click);
			// 
			// moveDown
			// 
			this->moveDown->Location = System::Drawing::Point(296, 98);
			this->moveDown->Name = L"moveDown";
			this->moveDown->Size = System::Drawing::Size(45, 23);
			this->moveDown->TabIndex = 10;
			this->moveDown->Text = L"Down";
			this->moveDown->UseVisualStyleBackColor = true;
			this->moveDown->Click += gcnew System::EventHandler(this, &Commands::moveDown_Click);
			// 
			// Commands
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightGray;
			this->ClientSize = System::Drawing::Size(342, 305);
			this->Controls->Add(this->moveDown);
			this->Controls->Add(this->moveUp);
			this->Controls->Add(this->close);
			this->Controls->Add(this->addCommand);
			this->Controls->Add(this->sendCommand);
			this->Controls->Add(this->deleteCommand);
			this->Controls->Add(this->editCommand);
			this->Controls->Add(this->commandList);
			this->Controls->Add(this->serverCommandsLabel);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Commands";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Server Commands";
			this->Shown += gcnew System::EventHandler(this, &Commands::Window_Shown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Window_Shown(System::Object^  sender, System::EventArgs^  e);
	private: System::Void commandList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void addCommand_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void editCommand_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void deleteCommand_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void sendCommand_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void close_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void moveUp_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void moveDown_Click(System::Object^  sender, System::EventArgs^  e);
			 
	private: System::String^ commandEntry();
	private: System::Void fillCommandBox();
	private: System::Void addNewCommand(String^ command);
	private: System::Void deleteSelectedCommand(int num);
	private: System::Void editSelectedCommand(int num, String^ command);
	private: System::Void swapCommands(int from, String^ fromString, int to, String^ toString);
};
}
