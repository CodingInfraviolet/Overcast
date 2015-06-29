#pragma once
#include "light.h"
#include "camera.h"
#include "Texture.h"
#include "RenderList.h"
#include "transformable.h"
#include "staticmesh.h"

/**A class representing the game world.*/
class World
{
public:

	RenderList m_renderList;
	std::vector<Light*> m_lights;
	Camera* temp_camera;
	StaticMesh* mesh = new StaticMesh();

	struct
	{
		math::vec3 ambientColour = math::vec3(0.05f, 0.025f, 0.01f);
	} EnvironmentVariables;

	/**Initialises variables to zero.*/
	World();

	/**Performs object logic and renders everything in the world, updating the camera matrix first.*/
	void frame(Camera* camera);

	/**Initialises the basic game world.*/
	bool initialise();

	bool initialiseObjects();

	/**Destroys the basic game world.*/
	void shutdown();

	/**Returns the main camera.*/
	Camera* getCamera();
};