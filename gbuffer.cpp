#include "stdafx.h"
#include "gbuffer.h"
#include "drawable.h"

Gbuffer::Gbuffer()
{
	m_FBO = ~0u;
}

Gbuffer::~Gbuffer()
{

}

bool Gbuffer::initialise(unsigned width, unsigned height, bool _initialiseShader)
{
	if (_initialiseShader) //Made optional for resizing purposes.
		if (!initialiseShader())
			return false;

	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	for (unsigned i = 0; i < TEXTURE_COUNT; ++i)
	{
		m_textures[i].create(width, height, Enum::GPU, Enum::RGB,
		{ make_pair(GL_TEXTURE_MIN_FILTER, GL_NEAREST), make_pair(GL_TEXTURE_MAG_FILTER, GL_NEAREST) }, Enum::FLOAT, Enum::RGB32F);
		m_textures[i].bindForGPU();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
			GL_TEXTURE_2D, m_textures[i].id(), 0);
	}

	m_depthTexture.create(width, height, Enum::GPU, Enum::DEPTH_COMPONENT,
	{ make_pair(GL_TEXTURE_MIN_FILTER, GL_NEAREST), make_pair(GL_TEXTURE_MAG_FILTER, GL_NEAREST) }, Enum::FLOAT, Enum::DEPTH32F_STENCIL8);
	m_depthTexture.bindForGPU();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture.id(), 0);

	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2 };

	glDrawBuffers(3, drawBuffers);

	unsigned status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		Error(std::string("Could not create gbuffer. Error status ") + toString(status));
		return false;
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void Gbuffer::shutdown()
{
	for (Texture& tx : m_textures)
		tx.clear();

	m_depthTexture.clear();

	if (m_FBO == ~0u)
	{
		glDeleteFramebuffers(1, &m_FBO);
		m_FBO = ~0u;
	}
}

bool Gbuffer::resize(unsigned width, unsigned height)
{
	shutdown();
	if (!initialise(width, height, false))
		return false;
	return true;
}

bool Gbuffer::initialiseShader()
{
	if (!m_geometryShader.load("Shaders/geometry.vert", "Shaders/geometry.frag"))
		return false;
	Drawable::s_geometryShader = &m_geometryShader;
	return true;
}

/**Binds framebuffer and shader.*/
void Gbuffer::bind()
{
	m_geometryShader.set();
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

/**Binds the appropriate textures.*/
void Gbuffer::bindForReading()
{
	glActiveTexture(GL_TEXTURE0);
	m_textures[TEXTURE_TYPE_DIFFUSE].bindForGPU();
	glActiveTexture(GL_TEXTURE1);
	m_textures[TEXTURE_TYPE_NORMAL].bindForGPU();
	glActiveTexture(GL_TEXTURE2);
	m_textures[TEXTURE_TYPE_POSITION].bindForGPU();
	glActiveTexture(GL_TEXTURE0);
}

void Gbuffer::setReadBuffer(Gbuffer::TextureType type)
{
	glReadBuffer(GL_COLOR_ATTACHMENT0 + type);
}