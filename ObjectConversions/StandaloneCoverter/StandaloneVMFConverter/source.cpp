#include <iostream>
#include <string>
#include "modelfilesystem.h"
#include <Windows.h>
#include <codecvt>
#include <locale>
#include <Pathcch.h>

#pragma comment (lib, "Pathcch.lib")

#define SUBPATH_NAME "processed"
#define LSUBPATH_NAME L"processed"
#define LSUBPATH_NAME_SLASH L"processed/"

using namespace std;

string getPathWithOtherExtension(const string& path, const string& desiredExtension)
{
	size_t iperiod = path.rfind('.');
	if (iperiod == std::string::npos)
		return path + desiredExtension;
	else
		return path.substr(0, iperiod) + desiredExtension;
}

wstring removeLast(const std::string& element)
{
	std::wstring_convert< std::codecvt_utf8_utf16<wchar_t>> converter;
	
	size_t slashLoc = max(min(element.rfind('/'),std::string::npos), min(element.rfind('\\'), std::string::npos));

	size_t loc1 = element.rfind('\\');
	size_t loc2 = element.rfind('/');

	if (loc1 == string::npos)
		if (loc2 == string::npos)
			return wstring();
		else
			slashLoc = loc2;
	else
		if (loc2 == string::npos)
			slashLoc = loc1;
		else
			slashLoc = max(loc1, loc2);

	return converter.from_bytes(element.substr(0,slashLoc+1));
}

string insertSubpath(const string& path)
{
	std::wstring_convert< std::codecvt_utf8_utf16<wchar_t>> converter;

	wstring dir = removeLast(path);
	size_t dirLen = dir.size();
	dir += LSUBPATH_NAME_SLASH;
	wstring fileName = converter.from_bytes(path.substr(dirLen, path.size() - dirLen + 1));
	return converter.to_bytes(dir + fileName);
}

bool createDirectory(const std::string& programPath)
{
	//Get program directory:
	wstring Dir = removeLast(programPath);

	if (!CreateDirectory((Dir + LSUBPATH_NAME).c_str(), NULL))
	{
		DWORD error = GetLastError();
		if (error == ERROR_ALREADY_EXISTS)
			return true; //No need to create
		else
		{
			std::cout << "Error creating subpath!\n";
			return false;
		}
	}
	else
		return true;
}

int main(int argc, char** argv)
{
	if (argc < 2)
		std::cout << "Invalid arguments!\n";
	else
	{
		if(!createDirectory(argv[0]))
			return 1;

		for (int i = 1; i < argc; ++i)
		{
			string model = argv[i];
			if (!FileSystem::processModel(model.c_str(), insertSubpath(getPathWithOtherExtension(model, ".vmf")).c_str()))
				return 2;
		}
		
		std::cout << "Done!\n";
	}


	cin.get();
}