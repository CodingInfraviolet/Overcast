#pragma once
#include "ShaderProgram.h"
#include "Texture.h"

class ShadowBuffer
{
private:
	ShadowShader m_shader;
	unsigned m_FBO;

public:
	Texture m_texture;

	ShadowBuffer();
	~ShadowBuffer();

	bool initialise(bool mainShadowBuffer = true);

	void bind();

	void setAsGlobalShadowBuffer();

	void shutdown();
};