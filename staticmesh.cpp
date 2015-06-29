#include "stdafx.h"
#include "staticmesh.h"
#include "camera.h"
#include "ShaderProgram.h"
#include "world.h"
#include "System.h"
#include "Graphics.h"

void StaticMesh::draw(Camera* camera)
{
	m_apiData.prepareForDrawing();
	assert(m_inGPU && (m_instanceTransforms.size() == m_appliedTextures.size()));

	for (unsigned i = 0; i < m_instanceTransforms.size(); ++i)
	{
		if (m_instanceTransforms[i].pendingUpdate())
			m_instanceTransforms[i].forceMatrixUpdate();

		//if (Graphics::viewFrustrumCheck(MVP, m_centrePoint, m_radius))
		{
			systemptr->graphics->prepareGeomPass();
		
			s_geometryShader->setModelMatrix(m_instanceTransforms[i].matrix()); 
			s_geometryShader->setMVP(camera->projection() * camera->matrix() * m_instanceTransforms[i].matrix());
			s_geometryShader->setModelViewMatrix(camera->matrix() * m_instanceTransforms[i].matrix());
			m_appliedTextures[i].bindForGPU();

			GraphicsInterface::drawIndexedMeshWithState(m_indexCount);

			//Draw for shadows:
			systemptr->graphics->prepareShadowPass();

			for (Light*& l : systemptr->gamestate.m_world->m_lights)
			{
				LightShadowInfo* shadowInfo = l->getShadowInfo();
				if (shadowInfo)
				{
					switch (l->type())
					{
					case Enum::LIGHT_DIRECTIONAL:
					{
						DirectionalLight* light = (DirectionalLight*)l;
						Camera lightCam;
						lightCam.initOrthoProjectionMatrix(-90, 90, -90, 90, -90, 90);

						s_shadowShader->setMVP(lightCam.projection() * m_instanceTransforms[i].matrix());

						GraphicsInterface::drawIndexedMeshWithState(m_indexCount);
						break;
					}
					
					}
				}
			}
		}
	}
}

void StaticMesh::createInstance(const Transformable& position, const Texture& texture)
{
	m_instanceTransforms.push_back(position);
	m_appliedTextures.push_back(texture);
}