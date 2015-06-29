#pragma once

/**Converts a string to lower case.*/
void toLowerCase(std::string & text);

/**Converts a string to upper case.*/
void toUpperCase(std::string & text);

/**Converts a long to a string.*/
std::string toString(long t);

/**Returns the name of a file from a directory string.*/
std::string getNameFromDirectory(const std::string& dir);

/**Clamps a value into a given range.*/
template <class T> T clamp(T x, T min, T max)
{
	return (x < min ? min:(x>max ? max:x));
}

wchar_t charToWchar(unsigned char c);