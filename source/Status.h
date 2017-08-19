/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.4 on 8/18/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#pragma once

#include <winsock2.h>
#include <windows.h>

#include "msclr\marshal.h"
#include "zmq.h"
//#include "zhelpers.h"
#include <assert.h>     /* assert */

//#define POLL_TIMEOUT 1

namespace QuakeLiveRcon {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for Status
	/// </summary>
	public ref class Status : public System::Windows::Forms::Form {

	private:
		bool disconnect; //used to signal shutdown
		array<System::String^>^ info; //used to store the server information and colors
		//this->info[0] is the IP; this->info[1] is the Game Port; this->info[2] is the Password; this->info[3] is the UUID; this->info[4] thru this->info[12] are the Colors
		Thread^ statusThread; //thread used for the server communications

	public:
		Status(array<System::String^>^ info);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Status();
	private: System::Windows::Forms::RichTextBox^  serverStatus;
	private: System::Windows::Forms::Button^  close;
	protected:



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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Status::typeid));
			this->serverStatus = (gcnew System::Windows::Forms::RichTextBox());
			this->close = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// serverStatus
			// 
			this->serverStatus->BackColor = System::Drawing::Color::Black;
			this->serverStatus->ForeColor = System::Drawing::Color::White;
			this->serverStatus->Location = System::Drawing::Point(0, 24);
			this->serverStatus->Name = L"serverStatus";
			this->serverStatus->Size = System::Drawing::Size(466, 284);
			this->serverStatus->TabIndex = 0;
			this->serverStatus->Text = L"";
			// 
			// close
			// 
			this->close->BackColor = System::Drawing::Color::Black;
			this->close->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->close->Location = System::Drawing::Point(389, 0);
			this->close->Name = L"close";
			this->close->Size = System::Drawing::Size(75, 23);
			this->close->TabIndex = 1;
			this->close->Text = L"Close";
			this->close->UseVisualStyleBackColor = false;
			this->close->Click += gcnew System::EventHandler(this, &Status::close_Click);
			// 
			// Status
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(466, 306);
			this->Controls->Add(this->close);
			this->Controls->Add(this->serverStatus);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Status";
			this->Text = L"Server Status";
			this->Load += gcnew System::EventHandler(this, &Status::Window_Load);
			this->Shown += gcnew System::EventHandler(this, &Status::Window_Shown);
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void close_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Window_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Window_Shown(System::Object^  sender, System::EventArgs^  e);

	private: void connectToServer();
	//private: bool checkMonitor(void *monitor, int* eventNum);
	private: System::String^ formatMessage(System::String^ message);
	//private: void displayText(String^ text);
	private: void displayServerMessage(System::String^ text);


	};
}
