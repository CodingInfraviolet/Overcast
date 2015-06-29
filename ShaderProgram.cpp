#include "stdafx.h"
#include "ShaderProgram.h"

bool ShaderProgramBase::validate()
{
	GLint valstatus;
	glValidateProgram(m_id);
	glGetProgramiv(m_id, GL_VALIDATE_STATUS, &valstatus);
	if (!valstatus)
	{
		GLint length;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
		char* log = new char[length];
		glGetProgramInfoLog(m_id, length, NULL, log);
		Error(string("Error validating program:") + log);
		delete[] log;
		return false;
	}
	return true;
}

bool ShaderProgramBase::load(const string& vertpath, const string& fragpath)
{
	Inform (std::string("Making shader: ") + getNameFromDirectory(vertpath) + ", " +
		getNameFromDirectory(fragpath));
	fstream fragfile(fragpath, ios::in | ios::ate), vertfile(vertpath, ios::in | ios::ate);
	const unsigned fragsize = (unsigned)fragfile.tellg(), vertsize = (unsigned)vertfile.tellg();
	fragfile.seekg(0);
	vertfile.seekg(0);
	if (vertfile.fail() || vertsize == 0)
	{
		Warning(string("Could not open ") + vertpath);
		return false;
	}
	if (fragfile.fail() || fragsize == 0)
	{
		Warning(string("Could not open ") + fragpath + "!");
		return false;
	}

	string vertstr, fragstr, temp;
	while (getline(vertfile, temp))
		vertstr += temp + "\n";
	while (getline(fragfile, temp))
		fragstr += temp + "\n";
	fragfile.close();
	vertfile.close();
	GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint vert = glCreateShader(GL_VERTEX_SHADER);
	const char* fragPointer = fragstr.c_str();
	const char* vertPointer = vertstr.c_str();

	glShaderSource(frag, 1, &fragPointer, NULL);
	glShaderSource(vert, 1, &vertPointer, NULL);
	GLsizei logLength;
	GLint result;
	glCompileShader(frag);
	glGetShaderiv(frag, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &logLength);
		char* fragmentShaderErrorMessage = new char[logLength];
		glGetShaderInfoLog(frag, logLength, NULL, fragmentShaderErrorMessage);
		Warning(string("Error loading fragment shader: ") + fragmentShaderErrorMessage);
		delete[] fragmentShaderErrorMessage;
		return false;
	}

	glCompileShader(vert);
	glGetShaderiv(vert, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &logLength);
		char* vertexShaderErrorMessage = new char[logLength];
		glGetShaderInfoLog(vert, logLength, NULL, vertexShaderErrorMessage);
		Warning(string("Error loading vertex shader: ") + vertexShaderErrorMessage);
		delete[] vertexShaderErrorMessage;
		return false;
	}
	GLuint prog = glCreateProgram();
	glAttachShader(prog, frag);
	glAttachShader(prog, vert);
	glLinkProgram(prog);
	glDeleteShader(frag);
	glDeleteShader(vert);
	glGetProgramiv(prog, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
		char* ProgramErrorMessage = new char[std::max(logLength, int(1))];
		glGetProgramInfoLog(prog, logLength, NULL, &ProgramErrorMessage[0]);
		ProgramErrorMessage;
		Warning(string("Linking error: ") + ProgramErrorMessage);
		delete[] ProgramErrorMessage;
		return false;
	}

	m_frag = frag;
	m_vert = vert;
	m_id = prog;

	prepare();

	if (!validate())
		return false;

	return true;
}

ShaderProgramBase::~ShaderProgramBase()
{
	if (m_id)
	{
		if (m_vert)
			glDetachShader(m_vert, m_id);
		if (m_frag)
			glDetachShader(m_frag, m_id);
		glDeleteProgram(m_id);
	}
}

void ShaderProgramBase::set()
{
	glUseProgram(m_id);
}

void GeometryShader::prepare()
{
	glUseProgram(m_id);
	MVPID = glGetUniformLocation(m_id, "MVP");
	MVID = glGetUniformLocation(m_id, "ModelViewMatrix");
	MID = glGetUniformLocation(m_id, "ModelMatrix");
	diffuseTextureID = glGetUniformLocation(m_id, "DiffuseTexture");
	glUniform1i(diffuseTextureID, 0);
	glUseProgram(0);
}

void GeometryShader::setMVP(const math::mat4& MVP)
{
	glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP.m[0][0]);
}

void GeometryShader::setModelMatrix(const math::mat4& modelMatrix)
{
	glUniformMatrix4fv(MID, 1, GL_FALSE, &modelMatrix.m[0][0]);
}

void GeometryShader::setModelViewMatrix(const math::mat4& viewMatrix)
{
	glUniformMatrix4fv(MVID, 1, GL_FALSE, &viewMatrix.m[0][0]);
}

void ShadowShader::prepare()
{
	glUseProgram(m_id);
	MVPID = glGetUniformLocation(m_id, "MVP");
	glUseProgram(0);
}

void ShadowShader::setMVP(const math::mat4& MVP)
{
	glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP.m[0][0]);
}

void LightShaderBase::prepare()
{
	glUseProgram(m_id);

	geometryDiffuseTexID = glGetUniformLocation(m_id, "DiffuseTexture");
	geometryNormalTexID = glGetUniformLocation(m_id, "NormalTexture");
	geometryPosTexID = glGetUniformLocation(m_id, "PositionTexture");
	shadowMapID = glGetUniformLocation(m_id, "ShadowMap");
	VID = glGetUniformLocation(m_id, "ViewMatrix");
	lightColourID = glGetUniformLocation(m_id, "LightColour");
	LID = glGetUniformLocation(m_id, "LightMatrix");

	glUniform1i(geometryDiffuseTexID, 0);
	glUniform1i(geometryNormalTexID, 1);
	glUniform1i(geometryPosTexID, 2);
	glUniform1i(shadowMapID, 3);
	glUseProgram(0);
}

void LightShaderBase::setLightColour(const math::vec3& colour)
{
	glUniform3fv(lightColourID, 1, &colour.x);
}

void LightShaderBase::setViewMatrix(const math::mat4 viewMatrix)
{
	glUniformMatrix4fv(VID, 1, GL_FALSE, &viewMatrix.m[0][0]);
}

void LightShaderBase::setLightMatrix(const math::mat4& LM)
{
	glUniformMatrix4fv(LID, 1, GL_FALSE, &LM.m[0][0]);
}

DirectionalLightShader::DirectionalLightShader()
{
	static bool exists = false;
	assert(!exists);
	exists = true;
}

void DirectionalLightShader::prepare()
{;
	LightShaderBase::prepare();
	lightVectorID = glGetUniformLocation(m_id, "LightVector");
}

void DirectionalLightShader::setLight(const DirectionalLight* light, const math::mat4& viewMatrix)
{
	math::vec3 lightVectorCameraspace =
		((viewMatrix*math::vec4(light->vector.x, light->vector.y, light->vector.z, 0)).xyz()).normalize();


	setLightVector(lightVectorCameraspace);
	setLightColour(light->colour*light->intensity);
}

void DirectionalLightShader::setLightVector(const math::vec3& vector)
{
	glUniform3fv(lightVectorID, 1, &vector.x);
}

SkyShader::SkyShader()
{
	static bool exists = false;
	assert(!exists);
	exists = true;
}

void SkyShader::prepare()
{
	MVPID = glGetUniformLocation(m_id, "MVP");
}

void SkyShader::setMVP(const math::mat4 MVP)
{
	glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP.m[0][0]);
}


SpriteShader::SpriteShader()
{
	static bool exists = false;
	assert(!exists);
	exists = true;
}

void SpriteShader::prepare()
{
	glUseProgram(m_id);
	textureID = glGetUniformLocation(m_id, "Texture");
	posScaleID = glGetUniformLocation(m_id, "PosScale");
	aspectScaleID = glGetUniformLocation(m_id, "Aspect");
	glUniform1i(textureID, 0);
	glUseProgram(0);
}

void SpriteShader::setPosScale(const math::vec4& posScale)
{
	glUniform4fv(posScaleID, 1, &posScale.x);
}


void SpriteShader::setAspectScale(const float aspect)
{
	glUniform1f(aspectScaleID, aspect);
}
