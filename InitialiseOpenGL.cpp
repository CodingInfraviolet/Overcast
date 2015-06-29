#include "stdafx.h"
#include "OpenGLClass.h"
#include "System.h"
#include "gbuffer.h"

#define GL_DEBUG_MODE

void _stdcall debugCallbackARB(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar*, GLvoid*);

OpenGLClass::OpenGLClass()
{
	m_hdc = 0;
	m_hrc = 0;
	m_pixelFormat = 0;
}

OpenGLClass::OpenGLClass(const OpenGLClass&) {}

int OpenGLClass::reloadPixelFormat(PIXELFORMATDESCRIPTOR& pfd)
{
	using namespace std;

	//shutdown(); //What?

	m_pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	if (!m_pixelFormat)
	{
		Error("Could not create pixel format.");
		return -1;
	}

	fstream formatfile(PIXELFORMATPATH, ios::out | ios::binary | ios::trunc);
	if (formatfile.fail())
	{
		Warning(string("Could not open ") + PIXELFORMATPATH + "\nFormat not saved.");
		return 1;
	}
	formatfile.write((char*)&m_pixelFormat, sizeof(m_pixelFormat));
	formatfile.close();
	return 0;
}

bool OpenGLClass::loadPixelFormat()
{
	using namespace std;
	fstream formatfile(PIXELFORMATPATH, ios::in | ios::binary);
	if (formatfile.fail())
	{
		Warning(string("Could not open ") + PIXELFORMATPATH + "\nFormat regenerated.");
		return false;
	}
	formatfile.read((char*)&m_pixelFormat, sizeof(m_pixelFormat));
	formatfile.close();
	return true;
}

bool OpenGLClass::initialiseContext(bool vsync, bool reset)
{
	//Create device context
	m_hdc = GetDC(systemptr->hwnd());

	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | (vsync ? PFD_DOUBLEBUFFER : 0);
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;

	if (reset)
	{
		if (reloadPixelFormat( pfd) == -1)
			return false;
	}
	else if (!loadPixelFormat())
	{
		if (reloadPixelFormat( pfd) == -1)
			return false;
	}

	if (!SetPixelFormat(m_hdc, m_pixelFormat, &pfd))
		return false;

	m_hrc = wglCreateContext(m_hdc);
	if (m_hrc == NULL)
	{
		Error(std::string("Error creating OpenGL Context.\nError code: ") + toString(GetLastError()));
		return false;
	}

	if (!wglMakeCurrent(m_hdc, m_hrc))
	{
		Error(std::string("Error setting OpenGL Context.\nError code: ") + toString(GetLastError()));
		return false;
	}
	return true;
}

bool OpenGLClass::initialiseFunctionality()
{
	//init glew
	{
		glewExperimental = TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			Error(std::string("Could not initialise GLEW.\n") + (char*)glewGetErrorString(err));
			return false;
		}
	}
	return true;
}

void OpenGLClass::initialiseContextSettings()
{
	glClearColor(0.f, 0.f, 0.0f, 1.f);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	glCullFace(GL_BACK);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#ifdef GL_DEBUG_MODE
	glDebugMessageCallback(debugCallbackARB, stderr);
	glEnable(GL_DEBUG_OUTPUT);
#endif
	glClearDepth(1.f);

}

bool OpenGLClass::initialiseSceneAssets()
{
	//if (!m_sky.load("Game/Models/SkyDome.obj", Enum::GPU))
	//	return false;
	return true;
}

bool OpenGLClass::initialise(bool reset)
{
	if (!initialiseContext(systemptr->displaySet.vsync, reset))
		return false;
	if (!initialiseFunctionality())
		return false;
	if (!gbuffer.initialise(systemptr->displaySet.screenWidth, systemptr->displaySet.screenHeight))
		return false;
	if (!shadowBuffer.initialise())
		return false;

	initialiseContextSettings();
	initialiseSceneAssets();

	glViewport(0, 0, systemptr->displaySet.screenWidth, systemptr->displaySet.screenHeight);

	if (!Shaders.directionalShader.load("Shaders/DirectionalLight.vert", "Shaders/DirectionalLight.frag")) return false;
	if (!Shaders.skyShader.load("Shaders/sky.vert", "Shaders/sky.frag")) return false;

	unsigned err = glGetError();
	if (err != 0) Error(std::string("Unable to initialise GL. Error code " + toString(err)));

	return true;
}


void OpenGLClass::initialiseScreenQuad(Vertex2D* quad, GLuint& VBO, GLuint& VAO)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * 6, quad, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), NULL);
	glBindVertexArray(0);
}