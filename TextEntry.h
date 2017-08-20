/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.5 on 8/20/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#pragma once

namespace QuakeLiveRcon {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for TextEntry
	/// </summary>
	public ref class TextEntry : public System::Windows::Forms::Form
	{
	public:
		TextEntry(System::String^ titleString, System::String^ entryString);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TextEntry();
	protected:


	private: System::Windows::Forms::Label^  description;
	public: System::Windows::Forms::TextBox^  text;
	private: System::Windows::Forms::Button^  okButton;
	private: System::Windows::Forms::Button^  cancel;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TextEntry::typeid));
			this->description = (gcnew System::Windows::Forms::Label());
			this->text = (gcnew System::Windows::Forms::TextBox());
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->cancel = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// description
			// 
			this->description->AutoSize = true;
			this->description->Location = System::Drawing::Point(13, 13);
			this->description->Name = L"description";
			this->description->Size = System::Drawing::Size(60, 13);
			this->description->TabIndex = 0;
			this->description->Text = L"Description";
			this->description->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// text
			// 
			this->text->Location = System::Drawing::Point(13, 30);
			this->text->Name = L"text";
			this->text->Size = System::Drawing::Size(351, 20);
			this->text->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &TextEntry::text_KeyPress);
			this->text->TabIndex = 1;
			// 
			// okButton
			// 
			this->okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->okButton->Location = System::Drawing::Point(233, 56);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(75, 23);
			this->okButton->TabIndex = 2;
			this->okButton->Text = L"OK";
			this->okButton->UseVisualStyleBackColor = true;
			this->okButton->Click += gcnew System::EventHandler(this, &TextEntry::okButton_Click);
			// 
			// cancel
			// 
			this->cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancel->Location = System::Drawing::Point(78, 56);
			this->cancel->Name = L"cancel";
			this->cancel->Size = System::Drawing::Size(75, 23);
			this->cancel->TabIndex = 3;
			this->cancel->Text = L"Cancel";
			this->cancel->UseVisualStyleBackColor = true;
			this->cancel->Click += gcnew System::EventHandler(this, &TextEntry::cancel_Click);
			// 
			// TextEntry
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightGray;
			this->ClientSize = System::Drawing::Size(376, 84);
			this->Controls->Add(this->cancel);
			this->Controls->Add(this->okButton);
			this->Controls->Add(this->text);
			this->Controls->Add(this->description);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"TextEntry";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"TextEntry";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void text_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void okButton_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void cancel_Click(System::Object^  sender, System::EventArgs^  e);
};
}
