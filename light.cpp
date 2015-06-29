#include "stdafx.h"
#include "light.h"
#include "enums.h"

Light::Light()
{
	colour = math::vec3(1, 1, 1);

	intensity = 1;
	m_type = Enum::LIGHT_BASE;

	m_shadowInfo = nullptr;
}

Light::~Light()
{
	if (m_shadowInfo)
		delete m_shadowInfo;
}