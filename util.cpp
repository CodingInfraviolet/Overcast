#include "stdafx.h"
#include "util.h"
void toLowerCase(std::string & text)
{
	for (unsigned i = 0; i < text.length(); i++)
		text[i] = (char)tolower(text[i]);
}

void toUpperCase(std::string & text)
{
	for (unsigned i = 0; i < text.length(); i++)
		text[i] = (char)toupper(text[i]);
}

std::string toString(long t)
{
	std::ostringstream stream;
	stream << t;
	return std::string(stream.str());
}

std::string getNameFromDirectory(const std::string& dir)
{
	return std::string(
		std::find_if(dir.rbegin(), dir.rend(), [](char c) {return c == '\\' || c == '/'; }).base(),
		dir.end());
}

wchar_t charToWchar(unsigned char c)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(c)[0];
}