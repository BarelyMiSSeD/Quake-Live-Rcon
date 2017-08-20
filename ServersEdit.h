/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.5 on 8/20/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#pragma once

#include "IniEditor.h"

namespace QuakeLiveRcon {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ServersEdit
	/// </summary>
	public ref class ServersEdit : public System::Windows::Forms::Form {
	private:
		IniEditor^ ini; //Use the IniEditor.h to manage the server ini file
		List<String^>^ sections; // used to store the server IP:PORT sections of the ini file
		List<String^>^ serverNames; // used to store the server names
	private: System::Windows::Forms::CheckBox^  alphabeticSort;
			 List<String^>^ keys; //used to store the keys of a section

	public:
		ServersEdit(void);
		ServersEdit(const char *file);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ServersEdit();

	private: System::Windows::Forms::Label^  savedServersLabel;
	private: System::Windows::Forms::ComboBox^  savedServers;
	private: System::Windows::Forms::Label^  detailsLabel;
	private: System::Windows::Forms::CheckBox^  connectOnStart;
	private: System::Windows::Forms::Label^  ipLabel;
	private: System::Windows::Forms::TextBox^  ip;
	private: System::Windows::Forms::Label^  portLabel;
	private: System::Windows::Forms::TextBox^  port;
	private: System::Windows::Forms::Label^  nameLabel;
	private: System::Windows::Forms::TextBox^  name;
	private: System::Windows::Forms::Label^  passwordLabel;
	private: System::Windows::Forms::TextBox^  password;
	private: System::Windows::Forms::CheckBox^  logRcon;
	private: System::Windows::Forms::Button^  save;
	private: System::Windows::Forms::Button^  deleteServer;
	private: System::Windows::Forms::Button^  close;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ServersEdit::typeid));
			this->savedServersLabel = (gcnew System::Windows::Forms::Label());
			this->savedServers = (gcnew System::Windows::Forms::ComboBox());
			this->detailsLabel = (gcnew System::Windows::Forms::Label());
			this->connectOnStart = (gcnew System::Windows::Forms::CheckBox());
			this->ipLabel = (gcnew System::Windows::Forms::Label());
			this->ip = (gcnew System::Windows::Forms::TextBox());
			this->portLabel = (gcnew System::Windows::Forms::Label());
			this->port = (gcnew System::Windows::Forms::TextBox());
			this->nameLabel = (gcnew System::Windows::Forms::Label());
			this->name = (gcnew System::Windows::Forms::TextBox());
			this->passwordLabel = (gcnew System::Windows::Forms::Label());
			this->password = (gcnew System::Windows::Forms::TextBox());
			this->save = (gcnew System::Windows::Forms::Button());
			this->deleteServer = (gcnew System::Windows::Forms::Button());
			this->close = (gcnew System::Windows::Forms::Button());
			this->logRcon = (gcnew System::Windows::Forms::CheckBox());
			this->alphabeticSort = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// savedServersLabel
			// 
			this->savedServersLabel->AutoSize = true;
			this->savedServersLabel->Location = System::Drawing::Point(24, 9);
			this->savedServersLabel->Name = L"savedServersLabel";
			this->savedServersLabel->Size = System::Drawing::Size(96, 13);
			this->savedServersLabel->TabIndex = 0;
			this->savedServersLabel->Text = L"#of Saved Servers";
			// 
			// savedServers
			// 
			this->savedServers->BackColor = System::Drawing::Color::WhiteSmoke;
			this->savedServers->FormattingEnabled = true;
			this->savedServers->Location = System::Drawing::Point(12, 25);
			this->savedServers->Name = L"savedServers";
			this->savedServers->Size = System::Drawing::Size(298, 21);
			this->savedServers->TabIndex = 1;
			this->savedServers->SelectedIndexChanged += gcnew System::EventHandler(this, &ServersEdit::savedServers_SelectedIndexChanged);
			// 
			// detailsLabel
			// 
			this->detailsLabel->AutoSize = true;
			this->detailsLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->detailsLabel->Location = System::Drawing::Point(106, 60);
			this->detailsLabel->Name = L"detailsLabel";
			this->detailsLabel->Size = System::Drawing::Size(175, 20);
			this->detailsLabel->TabIndex = 2;
			this->detailsLabel->Text = L"Selected Server Details";
			// 
			// connectOnStart
			// 
			this->connectOnStart->AutoSize = true;
			this->connectOnStart->Location = System::Drawing::Point(110, 83);
			this->connectOnStart->Name = L"connectOnStart";
			this->connectOnStart->Size = System::Drawing::Size(194, 17);
			this->connectOnStart->TabIndex = 3;
			this->connectOnStart->Text = L"Connect to Server on Program Start";
			this->connectOnStart->UseVisualStyleBackColor = true;
			// 
			// ipLabel
			// 
			this->ipLabel->AutoSize = true;
			this->ipLabel->Location = System::Drawing::Point(45, 112);
			this->ipLabel->Name = L"ipLabel";
			this->ipLabel->Size = System::Drawing::Size(58, 13);
			this->ipLabel->TabIndex = 4;
			this->ipLabel->Text = L"IP Address";
			// 
			// ip
			// 
			this->ip->Location = System::Drawing::Point(108, 110);
			this->ip->Name = L"ip";
			this->ip->Size = System::Drawing::Size(198, 20);
			this->ip->TabIndex = 5;
			this->ip->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ServersEdit::ip_KeyDown);
			this->ip->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ServersEdit::ip_KeyPress);
			// 
			// portLabel
			// 
			this->portLabel->AutoSize = true;
			this->portLabel->Location = System::Drawing::Point(77, 144);
			this->portLabel->Name = L"portLabel";
			this->portLabel->Size = System::Drawing::Size(26, 13);
			this->portLabel->TabIndex = 6;
			this->portLabel->Text = L"Port";
			// 
			// port
			// 
			this->port->Location = System::Drawing::Point(108, 142);
			this->port->Name = L"port";
			this->port->Size = System::Drawing::Size(198, 20);
			this->port->TabIndex = 7;
			this->port->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ServersEdit::port_KeyDown);
			this->port->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ServersEdit::port_KeyPress);
			// 
			// nameLabel
			// 
			this->nameLabel->AutoSize = true;
			this->nameLabel->Location = System::Drawing::Point(68, 176);
			this->nameLabel->Name = L"nameLabel";
			this->nameLabel->Size = System::Drawing::Size(35, 13);
			this->nameLabel->TabIndex = 8;
			this->nameLabel->Text = L"Name";
			// 
			// name
			// 
			this->name->Location = System::Drawing::Point(108, 174);
			this->name->Name = L"name";
			this->name->Size = System::Drawing::Size(198, 20);
			this->name->TabIndex = 9;
			// 
			// passwordLabel
			// 
			this->passwordLabel->AutoSize = true;
			this->passwordLabel->Location = System::Drawing::Point(14, 208);
			this->passwordLabel->Name = L"passwordLabel";
			this->passwordLabel->Size = System::Drawing::Size(87, 13);
			this->passwordLabel->TabIndex = 10;
			this->passwordLabel->Text = L"RCON Password";
			// 
			// password
			// 
			this->password->Location = System::Drawing::Point(108, 206);
			this->password->Name = L"password";
			this->password->Size = System::Drawing::Size(198, 20);
			this->password->TabIndex = 11;
			this->password->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ServersEdit::password_KeyPress);
			// 
			// save
			// 
			this->save->Location = System::Drawing::Point(121, 259);
			this->save->Name = L"save";
			this->save->Size = System::Drawing::Size(75, 23);
			this->save->TabIndex = 12;
			this->save->Text = L"Save";
			this->save->UseVisualStyleBackColor = true;
			this->save->Click += gcnew System::EventHandler(this, &ServersEdit::save_Click);
			// 
			// deleteServer
			// 
			this->deleteServer->Location = System::Drawing::Point(219, 259);
			this->deleteServer->Name = L"deleteServer";
			this->deleteServer->Size = System::Drawing::Size(75, 23);
			this->deleteServer->TabIndex = 13;
			this->deleteServer->Text = L"Delete";
			this->deleteServer->UseVisualStyleBackColor = true;
			this->deleteServer->Click += gcnew System::EventHandler(this, &ServersEdit::deleteServer_Click);
			// 
			// close
			// 
			this->close->Location = System::Drawing::Point(169, 306);
			this->close->Name = L"close";
			this->close->Size = System::Drawing::Size(75, 23);
			this->close->TabIndex = 14;
			this->close->Text = L"Close";
			this->close->UseVisualStyleBackColor = true;
			this->close->Click += gcnew System::EventHandler(this, &ServersEdit::close_Click);
			// 
			// logRcon
			// 
			this->logRcon->AutoSize = true;
			this->logRcon->Location = System::Drawing::Point(110, 236);
			this->logRcon->Name = L"logRcon";
			this->logRcon->Size = System::Drawing::Size(129, 17);
			this->logRcon->TabIndex = 15;
			this->logRcon->Text = L"Log RCON info to File";
			this->logRcon->UseVisualStyleBackColor = true;
			// 
			// alphabeticSort
			// 
			this->alphabeticSort->AutoSize = true;
			this->alphabeticSort->Location = System::Drawing::Point(197, 8);
			this->alphabeticSort->Name = L"alphabeticSort";
			this->alphabeticSort->Size = System::Drawing::Size(113, 17);
			this->alphabeticSort->TabIndex = 16;
			this->alphabeticSort->Text = L"Sort Alphabetically";
			this->alphabeticSort->UseVisualStyleBackColor = true;
			//this->alphabeticSort->CheckedChanged += gcnew System::EventHandler(this, &ServersEdit::alphabeticSort_CheckedChanged);
			this->alphabeticSort->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &ServersEdit::alphabeticSort_MouseUp);
			// 
			// ServersEdit
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DarkGray;
			this->ClientSize = System::Drawing::Size(330, 360);
			this->Controls->Add(this->alphabeticSort);
			this->Controls->Add(this->logRcon);
			this->Controls->Add(this->close);
			this->Controls->Add(this->deleteServer);
			this->Controls->Add(this->save);
			this->Controls->Add(this->password);
			this->Controls->Add(this->passwordLabel);
			this->Controls->Add(this->name);
			this->Controls->Add(this->nameLabel);
			this->Controls->Add(this->port);
			this->Controls->Add(this->portLabel);
			this->Controls->Add(this->ip);
			this->Controls->Add(this->ipLabel);
			this->Controls->Add(this->connectOnStart);
			this->Controls->Add(this->detailsLabel);
			this->Controls->Add(this->savedServers);
			this->Controls->Add(this->savedServersLabel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"ServersEdit";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Edit Saved Servers";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void close_Click(System::Object^  sender, System::EventArgs^  e);	
	private: void fillComboBox();	
	private: System::Void savedServers_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);	
	private: System::Void save_Click(System::Object^  sender, System::EventArgs^  e);
	private: bool checkIpFormat(String^ ip);	
	//Select a server in the combobox based on server name
	private: void selectServer(String ^ name);	
	//Delete the selected server from the saved servers
	private: System::Void deleteServer_Click(System::Object^  sender, System::EventArgs^  e);
	//do not allow spaces in the password textbox
	private: System::Void password_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	//do not allow spaces; only allow digits and dots and 15 chars max in tha ip textbox (allow backspace)
	private: System::Void ip_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void ip_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
	//do not allow spaces; only allow digits and 6 chars max in the port textbox (allow backspace)
	private: System::Void port_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void port_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
	public: static bool isServerIpPort(String^ ipPort);
	//private: System::Void alphabeticSort_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void alphabeticSort_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
};
}
