#include "stdafx.h"
#include "SettingClasses.h"
#include "State.h"

namespace Vars
{
	void CameraSettings::initialise()
	{
		fov = initialiseVar("Fov", 50.f);
		nearClipPlane = initialiseVar("NearClipPlane", 0.1f);
		farClipPlane = initialiseVar("FarClipPlane", 400.0f);
		cameraSpeed = initialiseVar("Speed", 0.5f);
		cameraRotationMultiplier = initialiseVar("RotationMultiplier", 2.0f);
		cameraMaxLookUp = initialiseVar("MaxLoopUp", 85.f);
		cameraMaxLookDown = initialiseVar("MaxLoopDown", -85.f);
		cameraZNear = initialiseVar("znear", 0.01f);
		cameraZFar = initialiseVar("zfar", 500.f);
		mouseResetOffset = initialiseVar("MouseResetOffset", 35);
	}


	void DisplaySettings::initialise()
	{
		screenWidth = initialiseVar("ScreenWidth", 800);
		screenHeight = initialiseVar("ScreenHeight", 600);
		vsync = initialiseVar("vsync", false);
		fullscreen = initialiseVar("fullscreen", false);
	}
}