#include "stdafx.h"
#include "Graphics.h"
#include "System.h"
#include "OpenGLClass.h"
#include "guitext.h"

Graphics::Graphics()
{
	openglclass = nullptr;
	guitext = nullptr;
}

Graphics::Graphics(const Graphics&)
{

}

Graphics* Graphics::createInstance()
{
	static bool exists = false;

	if (!exists)
	{
		exists = true;
		return new Graphics();
	}
	else
	{
		Error("Can not create multiple instances of System.");
		return nullptr;
	}
}

bool Graphics::initialise()
{
	openglclass = new OpenGLClass();
	guitext = new GuiText();
	if (openglclass == nullptr || guitext == nullptr)			return false;
	if (!openglclass->initialise() || !guitext->initialise())	return false;
	initialiseScreenQuad();
	
	return true;
}

void Graphics::shutdown()
{
	if (openglclass)
	{
		openglclass->shutdown();
		delete openglclass;
	}
	if (guitext)
	{
		guitext->shutdown();
		delete guitext;
	}
}

void Graphics::beginScene()
{
	openglclass->beginScene();
}

void Graphics::endScene()
{
	openglclass->lightPass(systemptr->gamestate.m_world->m_lights);
	guiPass();
	openglclass->present();
	openglclass->clear(true, true, true);
}

void Graphics::resize(int width, int height, GameState* state)
{
	systemptr->displaySet.screenWidth = width;
	systemptr->displaySet.screenHeight = height;

	state->updateProjectionMatrixAspect(float(width), float(height),
		systemptr->cameraSet.fov, systemptr->cameraSet.cameraZNear, systemptr->cameraSet.cameraZFar);
	
	openglclass->resize(width, height);
}

void Graphics::prepareGeomPass()
{
	openglclass->prepareGeomPass();
}

void Graphics::prepareShadowPass()
{
	openglclass->prepareShadowPass();
}

void Graphics::guiPass()
{
	guitext->draw();
}

void Graphics::initialiseScreenQuad()
{
	screenQuad.quad[0] = Vertex2D(-1.f, -1.f, 0.f, 0.f);
	screenQuad.quad[1] = Vertex2D(1.f, -1.f, 1.f, 0.f);
	screenQuad.quad[2] = Vertex2D(-1.f, 1.f, 0.f, 1.f);
	screenQuad.quad[3] = Vertex2D(-1.f, 1.f, 0.f, 1.f),
		screenQuad.quad[4] = Vertex2D(1.f, -1.f, 1.f, 0.f);
	screenQuad.quad[5] = Vertex2D(1.f, 1.f, 1.f, 1.f);

	screenQuad.VAO = ~0u;
	screenQuad.VBO = ~0u;
	openglclass->initialiseScreenQuad(screenQuad.quad, screenQuad.VBO, screenQuad.VAO);
}
