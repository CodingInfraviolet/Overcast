#pragma once
#include "enums.h"
#include "Vertex.h"

namespace GraphicsInterface
{
	/**Handles the basic information an object needs to have associated with it to reference it in the GPU.*/
	struct GraphicsAPIData
	{
		unsigned VAO, VBO, elementBuffer;

		/**Manipulates GPU state to set the data for drawing.*/
		void prepareForDrawing()
		{
			glBindVertexArray(VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		}
	};

	/**
	Creates a texture in the GPU given the parameters.
	@param width The width of the texture.
	@param height The height of the texture.
	@param flags The flags to be passed to the texture using the format std::pair<flag,value>. See OpenGL documentation.
	@param format The component format of the image. See Enum::ImageFormat. e.g., RGBA.
	@param type Sets the type of the components of the image. See Enum::Type. e.g., UNSIGNED_BYTE.
	@param data The image data to be put into the texture. NULL to create an empty texture.
	@param internalFormat The internal format under which the image is stored. See Enum::InternalImageFormat. If _IIFUndefined, then \
		   the format field will be used.
	@return Returns the id of the texture.
	*/
	unsigned createTexture2D(int width, int height,
		const std::vector<std::pair<int, int> >& flags = {}, Enum::ImageFormat format = Enum::RGBA,
		Enum::Type type = Enum::UNSIGNED_BYTE, unsigned char* data = NULL,
		Enum::InternalImageFormat internalFormat = Enum::_IIFUndefined);

	/**
	Destroys a texture in the GPU.
	@param id The id of the texture returned by createTexture2D(...).
	*/
	void destroyTexture2D(unsigned id);

	/**
	Binds the texture for use on the GPU.
	@param id The id of the texture returned by createTexture2D(...).
	*/
	void bindTextureID(unsigned id);

	/**
	Uploads mesh information for use on the GPU.
	@param vertices The unique vertices of the mesh.
	@param indices The indices of the mesh (0 indexed) that refer to the vertices.
	@param vertexUsage A hint to the GPU on the usage of the vertices. e.g., STATIC_DRAW.
	@param indexUsage A hint to the GPU on the usage of the indices. e.g., STATIC_DRAW.
	@return GraphicsAPIData The data needed to refer to and manipulate the object in the GPU.
	*/
	GraphicsAPIData uploadMeshData(std::vector<Vertex3D> vertices, std::vector<ElementIndexType> indices,
		Enum::Usage vertexUsage = Enum::STATIC_DRAW, Enum::Usage indexUsage = Enum::STATIC_DRAW);

	/**
	Destroys the mesh data from the GPU.
	@param GraphicsAPIData The object returned by uploadMeshData(...) during object creation, which is then reset.
	*/
	void deuploadMeshData(GraphicsAPIData* index);

	/**
	Draws the indexed mesh that was previously set for usage.
	@param indexCount The number of indices to process during rendering.
	*/
	void drawIndexedMeshWithState(unsigned indexCount);
}