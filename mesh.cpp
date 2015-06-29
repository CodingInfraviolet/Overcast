#include "stdafx.h"
#include "mesh.h"
#include "vmfheader.h"


Mesh::Mesh() : m_inCPU(0), m_inGPU(0), m_apiData({ 0 }),
							   m_vertexCount(0), m_indexCount(0) {}

Mesh::Mesh(const char *path, int loadLocation) : Mesh()
{
	load(path, loadLocation);
}

bool Mesh::loadFromFile(const char *path)
{
	std::string fileLocation = path;
	FileSystem::toSpecialPath(&fileLocation);

	Inform(std::string("Loading object: \"") + fileLocation + "\"");

	std::ifstream modelFile(fileLocation, std::ios::binary);
	modelFile.seekg(0);

	if (modelFile.fail())
	{
		Warning(std::string("Could not open \"") + fileLocation + "\"!\n" + strerror(errno));
		return false;
	}

	//Read in header
	VMFHeader header;
	modelFile.read(reinterpret_cast<char*>(&header), sizeof(header));

	m_vertexCount	= header.vertCount;
	m_indexCount	= header.indexCount;

	m_vertices.clear();
	m_indices.clear();
	m_inCPU = false;

	//Fill vectors from file:
	if (header.vertCount > 0)
	{
		m_vertices.resize(header.vertCount);
		modelFile.read(reinterpret_cast<char*>(&m_vertices[0]), header.vertCount*sizeof(m_vertices[0]));
	}
	if (header.indexCount > 0)
	{
		m_indices.resize(header.indexCount);
		modelFile.read(reinterpret_cast<char*>(&m_indices[0]), header.indexCount*sizeof(ElementIndexType));
	}
	//

	m_inCPU = true;
	return true;
}

void Mesh::clearCPU()
{
	m_vertices.clear();
	m_indices.clear();
	m_inCPU = false;
}

void Mesh::upload(Enum::Usage vertexUsage, Enum::Usage indexUsage)
{
	if (m_inCPU)
	{
		m_apiData = GraphicsInterface::uploadMeshData(m_vertices, m_indices, vertexUsage, indexUsage);
		m_inGPU = true;
	}
}

void Mesh::deupload()
{
	if (m_inGPU)
	{
		GraphicsInterface::deuploadMeshData(&m_apiData);
		m_inGPU = false;
	}
}

bool Mesh::load(const char *path, int loadLocation)
{
	clearMeshData();

	//Local inXXX checks - don't touch m_ originals.
	bool l_inCPU	= (loadLocation & Enum::CPU) == Enum::CPU;
	bool l_inGPU	= (loadLocation & Enum::GPU) == Enum::GPU;

	if (!l_inCPU && !l_inGPU)
		return true;

	if (!loadFromFile(path))
		return false;

	// These automatically set m_inXXX.
	if (l_inGPU)
		upload();
	if (!l_inCPU)
		clearCPU();

	return true;
}

void Mesh::clearMeshData()
{
	if (m_inGPU)
	{
		deupload();
		m_inGPU = false;
	}
	if (m_inCPU)
	{
		clearCPU();
		m_inCPU = false;
	}
}