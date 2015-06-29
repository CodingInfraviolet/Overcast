#include "stdafx.h"
#include "shadowbuffer.h"
#include "drawable.h"

ShadowBuffer::ShadowBuffer()
{
	m_FBO = ~0u;
}

ShadowBuffer::~ShadowBuffer(){}

bool ShadowBuffer::initialise(bool mainShadowBuffer)
{
	if (!m_shader.load("Shaders/shadow.vert", "Shaders/shadow.frag"))
		return false;

	if (!m_texture.create(1024, 1024, Enum::GPU, Enum::DEPTH_COMPONENT,
	{ { GL_TEXTURE_MIN_FILTER, GL_NEAREST }, { GL_TEXTURE_MAG_FILTER, GL_NEAREST } }, Enum::FLOAT, Enum::DEPTH32))
		return false;
	

	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	m_texture.bindForGPU();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_TEXTURE_2D, m_texture.id(), 0);

	unsigned status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		Error(std::string("Could not create gbuffer. Error status ") + toString(status));
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (mainShadowBuffer)
		setAsGlobalShadowBuffer();

	return true;
}

void ShadowBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	m_shader.set();
}

void ShadowBuffer::setAsGlobalShadowBuffer()
{
	Drawable::s_shadowShader = &m_shader;
}

void ShadowBuffer::shutdown()
{
}