#pragma once
#include "drawable.h"

/**A class to act as a set of objects to be drawn. Each object inserted only once.*/
class RenderList
{
	std::set<Drawable*> m_objects;
public:
	
	/**Adds an object to the list.*/
	void addObject3D(Drawable* obj)
	{
		m_objects.insert(obj);
	}

	/**Draws all of the objects in the list.*/
	void draw(Camera* camera)
	{
		for (Drawable* draw : m_objects)
			draw->draw(camera);
	}
};