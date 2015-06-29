#include "stdafx.h"
#include "System.h"
#include "SettingClasses.h"
#include "Input.h"
#include "Graphics.h"
#include "camera.h"
#include "rand.h"
#include "miscUtilFunction.h"


System* systemptr = nullptr;


System::System()
{
	systemptr = this;
	graphics = nullptr;
	input = nullptr;
	m_initialised = false;
	
}
System::System(const System&)
{
	systemptr = nullptr;
}

bool System::initialise()
{
	FileSystem::CommenceModelFileSystem();

	FileSystem::IniParser  gameParser;
	gameParser.parseFile("Game/gameconfig.ini");

	displaySet.attachParser(&gameParser, "DISPLAY");
	displaySet.initialise();

	cameraSet.attachParser(&gameParser, "CAMERA");
	cameraSet.initialise();

	input = Input::createInstance();
	if (!input)
		return false;

	graphics = Graphics::createInstance();
	if (!graphics)
		return false;

	Rand::initialise(1);

	initialiseWindows();
	
	if (!input->initialise())
		return false;

	if (!graphics->initialise())
		return false;

	gamestate.initialise();

	if (!miscDevUtilOperations())
		return false;

	m_initialised = true;

	return true;
}

void System::shutdown()
{
	m_initialised = false;

	gamestate.shutdown();

	if (graphics)
	{
		graphics->shutdown();
		delete graphics;
	}

	if (input)
	{
		input->shutdown();
		delete input;
	}

	shutdownWindows();
}

void System::run()
{
	MSG msg;
	m_running = true;

	while (m_running)
	{
		while (PeekMessage(&msg, m_hwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);


			if (msg.message == WM_INPUT)
				input->frame(msg);
		}


		switch (msg.message)
		{
		case WM_QUIT:
			exit();
			break;
		default:
			frame();
			break;
		}
	}
}

void System::exit()
{
	m_running = false;
}

void System::frame()
{
	graphics->beginScene();
		handleInput(gamestate.m_mainCamera);
		gamestate.frame();
		graphics->endScene();

#ifdef _DEBUG
	GLERROR;
#endif
}

void System::handleInput(Camera* camera)
{
	if (input->onKeyDown(Input::Code::Esc))
		exit();

	static float speed = 1.f;

	if (input->onKeyDown(Input::Code::W))
		camera->flyForwards(input->onKeyDown(Input::Code::Shift) ? speed * 2 : speed);
	if (input->onKeyDown(Input::Code::S))
		camera->flyBackwards(input->onKeyDown(Input::Code::Shift) ? speed * 2 : speed);
	if (input->onKeyDown(Input::Code::D))
		camera->flyRight(input->onKeyDown(Input::Code::Shift) ? speed * 2 : speed);
	if (input->onKeyDown(Input::Code::A))
		camera->flyLeft(input->onKeyDown(Input::Code::Shift) ? speed * 2 : speed);
	if (input->onKeyDown(Input::Code::Q))
		camera->flyDown(input->onKeyDown(Input::Code::Shift) ? speed * 2 : speed);
	if (input->onKeyDown(Input::Code::E))
		camera->flyUp(input->onKeyDown(Input::Code::Shift) ? speed * 2 : speed);
	if (input->onKeyDown(Input::Code::C))
	{
		{
			camera->reset();
			camera->setPos(16.7f, -2.8f, 0.97f);
			camera->lookLeft(1.56f);
			camera->lookUp(0.2f);
		}
	}

	if (input->onKeyDown(0x52))
		camera->setPos(0, 0, 5);

	math::vec2 deltaMouseMovement = input->getMouseMovement()*0.01f;
	camera->lookDown(deltaMouseMovement.y);
	camera->lookRight(deltaMouseMovement.x);
}

LRESULT CALLBACK System::WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_SIZE:
	{
		if (systemptr->initialised())
		{
			RECT rect;
			GetWindowRect(hwnd, &rect);
			int newWidth = rect.right - rect.left;
			int newHeight = rect.bottom - rect.top;

			systemptr->graphics->resize(newWidth, newHeight, &systemptr->gamestate);
		}

		return 0;
	}
	default:
	{
		return DefWindowProc(hwnd, message, wparam, lparam);
	}
	}
}

System* System::createInstance()
{
	static bool exists = false;

	if (!exists)
	{
		exists = true;
		return new System();
	}
	else
	{
		ErrorSafe("Can not create multiple instances of System.");
		return nullptr;
	}
}

void System::initialiseWindows()
{
	WNDCLASSEX wc;
	int posX, posY;

	m_hInstance = GetModuleHandle(NULL);
	m_applicationName = L"Overcast";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = System::WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	if (displaySet.fullscreen)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		DEVMODE dmScreenSettings = { 0 };
		displaySet.screenWidth = GetSystemMetrics(SM_CXSCREEN);
		displaySet.screenHeight = GetSystemMetrics(SM_CYSCREEN);

		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		posX = posY = 0;
	}
	else
	{
		posX = GetSystemMetrics(SM_CXSCREEN) - displaySet.screenWidth;
		posY = GetSystemMetrics(SM_CYSCREEN) - displaySet.screenHeight;
	}

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		(displaySet.fullscreen ? (WS_EX_TOPMOST | WS_POPUP) : (WS_OVERLAPPEDWINDOW | WS_CAPTION)),
		posX, posY, displaySet.screenWidth, displaySet.screenHeight, NULL, NULL, m_hInstance, NULL);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	ShowCursor(false);
}

void System::shutdownWindows()
{
	if (displaySet.fullscreen)
		ChangeDisplaySettings(NULL, 0);

	DestroyWindow(m_hwnd);
	m_hwnd = nullptr;
	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = nullptr;
}

bool System::initialised()
{
	return m_initialised;
}