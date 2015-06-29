#pragma once
#include "State.h"
#include "ShaderProgram.h"

class OpenGLClass;
class GuiText;

/**A class to handle higher level graphics.*/
class Graphics
{
	/**The constructor initialises varaibles to zero. It is private.*/
	Graphics();
	
	/**Disabled copy constructor.*/
	Graphics(const Graphics&);

	OpenGLClass* openglclass;
	GuiText* guitext;

	struct
	{
		math::vec4 leftPlane;
		math::vec4 rightPlane;
		math::vec4 bottomPlane;
		math::vec4 topPlane;
		math::vec4 nearPlane;
		math::vec4 farPlane;
		math::mat4 VPMatrix;
	} Frustrum;


public:

	struct
	{
		Vertex2D quad[6];
		GLuint VBO;
		GLuint VAO;
	} screenQuad;

	/**Creates an instance using the singleton design pattern.*/
	static Graphics* createInstance();

	/**
	Initialises the graphics subsystem, as well as opengl.
	@param screenw The screen width.
	@param screenh The screen height.
	@return Success value.
	*/
	bool initialise();

	/**Shuts down and destroys the graphics subsystem.*/
	void shutdown();

	/**Performs setup needed to begin drawing objects.*/
	void beginScene();

	void prepareGeomPass();

	void prepareShadowPass();

	void guiPass();

	/**Ends the scene and dispaly the result on screen.*/
	void endScene();

	/**Acts as the second step in resizing the window.*/
	void resize(int width, int height, GameState* state);

	void initialiseScreenQuad();
};