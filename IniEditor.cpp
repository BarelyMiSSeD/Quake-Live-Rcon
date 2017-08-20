/*
Quake Live Remote Console Program

Created by James Weber
Version 1.0.7.4 on 8/18/2017

This is released to everyone, as-is, there is no warranty or guarantee.
*/

#include "IniEditor.h"

///Constructors
IniEditor::IniEditor() {
	this->lpFileName = nullptr;
}
IniEditor::IniEditor(char fileName[]) {
	//char * path;
	//path = _getcwd(NULL, 0);
	//this->lpFileName = gcnew String(path) + "\\" + gcnew String(fileName);
	this->lpFileName = ".\\" + gcnew String(fileName);
}
IniEditor::IniEditor(const char *fileName) {
	//char * path;
	//path = _getcwd(NULL, 0);
	//this->lpFileName = gcnew String(path) + "\\" + gcnew String(fileName);
	this->lpFileName = ".\\" + gcnew String(fileName);
}
IniEditor::IniEditor(String^ fileName) {
	//char * path;
	//path = _getcwd(NULL, 0);
	//this->lpFileName = gcnew String(path) + "\\" + fileName;
	this->lpFileName = ".\\" + fileName;
}

///Destructor
IniEditor::~IniEditor() {}

///Functions
void IniEditor::setFilePath(const char *filePath) {
	if (filePath != NULL)
		this->lpFileName = gcnew String(filePath);
}

void IniEditor::setFilePath(String^ filePath) {
	if (!String::IsNullOrEmpty(filePath))
		this->lpFileName = filePath;
}

void IniEditor::setFileName(const char *fileName) {
	if (fileName != NULL) {
		//char * path;
		//path = _getcwd(NULL, 0);
		//this->lpFileName = gcnew String(path) + "\\" + gcnew String(fileName);
		this->lpFileName = ".\\" + gcnew String(fileName);
	}
}

void IniEditor::setFileName(String^ fileName) {
	if (!String::IsNullOrEmpty(fileName)) {
		//char * path;
		//path = _getcwd(NULL, 0);
		//this->lpFileName = gcnew String(path) + "\\" + fileName;
		this->lpFileName = ".\\" + fileName;
	}
}

/*
DWORD WINAPI GetPrivateProfileString(
_In_  LPCTSTR lpAppName,
_In_  LPCTSTR lpKeyName,
_In_  LPCTSTR lpDefault,
_Out_ LPTSTR  lpReturnedString,
_In_  DWORD   nSize,
_In_  LPCTSTR lpFileName
);

lpAppName = section of ini
lpKeyName = key of section
lpDefault = default return
lpReturnedString = returned vaue of key
nSize = size of return buffer
lpFileName = file name of ini file

If lpAppName is NULL, GetPrivateProfileString copies all section names in the specified file to the supplied buffer.
If lpKeyName is NULL, the function copies all key names in the specified section to the supplied buffer.
An application can use this method to enumerate all of the sections and keys in a file. In either case, each string is
followed by a null character and the final string is followed by a second null character. If the supplied destination
buffer is too small to hold all the strings, the last string is truncated and followed by two null characters.
*/
bool IniEditor::isValidSection(String^ section) {
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName)) {
		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(this->lpFileName);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * filePath = new wchar_t[origsize2];
		wcscpy_s(filePath, origsize2, wch2);

		LPTSTR lpReturnedString = new wchar_t[lpszReturnBufferSize];
		DWORD charsCopied = GetPrivateProfileStringW(Section, NULL, L"", lpReturnedString, lpszReturnBufferSize, filePath);

		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
		delete[] lpReturnedString;
		lpReturnedString = NULL;

		return (charsCopied > 0);
	}
	return false;
}

/*
DWORD WINAPI GetPrivateProfileSectionNames(
_Out_ LPTSTR  lpszReturnBuffer,
_In_  DWORD   nSize,
_In_  LPCTSTR lpFileName
);

lpszReturnBuffer = returned buffer of section names
nSize = seize of return buffer
lpFileName = file name of ini file
*/
void IniEditor::getSectionNames(List<String^>^ sectionList) {
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName)) {
		//clear the section names list
		sectionList->Clear();

		//Convert String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(this->lpFileName);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * filePath = new wchar_t[origsize];
		wcscpy_s(filePath, origsize, wch);

		LPTSTR lpReturnedBuffer = new wchar_t[lpszReturnBufferSize];
		GetPrivateProfileStringW(NULL, NULL, L"", lpReturnedBuffer, lpszReturnBufferSize, filePath);

		wchar_t * nextSection = lpReturnedBuffer;

		while (*nextSection != 0x00) {
			sectionList->Add(gcnew String(nextSection));
			nextSection = nextSection + wcslen(nextSection) + 1;
		}
		delete[] filePath;
		filePath = NULL;
		nextSection = NULL;
		delete lpReturnedBuffer;
		lpReturnedBuffer = NULL;
	}
	return;
}

bool IniEditor::getSectionKeys(String^ section, List<String^>^ keyList) {
	//valid section boolean
	bool valid = false;
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName) && this->isValidSection(section)) {
		valid = true;
		//clear the section keys list
		keyList->Clear();

		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(this->lpFileName);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * filePath = new wchar_t[origsize2];
		wcscpy_s(filePath, origsize2, wch2);

		LPTSTR lpReturnedBuffer = new wchar_t[lpszReturnBufferSize];
		GetPrivateProfileStringW(Section, NULL, L"", lpReturnedBuffer, lpszReturnBufferSize, filePath);

		wchar_t * nextSection = lpReturnedBuffer;

		while (*nextSection != 0x00) {
			keyList->Add(gcnew String(nextSection));
			nextSection = nextSection + wcslen(nextSection) + 1;
		}

		nextSection = NULL;
		delete[] lpReturnedBuffer;
		lpReturnedBuffer = NULL;
		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
	}
	return valid;
}

/*
DWORD WINAPI GetPrivateProfileSection(
_In_  LPCTSTR lpAppName,
_Out_ LPTSTR  lpReturnedString,
_In_  DWORD   nSize,
_In_  LPCTSTR lpFileName
);

lpAppName = section of ini
lpReturnedString = returned buffer of keys and values
nSize = size of return buffer
lpFileName = file name of ini file
*/
bool IniEditor::getSectionData(String^ section, List<String^>^ sectionDataList) {
	//valid section boolean
	bool valid = false;
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName) && this->isValidSection(section)) {
		valid = true;
		//clear the section data list
		sectionDataList->Clear();

		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(this->lpFileName);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * filePath = new wchar_t[origsize2];
		wcscpy_s(filePath, origsize2, wch2);

		LPTSTR lpReturnedBuffer = new wchar_t[lpszReturnBufferSize];
		GetPrivateProfileSectionW(Section, lpReturnedBuffer, lpszReturnBufferSize, filePath);
		
		wchar_t * nextSection = lpReturnedBuffer;

		while (*nextSection != 0x00) {
			sectionDataList->Add(gcnew String(nextSection));
			nextSection = nextSection + wcslen(nextSection) + 1;
		}

		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
		nextSection = NULL;
		delete[] lpReturnedBuffer;
		lpReturnedBuffer = NULL;
	}
	return valid;
}

String^ IniEditor::getValue(String^ section, String^ key) {
	String^ value = "";
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName)) {
		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert key String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(key);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * Key = new wchar_t[origsize2];
		wcscpy_s(Key, origsize2, wch2);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch3 = PtrToStringChars(this->lpFileName);
		const size_t origsize3 = wcslen(wch3) + 1;
		wchar_t * filePath = new wchar_t[origsize3];
		wcscpy_s(filePath, origsize3, wch3);

		LPTSTR lpReturnedString = new wchar_t[lpszReturnBufferSize];
		GetPrivateProfileStringW(Section, Key, L"", lpReturnedString, lpszReturnBufferSize, filePath);
		if (wcslen(lpReturnedString) > 0)
			value = gcnew String(lpReturnedString);

		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
		delete[] Key;
		Key = NULL;
		delete[] lpReturnedString;
		lpReturnedString = NULL;
	}
	return value;
}

String^ IniEditor::getValue(String^ section, String^ key, String^ defaultValue) {
	String^ value = defaultValue;
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName)) {
		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert key String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(key);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * Key = new wchar_t[origsize2];
		wcscpy_s(Key, origsize2, wch2);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch3 = PtrToStringChars(this->lpFileName);
		const size_t origsize3 = wcslen(wch3) + 1;
		wchar_t * filePath = new wchar_t[origsize3];
		wcscpy_s(filePath, origsize3, wch3);

		LPTSTR lpReturnedString = new wchar_t[lpszReturnBufferSize];
		GetPrivateProfileStringW(Section, Key, L"", lpReturnedString, lpszReturnBufferSize, filePath);
		if (wcslen(lpReturnedString) > 0)
			value = gcnew String(lpReturnedString);

		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
		delete[] Key;
		Key = NULL;
		delete[] lpReturnedString;
		lpReturnedString = NULL;
	}
	return value;
}

/*
UINT WINAPI GetPrivateProfileInt(
_In_ LPCTSTR lpAppName,
_In_ LPCTSTR lpKeyName,
_In_ INT     nDefault,
_In_ LPCTSTR lpFileName
);

lpAppName = section of ini
lpKeyName = key of section
lpDefault = default return
lpFileName = file name of ini file
*/
int IniEditor::getInt(String^ section, String^ key, int defaultValue) {
	int value = defaultValue;
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName)) {
		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert key String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(key);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * Key = new wchar_t[origsize2];
		wcscpy_s(Key, origsize2, wch2);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch3 = PtrToStringChars(this->lpFileName);
		const size_t origsize3 = wcslen(wch3) + 1;
		wchar_t * filePath = new wchar_t[origsize3];
		wcscpy_s(filePath, origsize3, wch3);

		value = GetPrivateProfileInt(Section, Key, defaultValue, filePath);

		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
		delete[] Key;
		Key = NULL;
	}
	return value;
}

double IniEditor::getDouble(String^ section, String^ key, double defaultValue) {
	double value = defaultValue;
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName)) {
		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert key String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(key);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * Key = new wchar_t[origsize2];
		wcscpy_s(Key, origsize2, wch2);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch3 = PtrToStringChars(this->lpFileName);
		const size_t origsize3 = wcslen(wch3) + 1;
		wchar_t * filePath = new wchar_t[origsize3];
		wcscpy_s(filePath, origsize3, wch3);

		LPTSTR lpReturnedString = new wchar_t[lpszReturnBufferSize];
		GetPrivateProfileStringW(Section, Key, L"", lpReturnedString, lpszReturnBufferSize, filePath);
		if (wcslen(lpReturnedString) > 0)
			value = wcstod(lpReturnedString, NULL);

		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
		delete[] Key;
		Key = NULL;
		delete[] lpReturnedString;
		lpReturnedString = NULL;
	}
	return value;
}

bool IniEditor::getBoolean(String^ section, String^ key, bool defaultValue) {
	bool value = defaultValue;
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName)) {
		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert key String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(key);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * Key = new wchar_t[origsize2];
		wcscpy_s(Key, origsize2, wch2);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch3 = PtrToStringChars(this->lpFileName);
		const size_t origsize3 = wcslen(wch3) + 1;
		wchar_t * filePath = new wchar_t[origsize3];
		wcscpy_s(filePath, origsize3, wch3);

		LPTSTR lpReturnedString = new wchar_t[lpszReturnBufferSize];
		GetPrivateProfileStringW(Section, Key, L"", lpReturnedString, lpszReturnBufferSize, filePath);
		if (wcslen(lpReturnedString) > 0)
			value = (!wcscmp(lpReturnedString, L"true") || !wcscmp(lpReturnedString, L"TRUE") || !wcscmp(lpReturnedString, L"True"));

		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
		delete[] Key;
		Key = NULL;
		delete[] lpReturnedString;
		lpReturnedString = NULL;
	}
	return value;
}

bool IniEditor::isTrue(String^ section, String^ key) {
	bool value = false;
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName)) {
		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert key String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(key);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * Key = new wchar_t[origsize2];
		wcscpy_s(Key, origsize2, wch2);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch3 = PtrToStringChars(this->lpFileName);
		const size_t origsize3 = wcslen(wch3) + 1;
		wchar_t * filePath = new wchar_t[origsize3];
		wcscpy_s(filePath, origsize3, wch3);

		LPTSTR lpReturnedString = new wchar_t[lpszReturnBufferSize];
		GetPrivateProfileString(Section, Key, L"", lpReturnedString, lpszReturnBufferSize, filePath);
		value = (!wcscmp(lpReturnedString, L"true") || !wcscmp(lpReturnedString, L"TRUE") || !wcscmp(lpReturnedString, L"True"));

		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
		delete[] Key;
		Key = NULL;
		delete[] lpReturnedString;
		lpReturnedString = NULL;
	}
	return value;
}

/*
BOOL WINAPI WritePrivateProfileString(
_In_ LPCTSTR lpAppName,
_In_ LPCTSTR lpKeyName,
_In_ LPCTSTR lpString,
_In_ LPCTSTR lpFileName
);

lpAppName = section of ini
lpKeyName = key of section
lpString = a null-terminated string to save
lpFileName = file name of ini file
*/
void IniEditor::writeValue(String^ section, String^ key, String^ value) {
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName)) {
		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert key String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(key);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * Key = new wchar_t[origsize2];
		wcscpy_s(Key, origsize2, wch2);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch3 = PtrToStringChars(this->lpFileName);
		const size_t origsize3 = wcslen(wch3) + 1;
		wchar_t * filePath = new wchar_t[origsize3];
		wcscpy_s(filePath, origsize3, wch3);

		//Convert value String^ to wchar_t*
		pin_ptr<const wchar_t> wch4 = PtrToStringChars(value);
		const size_t origsize4 = wcslen(wch4) + 1;
		wchar_t * Value = new wchar_t[origsize4];
		wcscpy_s(Value, origsize4, wch4);

		WritePrivateProfileStringW(Section, Key, Value, filePath);

		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
		delete[] Key;
		Key = NULL;
		delete[] Value;
		Value = NULL;
	}
}

void IniEditor::writeValue(String^ section, String^ key, int value) {
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName)) {
		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert key String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(key);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * Key = new wchar_t[origsize2];
		wcscpy_s(Key, origsize2, wch2);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch3 = PtrToStringChars(this->lpFileName);
		const size_t origsize3 = wcslen(wch3) + 1;
		wchar_t * filePath = new wchar_t[origsize3];
		wcscpy_s(filePath, origsize3, wch3);

		//convert 'value' to wchar_t*
		pin_ptr<const wchar_t> wch4 = PtrToStringChars(System::Convert::ToString(value));
		const size_t origsize4 = wcslen(wch4) + 1;
		wchar_t * Value = new wchar_t[origsize4];
		wcscpy_s(Value, origsize4, wch4);

		WritePrivateProfileStringW(Section, Key, Value, filePath);

		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
		delete[] Key;
		Key = NULL;
		delete[] Value;
		Value = NULL;
	}
}

void IniEditor::writeValue(String^ section, String^ key, double value) {
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName)) {
		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert key String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(key);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * Key = new wchar_t[origsize2];
		wcscpy_s(Key, origsize2, wch2);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch3 = PtrToStringChars(this->lpFileName);
		const size_t origsize3 = wcslen(wch3) + 1;
		wchar_t * filePath = new wchar_t[origsize3];
		wcscpy_s(filePath, origsize3, wch3);

		//convert 'value' to wchar_t*
		pin_ptr<const wchar_t> wch4 = PtrToStringChars(System::Convert::ToString(value));
		const size_t origsize4 = wcslen(wch4) + 1;
		wchar_t * Value = new wchar_t[origsize4];
		wcscpy_s(Value, origsize4, wch4);

		WritePrivateProfileStringW(Section, Key, Value, filePath);

		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
		delete[] Key;
		Key = NULL;
		delete[] Value;
		Value = NULL;
	}
}

void IniEditor::writeValue(String^ section, String^ key, bool value) {
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName)) {
		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert key String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(key);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * Key = new wchar_t[origsize2];
		wcscpy_s(Key, origsize2, wch2);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch3 = PtrToStringChars(this->lpFileName);
		const size_t origsize3 = wcslen(wch3) + 1;
		wchar_t * filePath = new wchar_t[origsize3];
		wcscpy_s(filePath, origsize3, wch3);

		WritePrivateProfileStringW(Section, Key, (value ? L"true" : L"false"), filePath);

		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
		delete[] Key;
		Key = NULL;
	}
}

/*
BOOL WINAPI WritePrivateProfileStruct(
_In_ LPCTSTR lpszSection,
_In_ LPCTSTR lpszKey,
_In_ LPVOID  lpStruct,
_In_ UINT    uSizeStruct,
_In_ LPCTSTR szFile
);

lpszSection = section of ini
lpszKey = key of section. If this parameter is NULL, the entire section, including all keys and entries within the section, is deleted.
lpStruct = The data to be copied. If this parameter is NULL, the key is deleted.
uSizeStruct = The size of the buffer pointed to by the lpStruct parameter, in bytes.
szFile = file name of ini file
*/

void IniEditor::deleteSection(String^ section) {
	//Convert section String^ to wchar_t*
	pin_ptr<const wchar_t> wch = PtrToStringChars(section);
	const size_t origsize = wcslen(wch) + 1;
	wchar_t * Section = new wchar_t[origsize];
	wcscpy_s(Section, origsize, wch);

	//Convert this->lpFileName String^ to wchar_t*
	pin_ptr<const wchar_t> wch2 = PtrToStringChars(this->lpFileName);
	const size_t origsize2 = wcslen(wch2) + 1;
	wchar_t * filePath = new wchar_t[origsize2];
	wcscpy_s(filePath, origsize2, wch2);

	WritePrivateProfileStructW(Section, NULL, NULL, 0, filePath);

	delete[] Section;
	Section = NULL;
	delete[] filePath;
	filePath = NULL;
}

void IniEditor::deleteKey(String^ section, String^ key) {
	//check if there is a file name stored
	if (!String::IsNullOrEmpty(this->lpFileName)) {
		//Convert section String^ to wchar_t*
		pin_ptr<const wchar_t> wch = PtrToStringChars(section);
		const size_t origsize = wcslen(wch) + 1;
		wchar_t * Section = new wchar_t[origsize];
		wcscpy_s(Section, origsize, wch);

		//Convert key String^ to wchar_t*
		pin_ptr<const wchar_t> wch2 = PtrToStringChars(key);
		const size_t origsize2 = wcslen(wch2) + 1;
		wchar_t * Key = new wchar_t[origsize2];
		wcscpy_s(Key, origsize2, wch2);

		//Convert this->lpFileName String^ to wchar_t*
		pin_ptr<const wchar_t> wch3 = PtrToStringChars(this->lpFileName);
		const size_t origsize3 = wcslen(wch3) + 1;
		wchar_t * filePath = new wchar_t[origsize3];
		wcscpy_s(filePath, origsize3, wch3);

		WritePrivateProfileStructW(Section, Key, NULL, 0, filePath);

		delete[] Section;
		Section = NULL;
		delete[] filePath;
		filePath = NULL;
		delete[] Key;
		Key = NULL;
	}
}
