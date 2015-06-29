#include "stdafx.h"
#include "graphicsinterface.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))


namespace GraphicsInterface
{
	unsigned createTexture2D(int width, int height, const std::vector<std::pair<int, int> >& flags,
		Enum::ImageFormat format, Enum::Type type, unsigned char* data, Enum::InternalImageFormat internalFormat)
	{
		GLint currentBoundTexture;
		GLuint textureID = ~0u;

		glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentBoundTexture);
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, (internalFormat == 0 ? format : internalFormat), width,
			height, 0, format, type, data);

		for (auto it = flags.begin(); it != flags.end(); ++it)
			glTexParameteri(GL_TEXTURE_2D, it->first, it->second);

		glBindTexture(GL_TEXTURE_2D, currentBoundTexture);
		return textureID;
	}

	void destroyTexture2D(unsigned id)
	{
		glDeleteTextures(1, &id);
	}

	void bindTextureID(unsigned id)
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	GraphicsAPIData uploadMeshData(std::vector<Vertex3D> vertices, std::vector<ElementIndexType> indices,
		Enum::Usage vertexUsage, Enum::Usage indexUsage)
	{
		unsigned VAO=~0u, VBO=~0u, elementBuffer=~0u;

		int currentVAO, currentVBO, currentElementBuffer;
		glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);
		glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentVBO);
		glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentElementBuffer);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), &vertices[0], vertexUsage);

		glGenBuffers(1, &elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(ElementIndexType), &indices[0], indexUsage);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), NULL);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(sizeof(float) * 3));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(sizeof(float) * 6));

		glBindVertexArray(currentVAO);
		glBindBuffer(GL_ARRAY_BUFFER, currentVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentElementBuffer);

		GraphicsAPIData out;
		out.VAO = VAO;
		out.VBO = VBO;
		out.elementBuffer = elementBuffer;
		return out;
	}

	void deuploadMeshData(GraphicsAPIData* index)
	{
		glDeleteVertexArrays(1, &index->VAO);
		glDeleteBuffers(1, &index->VBO);
		glDeleteBuffers(1, &index->VAO);
		*index = { 0 };
	}

	void drawIndexedMeshWithState(unsigned indexCount)
	{
		glDrawElements(GL_TRIANGLES, indexCount, Enum::ELEMENT_INDEX_TYPE, 0);
	}
}