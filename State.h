#pragma once
#include "SettingClasses.h"
#include "world.h"
class Camera;

/**A class responsible for keeping and maintaining important game information.*/
class GameState
{
private:

public:

	Camera* m_mainCamera;
	World* m_world;

	/**Initialises variables to zero.*/
	GameState();

	struct {
		math::vec3 lightVector;
		math::vec3  lightColour;
		math::vec3  ambientColour;
	} Environment;

	void frame()
	{
		m_world->frame(m_mainCamera);
	}

	/**Initialises the GameState system.*/
	bool initialise();

	/**Shuts down the GameState system.*/
	void shutdown();

	/**
	Updates the camera matrices upon screen resize. Note, will need fixing for multiple cameras.
	@param width The screen width.
	@param height The screen height.
	*/
	void updateProjectionMatrixAspect(float width, float height, float fov, float znear, float zfar)
	{
		m_mainCamera->initPerspectiveProjectionMatrix(width, height, fov, znear, zfar);
	}
};