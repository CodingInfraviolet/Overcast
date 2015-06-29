#pragma once
#include "Vertex.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "RenderList.h"
#include "sky.h"
#include "gbuffer.h"
#include "light.h"
#include "shadowbuffer.h"

#define PIXELFORMATPATH "Engine/pixelformat.bin"

/**
A class designed to encapsulate much of the opengl-specific functionality that is directly interwoven into the rendering pipeline.
*/
class OpenGLClass
{
public:
	/**Initialises internal variables to zero.*/
	OpenGLClass();

	/**
	Initialises much of the rendering system, including the context, shaders and important systems.
	@param reset Indicates whether the pixel format should be recreated instead of loaded.
			Must be done at least once, but introduce startup delay.
	@return The success state of the operation.
	*/
	bool initialise(bool reset = false);

	/**Shuts down the rendering system.*/
	void shutdown();

	/**Presents the contents of the main render buffer to the screen.*/
	void present();

	/**Acts as the third step in resizing the window.*/
	void resize(int width, int height);

	/**Sets the basic clear colour given four normalised values.*/
	void clearColour(float r, float g, float b, float a);

	/**Clears the specified components of the currently set render buffer.*/
	void clear(bool colour, bool depth, bool stencil = false);

	/**Finalises the deferred 3D rendering step.*/
	void lightPass(const std::vector<Light*>& dlights);

	void beginScene()
	{
		shadowBuffer.bind();
		clear(true, true, true);
		gbuffer.bind();
		clear(true, true, true);
	}

	void prepareGeomPass()
	{
		gbuffer.bind();
	}

	void prepareShadowPass()
	{
		
		shadowBuffer.bind();
	}

	/**Initialises the screen quad needed for deferred shading.*/
	void initialiseScreenQuad(Vertex2D* quad, GLuint& VBO, GLuint& VAO);


private:
	HDC m_hdc; //device context
	HGLRC m_hrc; //render context
	int m_pixelFormat;
	Sky m_sky;
	Texture m_skyTexture;
	SkyShader m_skyShader;
	Gbuffer gbuffer;

	struct
	{
		SkyShader skyShader;
		DirectionalLightShader directionalShader;
	} Shaders;

	ShadowBuffer shadowBuffer;

	///Disabled copy constructor.
	OpenGLClass(const OpenGLClass&);

	/**
	Attempts to determine the proper pixel format and save it to file.
	@param vsync Whether vsync is to be used.
	@param pfd The pixel format descriptor supplying creation information.
	@return value - 0 = success. 1 = error saving. -1 = fatal error.
	*/
	int  reloadPixelFormat(PIXELFORMATDESCRIPTOR& pfd);

	///Attempts to load the pixel format from file.
	bool loadPixelFormat();

	/**
	Initialises the OpenGL context.
	@param vsync Whether vsync is to be used.
	@param Whether to reload the pixel format instead of attempting to read from file.
	@return value Whether the function succeeded.
	*/
	bool initialiseContext(bool vsync, bool reset);

	/**Shuts down the context, freeing the associated resources.*/
	void shutdownContext();

	/**ully loads OpenGL functionality using GLEW.*/
	bool initialiseFunctionality();

	/**Sets up initial context settings.*/
	void initialiseContextSettings();

	/**Initialies some basic scene assets, such as the sky.*/
	bool initialiseSceneAssets();


	
	/**Renders the sky.*/
	void renderSky(Camera* camera, SkyShader* skyShader);

	/**Renders the directional lights during the lighting pass.*/
	void renderDirectionalLights(const std::vector<Light*>& lights, Camera& camera);
};