#pragma once
#include "settings.h"

class State;

namespace Vars
{
	/**A class to contain various camera settings.*/
	class CameraSettings : public Settings
	{
	public:
		friend class State;

		float fov;
		float nearClipPlane;
		float farClipPlane;
		float cameraSpeed;
		float cameraRotationMultiplier;
		float cameraMaxLookUp;
		float cameraMaxLookDown;
		float cameraZNear;
		float cameraZFar;
		int mouseResetOffset;

		/**Initialises the variables from file.*/
		void initialise() override;
	};

	/**A class for containing various display settings.*/
	class DisplaySettings : public Settings
	{
	public:
		friend class State;

		int screenWidth;
		int screenHeight;
		bool vsync;
		bool fullscreen;

		/**Initialises the variables from file.*/
		void initialise() override;
	};
}