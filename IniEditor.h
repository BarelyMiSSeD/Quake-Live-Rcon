/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.4 on 8/18/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#pragma once

#include <string>
#include <sstream>
#include <windows.h>
#include <vcclr.h>

#define lpszReturnBufferSize 500


using namespace System;
using namespace System::Collections::Generic;


public ref class IniEditor {
private:
	String^ lpFileName;

public:
	///Constructors
	IniEditor();
	IniEditor(char fileName[]);
	IniEditor(const char *fileName);
	IniEditor(String^ fileName);

	//Destructor
	~IniEditor();

	//Functions
	void setFilePath(const char *filePath);
	void setFilePath(String^ filePath);
	void setFileName(const char *fileName);
	void setFileName(String^ fileName);
	bool isValidSection(String^ section);
	void getSectionNames(List<String^>^ sectionList);
	bool getSectionKeys(String^ section, List<String^>^ keyList);
	bool getSectionData(String^ section, List<String^>^ sectionDataList);
	String^ getValue(String^ section, String^ key);
	String^ getValue(String^ section, String^ key, String^ defaultValue);
	int getInt(String^ section, String^ key, int defaultValue);
	double getDouble(String^ section, String^ key, double defaultValue);
	bool getBoolean(String^ section, String^ key, bool defaultValue);
	bool isTrue(String^ section, String^ key);
	void writeValue(String^ section, String^ key, String^ value);
	void writeValue(String^ section, String^ key, int value);
	void writeValue(String^ section, String^ key, double value);
	void writeValue(String^ section, String^ key, bool value);
	void deleteSection(String^ section);
	void deleteKey(String^ section, String^ key);

};
