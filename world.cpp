#include "stdafx.h"
#include "world.h"
#include "quaternion.h"

World::World()
{
	temp_camera = nullptr;
}

void World::frame(Camera* camera)
{
	camera->generateMatrix();

	(*mesh)[0].rotate(math::Quaternion().fromAxisRotation(math::vec3(0,1,0),0.008f));

	m_renderList.draw(camera);
}

bool World::initialise()
{
	DirectionalLight* sun = new DirectionalLight();
	sun->intensity = 5;
	sun->colour = math::vec3(1.f, 1.f, 1.f);
	sun->vector = math::vec3(0.f, 0.4f, 0.5f);

	m_lights.push_back(sun);

	initialiseObjects();

	return true;
}


bool World::initialiseObjects()
{
	temp_camera = new Camera(math::vec3(0, 0, 5));
	if (!temp_camera)
		return false;


	if (!mesh->load("Game/Models/building.obj", Enum::GPU))
		return false;

	Texture* marble = new Texture();
	if (!marble->load("Game/Textures/building.dds", Enum::GPU))
		return false;

	mesh->createInstance(Transformable(), *marble);
	(*mesh)[0].setScale(0.4f);
	m_renderList.addObject3D(mesh);

	return true;
}

void World::shutdown()
{
	for (Light* l : m_lights)
		delete l;

	if (temp_camera)
		delete temp_camera;

}

Camera* World::getCamera()
{
	return temp_camera;
}