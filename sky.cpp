#include "stdafx.h"
#include "camera.h"
#include "sky.h"
#include "graphicsinterface.h"

void Sky::draw(Camera* camera)
{
	camera->flyDown(0.f); //Use camera parameter later (this only silences the warning)
	m_apiData.prepareForDrawing();
	GraphicsInterface::drawIndexedMeshWithState(m_indexCount);
}