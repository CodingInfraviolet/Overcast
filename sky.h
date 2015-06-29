#pragma once
#include "mesh.h"

class Sky : public Mesh
{
public:
	/**Overrides the virtual draw() method, implementing sky drawing functionality.*/
	void draw(Camera* camera) override;
};