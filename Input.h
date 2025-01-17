#pragma once
#include <vector>

class System;

/**Handles keyboard and mouse input.*/
class Input
{
private:
	/**Basic constructor..*/
	Input();

	/**Disabled copy constructor.*/
	Input(const Input&);
	
public:
	/**Creates an instance of the class using the singleton design pattern.*/
	static Input* createInstance();

	/**Initialises input functionality.*/
	bool initialise();

	/**Shuts down input functionality.*/
	void shutdown();

	/**Returns true if a key is being pressed down.*/
	bool onKeyDown(WPARAM key);

	/**Returns true if a key is not being pressed down.*/
	bool onKeyUp(WPARAM key);

	/**Processes potential inputs.*/
	void frame(MSG& msg);

	/**Returns the relative mouse position in the range [-1,1].*/
	math::vec2 getMousePos();

	/**Returns the delta mouse between two frames.*/
	math::vec2 getMouseMovement();

	/**A struct containing various key codes.*/
	struct Code
	{
		enum Key
		{
			MouseLeft = 0x01,   MouseRight = 0x02,   MouseMiddle = 0x04,
			Backspace = 0x08,   Tab = 0x09,		     Clear = 0x0C,
			Enter = 0x0D,       Shift = 0x10,		 Ctrl = 0x11,
			Menu = 0x12,	    Pause = 0x13,		 CapsLock = 0x14,
			Esc = 0x1B,		    Space = 0x20,		 PgUp = 0x21,
			PgDown = 0x22,	    End = 0x23,		     Home = 0x24,
			Left = 0x25,	    Right = 0x27,		 Up = 0x28,
			Down = 0x29,	    Select = 0x29,	     Print = 0x2A,
			PrintScreen = 0x2C, Insert = 0x2D,	     Delete = 0x2E,
			Help = 0x2F,	    Zero = 0x30,	     One = 0x31,
			Two = 0x32,			Three = 0x33,		 Four = 0x34,
			Five = 0x35,		Six = 0x36,			 Seven = 0x37,
			Eight = 0x38,		Nine = 0x39,		 A = 0x41,
			B = 0x42,			C = 0x43,			 D = 0x44,
			E = 0x45,			F = 0x46,			 G = 0x47,
			H = 0x48,			I = 0x49,			 J = 0x4A,
			K = 0x4B,			L = 0x4C,			 M = 0x4D,
			N = 0x4E,			O = 0x4F,			 P = 0x50,
			Q = 0x51,			R = 0x52,			 S = 0x53,
			T = 0x54,			U = 0x55,			 V = 0x56,
			W = 0x57,			X = 0x58,			 Y = 0x59,
			Z = 0x5A,			LeftWindows = 0x5B,  RightWindows = 0x5C,
			Applications = 0x5D,Sleep = 0x5F,	     KeypadZero = 0x60,
			KeypadOne = 0x61,	KeypadTwo = 0x62,	 KeypadThree = 0x63,
			KeypadFour = 0x64,	KeypadFive = 0x65,	 KeypadSix = 0x66,
			KeypadSeven = 0x67, KeypadEight = 0x68, KeypadNine = 0x69,
			Multiply = 0x6A,	Add = 0x6B,			 Separator = 0x6C,
			Subtract = 0x6D,	Decimal = 0x6E,		 Divide = 0x6F,
			F1 = 0x70,			F2 = 0x71,			 F3 = 0x72,
			F4 = 0x73,			F5 = 0x74,			 F6 = 0x75,
			F7 = 0x76,			F8 = 0x77,			 F9 = 0x78,
			F10 = 0x79,			F11 = 0x7A,			 F12 = 0x7B,
			F13 = 0x7C,			F14 = 0x7D,			 F15 = 0x7E,
			F16 = 0x7F,			F17 = 0x80,			 F18 = 0x81,
			F19 = 0x82,			F20 = 0x83,			 F21 = 0x84,
			F22 = 0x85,			F23 = 0x86,			 F24 = 0x87,
			NumLock = 0x90,		ScrollLock = 0x91,	 ShiftLeft = 0xA0,
			ShiftRight = 0xA1,  CtrlLeft = 0xA2,	 CtrlRight = 0xA3,
			MenuLeft = 0xA4,	MenuRight = 0xA5,	 VolumeMute = 0xAD,
			VolumeDown = 0xAE,	VolumeUp = 0xAF,
		};
	};

private:
	std::vector<bool> keys;
	int deltaMouseX, deltaMouseY;
};