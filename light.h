#pragma once
#include "enums.h"

class LightShadowInfo
{
public:
	LightShadowInfo(){}
	LightShadowInfo(const math::mat4& proj) : m_projection(proj) {}

	math::mat4 getPorjection() const
	{
		return m_projection;
	}
private:
	math::mat4 m_projection;
};

/**A class designed to encapsulate the basic light type, acting as a base class for more advanced types.*/
class Light
{
protected:
	Enum::LightType m_type;
	LightShadowInfo* m_shadowInfo;

public:

	math::vec3 colour;
	float intensity;

	/**Returns the type of the light.*/
	Enum::LightType type() const { return m_type; } 

	LightShadowInfo* getShadowInfo()
	{
		return m_shadowInfo;
	}

	void setShadowInfo(LightShadowInfo* shadowInfo)
	{
		if (m_shadowInfo)
			delete m_shadowInfo;
		m_shadowInfo = shadowInfo;
	}

	/**Initialises the internal variables.*/
	Light();

	virtual ~Light();
};

/**A directional light class, extending the basic Light.*/
class DirectionalLight : public Light
{
public:
	math::vec3 vector;

	/**Initialises the internal variables.*/
	DirectionalLight() : Light()
	{
		m_type = Enum::LIGHT_DIRECTIONAL;
		m_shadowInfo = new LightShadowInfo(math::createOrthoProjectionMatrix(-80,80,-80,80,-80,80));
	}
};