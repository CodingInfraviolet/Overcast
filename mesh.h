#pragma once
#include "drawable.h"
#include "graphicsinterface.h"
#include "enums.h"
#include "typedefs.h"


/**A virtual base class designed to handle basic mesh management, such as loading, uploading to the GPU, etc. Not placable.*/
class Mesh : public Drawable
{
protected:
	std::vector < Vertex3D > m_vertices;
	std::vector < ElementIndexType > m_indices;
	unsigned m_vertexCount, m_indexCount;
	GraphicsInterface::GraphicsAPIData m_apiData;
	bool m_inCPU, m_inGPU;
public:


	/**Initialises internal variables to zero.*/
	Mesh();

	/**
	Loads an object from the corresponding vmf file during construction.
	@param path The path of the original file (.obj, etc.)
	@param loadLocation A combination of Enum::GPU and Enum::CPU to determine where the model data will be stored.
	*/
	Mesh(const char *path, int loadLocation);

	/**
	Loads an object from the corresponding vmf file.
	@param path The path of the original file (.obj, etc.)
	@param loadLocation A combination of Enum::GPU and Enum::CPU to determine where the model data will be stored.
	*/
	bool load(const char *path, int loadLocation);

	//More low level:

	/**
	Loads a model from a file into the CPU. Shouldn't call directly.
	@param path The path of the original file (.obj, etc.)
	*/
	bool loadFromFile(const char *path);

	///Clears the model information from the CPU.
	void clearCPU();

	/**
	Uploads the model to GPU memory.
	@param vertexUsage The usage hint to the GPU for the vertices. e.g, Enum::STATIC_DRAW.
	@param indexUsage The usage hint to the GPU for the indices. e.g., Enum::STATIC_DRAW.
	*/
	void upload(Enum::Usage vertexUsage = Enum::STATIC_DRAW, Enum::Usage indexUsage = Enum::STATIC_DRAW);


	/**Clears the model information from GPU memory.*/
	void deupload();

	/**Fully clears the object from CPU and GPU, where applicable.*/
	void clearMeshData();

	/**Override this to implement drawing functionality.*/
	virtual void draw(Camera* camera) = 0;
};