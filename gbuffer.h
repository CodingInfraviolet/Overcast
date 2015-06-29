#pragma once
#include "Texture.h"
#include "ShaderProgram.h"

class Gbuffer
{
public:
	enum TextureType { TEXTURE_TYPE_DIFFUSE, TEXTURE_TYPE_POSITION, TEXTURE_TYPE_NORMAL, TEXTURE_COUNT };

	Gbuffer();
	~Gbuffer();

	bool initialise(unsigned width, unsigned height, bool _initialiseShader=true);
	void shutdown();

	bool resize(unsigned width, unsigned height);

	void bind();
	void bindForReading();
	void setReadBuffer(TextureType);

private:
	unsigned m_FBO;
	Texture m_textures[TEXTURE_COUNT];
	Texture m_depthTexture;
	GeometryShader m_geometryShader;

	bool initialiseShader();
};