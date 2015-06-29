#include "stdafx.h"
#include "OpenGLClass.h"
#include "System.h"
#include "sky.h"
#include "drawable.h"
#include "camera.h"
#include "Graphics.h"


void OpenGLClass::present()
{
	SwapBuffers(m_hdc);
}

void OpenGLClass::renderSky(Camera* camera, SkyShader* skyShader)
{
	skyShader->set();
	m_skyTexture.bindForGPU();

	math::mat4 MVP = camera->projection()*camera->matrix();
	skyShader->setMVP(MVP.m[0][0]);
	m_sky.draw(camera);
}

void OpenGLClass::shutdown()
{
	shadowBuffer.shutdown();
	wglMakeCurrent(NULL, NULL);
	shutdownContext();
}

void OpenGLClass::shutdownContext()
{
	if (m_hrc)
		wglDeleteContext(m_hrc);
	if (m_hdc)
		ReleaseDC(systemptr->hwnd(), m_hdc);
}

void OpenGLClass::resize(int width, int height)
{
	glViewport(0, 0, width, height);
	gbuffer.resize(width, height);
}

void OpenGLClass::clearColour(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void OpenGLClass::clear(bool colour, bool depth, bool stencil)
{
	glClear((colour ? GL_COLOR_BUFFER_BIT:0) | (depth ? GL_DEPTH_BUFFER_BIT:0) | (stencil ? GL_STENCIL_BUFFER_BIT:0));
}

void OpenGLClass::lightPass(const std::vector<Light*>& dlights)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	gbuffer.bindForReading();

	renderDirectionalLights(dlights, *systemptr->gamestate.m_mainCamera);
}

void OpenGLClass::renderDirectionalLights(const std::vector<Light*>& lights, Camera& camera)
{
	Shaders.directionalShader.set();
	Shaders.directionalShader.setViewMatrix(camera.matrix());
	glActiveTexture(GL_TEXTURE3);GLERROR
	shadowBuffer.m_texture.bindForGPU(); 
		glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(systemptr->graphics->screenQuad.VAO);

	for (const Light* const & l : lights)
	{
		if (l->type() == Enum::LIGHT_DIRECTIONAL)
		{
			Camera lightCam;
			lightCam.initOrthoProjectionMatrix(-90, 90, -90, 90, -90, 90);
			Shaders.directionalShader.setLightMatrix(lightCam.projection()*lightCam.matrix());
			Shaders.directionalShader.setLight((DirectionalLight*)l, systemptr->gamestate.m_mainCamera->matrix());
			
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
}