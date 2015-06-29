#pragma once
#include "util.h"

/**Pops up an error message to the screen.*/
void Error(std::string err);

/**Pops up an warning message to the screen.*/
void Warning(std::string err);

/**Prints an information message.*/
void Inform(std::string err);

/**Prints an error message without crashing if no window functionality.*/
void ErrorSafe(std::string err); //does not require window to be open

/*Pops up a window with a GL error, if one exists. For debugging only.*/
#define GLERROR {unsigned err = glGetError(); if (err!=0) {Error(string("GL Error ") + toString(err) + " at line " + toString(__LINE__) +"\n" + __FILE__ + "\n" + (char*)gluErrorString(err));}}