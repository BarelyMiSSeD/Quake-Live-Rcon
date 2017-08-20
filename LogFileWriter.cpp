/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.4 on 8/18/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#include "LogFileWriter.h"

LogFileWriter::LogFileWriter(String^ logLocation) {
	this->activeArray = 1;
	this->storedLines = 0;
	this->writeArray1 = gcnew array<String^>(MAX_LINES_STORED);
	this->writeArray2 = gcnew array<String^>(MAX_LINES_STORED);
	this->fileName = "";
	this->logLocation = logLocation;
}

LogFileWriter::LogFileWriter(String^ fileName, String^ logLocation) {
	this->activeArray = 1;
	this->storedLines = 0;
	this->writeArray1 = gcnew array<String^>(MAX_LINES_STORED);
	this->writeArray2 = gcnew array<String^>(MAX_LINES_STORED);
	this->fileName = fileName;
	this->logLocation = logLocation;

	if (!Directory::Exists(this->logLocation))
		Directory::CreateDirectory(this->logLocation);
}

LogFileWriter::~LogFileWriter() {
	delete writeArray1;
	writeArray1 = nullptr;
	delete writeArray2;
	writeArray2 = nullptr;
	delete fileName;
	fileName = nullptr;
	delete logLocation;
	logLocation = nullptr;
}

//Save line to the active array; if full, switch active array to other array and write full array to log file
void LogFileWriter::storeEntry(String^ line) {
	if (String::Compare(this->fileName, "")) {
		switch (this->activeArray) {
		case 1:
			this->writeArray1[this->storedLines] = DateTime::Now + ": " + line;
			this->storedLines++;
			if (this->storedLines == MAX_LINES_STORED) {
				this->activeArray = 2;
				this->storedLines = 0;
				this->writeToFile(1);
			}
			break;
		case 2:
			this->writeArray2[this->storedLines] = DateTime::Now + ": " + line;
			this->storedLines++;
			if (this->storedLines == MAX_LINES_STORED) {
				this->activeArray = 1;
				this->storedLines = 0;
				this->writeToFile(2);
			}
			break;
		}
	}
}

//Write full array to log file
void LogFileWriter::writeToFile(int fullArray) {
	if (String::Compare(this->fileName, "")) {
		bool create = false;
		String^ file = this->logLocation + this->fileName;
		FileInfo^ fileInfo = gcnew FileInfo(gcnew String(file + ".txt"));
		FileStream^ fStream = nullptr;

		if (fileInfo->Exists) {
			if (fileInfo->Length / 1000000 >= MAX_MB_FILE_SIZE) {
				create = true;
				bool found = false;
				int append = 1;
				String^ newFileName = nullptr;
				FileInfo^ checkFileName = nullptr;
				while (!found) {
					newFileName = file + "_" + append + ".txt";
					checkFileName = gcnew FileInfo(newFileName);
					if (!checkFileName->Exists) {
						fileInfo->CopyTo(newFileName);
						fileInfo->Delete();
						found = true;
					}
					append++;
				}
				if (newFileName != nullptr) {
					delete newFileName;
					newFileName = nullptr;
				}
				if (checkFileName != nullptr) {
					delete checkFileName;
					checkFileName = nullptr;
				}
			}
		}


		if (!fileInfo->Exists || create) {
			fStream = gcnew FileStream(gcnew String(file + ".txt"), FileMode::Create, FileAccess::Write);
		}
		else {
			fStream = gcnew FileStream(gcnew String(file + ".txt"), FileMode::Append, FileAccess::Write);
		}

		//FileStream^ fStream = gcnew FileStream(gcnew String(file + ".txt"), FileMode::OpenOrCreate, FileAccess::Write);

		StreamWriter^ writeToFile = gcnew StreamWriter(fStream);

		switch (fullArray) {
		case 1: {
			for (int i = 0; i < MAX_LINES_STORED; i++) {
				writeToFile->Write(this->writeArray1[i]);
			}
			//System::Array::Clear(this->writeArray1, 0, MAX_LINES_STORED);
			this->writeArray1 = gcnew array<String^>(MAX_LINES_STORED);
		}
				break;
		case 2: {
			for (int i = 0; i < MAX_LINES_STORED; i++) {
				writeToFile->Write(this->writeArray2[i]);
			}
			//System::Array::Clear(this->writeArray2, 0, MAX_LINES_STORED);
			this->writeArray2 = gcnew array<String^>(MAX_LINES_STORED);
		}
				break;
		}
		writeToFile->Close();
		fStream->Close();
		delete file;
		file = nullptr;
		delete fileInfo;
		fileInfo = nullptr;
		if (fStream != nullptr) {
			delete fStream;
			fStream = nullptr;
		}
		delete (IDisposable^)writeToFile;
	}
}

//Write line to log file
void LogFileWriter::writeToFile(String^ line) {
	if (String::Compare(this->fileName, "")) {
		bool create = false;
		String^ file = this->logLocation + this->fileName;
		FileInfo^ fileInfo = gcnew FileInfo(gcnew String(file + ".txt"));
		FileStream^ fStream = nullptr;

		if (fileInfo->Exists) {
			if (fileInfo->Length / 1000000 >= MAX_MB_FILE_SIZE) {
				create = true;
				bool found = false;
				int append = 1;
				String^ newFileName = nullptr;
				FileInfo^ checkFileName = nullptr;
				while (!found) {
					newFileName = file + "_" + append + ".txt";
					checkFileName = gcnew FileInfo(newFileName);
					if (!checkFileName->Exists) {
						fileInfo->CopyTo(newFileName);
						fileInfo->Delete();
						found = true;
					}
					append++;
				}
				if (newFileName != nullptr) {
					delete newFileName;
					newFileName = nullptr;
				}
				if (checkFileName != nullptr) {
					delete checkFileName;
					checkFileName = nullptr;
				}
			}
		}


		if (!fileInfo->Exists || create) {
			fStream = gcnew FileStream(gcnew String(file + ".txt"), FileMode::Create, FileAccess::Write);
		}
		else {
			fStream = gcnew FileStream(gcnew String(file + ".txt"), FileMode::Append, FileAccess::Write);
		}

		StreamWriter^ writeToFile = gcnew StreamWriter(fStream);

		writeToFile->Write(line);

		writeToFile->Close();
		fStream->Close();
		delete file;
		file = nullptr;
		delete fileInfo;
		fileInfo = nullptr;
		if (fStream != nullptr) {
			delete fStream;
			fStream = nullptr;
		}
		delete (IDisposable^)writeToFile;
	}
}

bool LogFileWriter::writeRemaining() {
	if (String::Compare(this->fileName, "")) {
		bool create = false;
		String^ file = this->logLocation + this->fileName;
		FileInfo^ fileInfo = gcnew FileInfo(gcnew String(file + ".txt"));
		FileStream^ fStream = nullptr;

		if (fileInfo->Exists) {
			if (fileInfo->Length / 1000000 >= MAX_MB_FILE_SIZE) {
				create = true;
				bool found = false;
				int append = 1;
				String^ newFileName = nullptr;
				FileInfo^ checkFileName = nullptr;
				while (!found) {
					newFileName = file + "_" + append + ".txt";
					checkFileName = gcnew FileInfo(newFileName);
					if (!checkFileName->Exists) {
						fileInfo->CopyTo(newFileName);
						fileInfo->Delete();
						found = true;
					}
					append++;
				}
				if (newFileName != nullptr) {
					delete newFileName;
					newFileName = nullptr;
				}
				if (checkFileName != nullptr) {
					delete checkFileName;
					checkFileName = nullptr;
				}
			}
		}


		if (!fileInfo->Exists || create) {
			fStream = gcnew FileStream(gcnew String(file + ".txt"), FileMode::Create, FileAccess::Write);
		}
		else {
			fStream = gcnew FileStream(gcnew String(file + ".txt"), FileMode::Append, FileAccess::Write);
		}

		StreamWriter^ writeToFile = gcnew StreamWriter(fStream);

		switch (this->activeArray) {
		case 1:
			for (int i = 0; i <= this->storedLines; i++) {
				writeToFile->Write(this->writeArray1[i]);
			}
			//System::Array::Clear(this->writeArray1, 0, MAX_LINES_STORED);
			delete this->writeArray1;
			this->writeArray1 = gcnew array<String^>(MAX_LINES_STORED);
			break;
		case 2:
			for (int i = 0; i <= this->storedLines; i++) {
				writeToFile->Write(this->writeArray2[i]);
			}
			//System::Array::Clear(this->writeArray2, 0, MAX_LINES_STORED);
			delete this->writeArray2;
			this->writeArray2 = gcnew array<String^>(MAX_LINES_STORED);
			break;
		}

		writeToFile->Close();
		fStream->Close();
		delete file;
		file = nullptr;
		delete fileInfo;
		fileInfo = nullptr;
		if (fStream != nullptr) {
			delete fStream;
			fStream = nullptr;
		}
		delete (IDisposable^)writeToFile;

		return true;
	}
	return false;
}

int LogFileWriter::deleteOldFiles(DateTime time, System::Collections::Generic::List<String^>^ exclusions) {
	int deleteCount = 0;

	if (Directory::Exists(this->logLocation)) {
		//Get a list of the files in the this->logLocation directory
		array<String^>^ files = Directory::GetFiles(this->logLocation);

		//go through the list of files and check for delete qualifications
		for (int i = 0; i < files->Length; i++) {
			FileInfo^ fileInfo = gcnew FileInfo(files[i]);
			//check to see if the file is older then the supplied time and is not in the exclusions list
			if ((time - fileInfo->LastWriteTime).TotalSeconds > 0 && !exclusions->Contains(files[i])) {
				//Delete the file
				File::Delete(files[i]);
				deleteCount++;
			}
		}
	}
	else {
		deleteCount = -1;
	}
	return deleteCount;
}
