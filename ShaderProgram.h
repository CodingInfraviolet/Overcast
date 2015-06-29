#pragma once
#include "Texture.h"
#include "light.h"

using namespace std;

/**A virtual base class to give essential shader creation functionality to derived classes.*/
class ShaderProgramBase
{
private:
	GLuint m_vert = 0;
	GLuint m_frag = 0;

protected:
	GLuint m_id = 0;

	/**Performs shader-specific setup. Override, but don't call directly.*/
	virtual void prepare() = 0; //called from within load(...) function.
public:

	/**Returns the ID of the shader.*/
	GLint id() { return m_id; };

	/**
	Initialises the shader from a source file.
	@param vertpath The part of the vertex shader.
	@param fragpath The path of the fragment shader.
	@return The success value.
	*/
	bool load(const string& vertpath, const string& fragpath);

	/**Checks whether the shader is working properly.*/
	bool validate();

	/**The virtual destructor to do basic cleanup.*/
	virtual ~ShaderProgramBase();

	/**Sets the shader as the current one in the rendering pipeline.*/
	void set();
};


/**A geometry shader to be used in deferred shading.*/
class GeometryShader : public ShaderProgramBase
{
protected:
	/**Implements custom setup.*/
	void prepare() override;

	GLint MVPID;
	GLint MVID;
	GLint MID;
	GLint diffuseTextureID;


public:
	/**Uploads the MVP matrix.*/
	void setMVP(const math::mat4& MVP);

	/**Uploads the model matrix matrix.*/
	void setModelMatrix(const math::mat4& modelMatrix);

	/**Uploads the model view matrix (resulting in cameraspace).*/
	void setModelViewMatrix(const math::mat4& viewMatrix);
};

/**A geometry shader to be used in deferred shading.*/
class ShadowShader : public ShaderProgramBase
{
protected:
	/**Implements custom setup.*/
	void prepare() override;

	GLint MVPID;


public:
	/**Uploads the MVP matrix.*/
	void setMVP(const math::mat4& MVP);
};

class LightShaderBase : public ShaderProgramBase
{
protected:
	virtual void prepare() override;

	GLint geometryDiffuseTexID;
	GLint geometryNormalTexID;
	GLint geometryPosTexID;
	GLint shadowMapID;

	GLint VID;
	GLint lightColourID;
	GLint LID;

	/**Disabled direct constructor.*/
	LightShaderBase(){}

public:
	/**Uploads the light colour.*/
	void setLightColour(const math::vec3& colour);

	/**Uploads the view (IE. CAMERA) matrix.*/
	void setViewMatrix(const math::mat4 viewMatrix);

	/**Uploads the light matrix.*/
	void setLightMatrix(const math::mat4& LM);
};

class DirectionalLightShader : public LightShaderBase
{
	/**Implements custom setup.*/
	void prepare() override;
	
	GLint lightVectorID;

public:
	/**Ensures single instance through assertion.*/
	DirectionalLightShader();

	/**Uploads the light.*/
	void setLight(const DirectionalLight* light, const math::mat4& viewMatrix);

	void setLightVector(const math::vec3& vector);
};

class PointLightShader : public LightShaderBase
{
	/**Implements custom setup.*/
	void prepare() override;

	GLint lightPositionID;

public:
	/**Ensures single instance through assertion.*/
	PointLightShader();

	/**Uploads the light vector.*/
	void setLightPosition(const math::vec3 lightPosition);
};


/**A shader to be used for the sky.*/
class SkyShader : public ShaderProgramBase
{
protected:
	/**Implements custom setup.*/
	void prepare() override;

	GLint MVPID;
public:

	/**Ensures single instance through assertion.*/
	SkyShader();

	/**Uploads the MVP matrix.*/
	void setMVP(const math::mat4 MVP);
};

/**A shader to be used for the sky.*/
class SpriteShader : public ShaderProgramBase
{
protected:
	/**Implements custom setup.*/
	void prepare() override;

	GLint textureID;
	GLint posScaleID;
	GLint aspectScaleID;
public:

	/**Ensures single instance through assertion.*/
	SpriteShader();

	/**Uploads the coords.*/
	void setPosScale(const math::vec4& posScale);

	void setAspectScale(float aspect);
};