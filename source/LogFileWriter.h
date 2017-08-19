/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.4 on 8/18/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#pragma once

using namespace System;
using namespace System::IO;

#define MAX_LINES_STORED 100
#define MAX_MB_FILE_SIZE 5

public ref class LogFileWriter {

private:
	int activeArray;
	int storedLines;
	array<String^>^ writeArray1;
	array<String^>^ writeArray2;
	String^ fileName;
	String^ logLocation;

	//writes the filled array to the file
	void writeToFile(int fullArray);
	//writes the supplied String to the file
	void writeToFile(String^ line);


public:
	//Constructor (Creates the logLocation directory if it does not exist)
	LogFileWriter(String^ logLocation);
	LogFileWriter(String^ fileName, String^ logLocation);
	//Destructor
	~LogFileWriter();
	//puts supplied String into a storage array and calls the writeToFile function when array is full
	void storeEntry(String^ line);
	//writes the lines in the storage array to the file and returns 'true' when complete
	bool writeRemaining();
	//deletes files in the logfile directory that are older then the supplied DateTime unless they are in the exclusions List (returns -1 if directory doesn't exist)
	int deleteOldFiles(DateTime time, System::Collections::Generic::List<String^>^ exclusions);

};