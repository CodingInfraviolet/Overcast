#include "stdafx.h"


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <string>

#include "System.h"
#include "Console.h"



int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, int)
{
	System* system = nullptr;
	system = System::createInstance();
	if (!system) return 1;

	Console console;
	console.enable();

	if (!system->initialise()) return 1;

	system->run();

	system->shutdown();
	delete system;

	console.disable();

	return 0;
}