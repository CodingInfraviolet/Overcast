#pragma once
#include "Texture.h"
#include "movable.h"
#include "System.h"
#include "Graphics.h"
#include "ShaderProgram.h"

class Sprite : public Texture
{
protected:
	static GLuint VAO;

public:
	
	Sprite()
	{
	}

	void initialise()
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, systemptr->graphics->screenQuad.VBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), NULL);
		glBindVertexArray(0);
	}
	
	void setForRendering()
	{
		static bool initialised = false; //NOTE: Must not be done in constructor due to construction priority.
		if (!initialised)
		{
			VAO = ~0u;
			initialise();
			initialised = true;
		}

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, systemptr->graphics->screenQuad.VBO);
		if (!(m_data == nullptr))
			bindForGPU();
	}

};

class SpriteInstace : public Movable
{
private:
	Sprite* mParent = nullptr;

public:
	
	SpriteInstace(){}
	SpriteInstace(Sprite& sp)
	{
		mParent = &sp;
	}
	
	void draw(SpriteShader& shader)
	{
		if (pendingUpdate())
			update(shader);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void update(SpriteShader& shader)
	{
		shader.setPosScale(math::vec4(m_pos.x, m_pos.y, m_scale, m_scale));
		m_pendingMatrixUpdate = false;
	}
};