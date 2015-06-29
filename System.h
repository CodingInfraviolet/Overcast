#pragma once
#include "State.h"

class Input;
class Graphics;

/**The main system class that takes over after Main and manages the program.*/
class System
{
private:
	/**Initialises varaibles to zero.*/
	System();

	/**Disabled copy constructor.*/
	System(const System&);
public:

	/**Creates an instance of the class in accordance with the singleton pattern.*/
	static System* createInstance();

	/**Does vital system setup.*/
	bool initialise();

	/**Shuts down the system at the end of execution.*/
	void shutdown();

	/**Runs the main loop, helping event management and then calling frame().*/
	void run();

	/**Signals that the program is to be quit. This does not happen immediately.*/
	void exit();

	/**Returns true if the system is initialised and ready to perform.*/
	bool initialised();

	/**Returns the main window handle.*/
	HWND hwnd() { return m_hwnd; }

	/**Returns the HINSTANCE of the program.*/
	HINSTANCE windowInstance() { return m_hInstance; }

	Vars::DisplaySettings displaySet;
	Vars::CameraSettings cameraSet;

	Input* input;
	Graphics* graphics;

	GameState gamestate;

private:

	/**Serves as a frame to manage the majority of the game loop.*/
	void frame();

	/**Handles user input in accordance with game requirments.*/
	void handleInput(Camera* camera);

	/**Initialises the Window using the WINAPI.*/
	void initialiseWindows();

	/**Shuts down the Windows components that have been invoked through WINAPI.*/
	void shutdownWindows();

	LPCWSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hwnd;

	bool m_running;
	bool m_initialised;

	/**The WndProc callback called by the WINAPI.*/
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
};

extern System* systemptr;