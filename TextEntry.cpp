/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.5 on 8/20/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#include "TextEntry.h"

QuakeLiveRcon::TextEntry::TextEntry(System::String^ titleString, System::String^ entryString) {
	InitializeComponent();

	this->description->Text = titleString;
	this->text->Text = entryString;
}

QuakeLiveRcon::TextEntry::~TextEntry() {
	if (components)
	{
		delete components;
	}
}

System::Void QuakeLiveRcon::TextEntry::okButton_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Close();
}

System::Void QuakeLiveRcon::TextEntry::cancel_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Close();
}

System::Void QuakeLiveRcon::TextEntry::text_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (char)Keys::Enter) {
		e->Handled = true;
		if (this->text->Text->Length > 0)
			this->okButton->PerformClick();
	}
}