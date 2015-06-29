#define OVERCAST_DLL
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem/operations.hpp>
#include "modelfilesystem.h"
#include "typedefs.h"
#include "Vertex.h"
#include "vmfheader.h"
using namespace std;
using namespace boost::filesystem;

namespace FileSystem
{
	/**
	*@brief Determines whether the file is a model that can be loaded.
	*/
	bool isModel(string& name, bool vmf)
	{
		static vector<string> supportedFormats = { "obj", "3ds" };

		if (!is_regular_file(name)) return false;

		//Check if it's one of the supported formats

		unsigned extensionPos = name.rfind(".");
		if (extensionPos == (unsigned)string::npos) return false; //If no extension.

		string extension = name.substr(extensionPos + 1);


		if (vmf)
			return (extension == CUSTOM_OBJECT_FORMAT);
		else
		{
			bool supported = false;
			for (unsigned i = 0; i < supportedFormats.size(); i++)
			{
				if (extension == supportedFormats[i])
				{
					supported = true;
					break;
				}
			}
			return supported;
		}
	}

	void toSpecialPath(string* path)
	{
		unsigned modelsPos = path->find("Models");
		if (modelsPos == (unsigned)string::npos)
		{
			std::cerr << "Model path does not contain \"Models\"\n";
			return;
		}
		path->replace(modelsPos, sizeof("Models") - 1, "PROCESSED_MODELS/Models");

		unsigned extensionPos(path->rfind('.'));
		if (extensionPos == (unsigned)string::npos) return; //If not a model

		path->erase(path->begin() + extensionPos + 1, path->end());
		path->append(CUSTOM_OBJECT_FORMAT);
	}

	bool processModel(const char fileLocation[], const char* destination)
	{
		std::cout << (string("Processing model \"") + fileLocation + "\"\n");
		ifstream modelFile(fileLocation);

		if (!modelFile)
		{
			std::cout << (string("Could not open \"") + fileLocation + "\"!\n");
			return false;
		}

		//Under construction:
		Assimp::Importer importer;

		importer.SetPropertyInteger("AI_CONFIG_PP_RVC_FLAGS", aiComponent_COLORS |
			aiComponent_BONEWEIGHTS |
			aiComponent_ANIMATIONS |
			aiComponent_TEXTURES |
			aiComponent_LIGHTS |
			aiComponent_CAMERAS |
			aiComponent_MATERIALS |
			aiComponent_COLORS |
			aiComponent_TANGENTS_AND_BITANGENTS);

		const aiScene* scene = nullptr;
		scene = importer.ReadFile(fileLocation,
			aiProcess_Triangulate |

			aiProcess_GenNormals |
			aiProcess_JoinIdenticalVertices |
			aiProcess_RemoveComponent |
			aiProcess_ImproveCacheLocality |
			//aiProcess_FindDegenerates |
			aiProcess_SortByPType |
			aiProcess_FindInvalidData |
			aiProcess_OptimizeMeshes |
			aiProcess_OptimizeGraph |
			aiProcess_GenUVCoords |
			aiProcess_FlipUVs |
			aiProcess_TransformUVCoords
			);

		if (!scene)
		{
			std::cerr << "Could not load fileLocation! Error: " << importer.GetErrorString();
			return false;
		}

		vector <Vertex3D> vertices;
		vector <ElementIndexType> indices;

		//Not used. Remove:
		float minBoundingPointX = 0, minBoundingPointY = 0, minBoundingPointZ = 0;
		float maxBoundingPointX = 0, maxBoundingPointY = 0, maxBoundingPointZ = 0;

		unsigned previousVerticesProcessed = 0; //Offset needed for next model

		for (unsigned m = 0; m < scene->mNumMeshes; m++) //For every model
		{
			aiMesh* mesh = nullptr;
			mesh = scene->mMeshes[m]; //Get the mesh of the model
			if (!mesh) return false;

			{
				const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);


				for (unsigned p = 0; p < mesh->mNumVertices; p++) //Fill the usual vectors
				{
					const aiVector3D* pPos = &(mesh->mVertices[p]);
					const aiVector3D* pNormal = &(mesh->mNormals[p]);
					const aiVector3D* pTexCoord = (mesh->HasTextureCoords(0)) ? &(mesh->mTextureCoords[0][p]) : &Zero3D;

					vertices.push_back(Vertex3D(pPos->x, pPos->y, pPos->z, pNormal->x, pNormal->y, pNormal->z,
						pTexCoord->x, pTexCoord->y));
				}


				for (unsigned f = 0; f < mesh->mNumFaces; f++) //For every face, get the indices:
				{
					const aiFace& face = mesh->mFaces[f]; //Get face

					for (unsigned v = 0; v < face.mNumIndices; v++) //For every vertex in the face:
					{
						//(add vertex offset for each model as well)
						indices.push_back(face.mIndices[v] + previousVerticesProcessed);
					}
				}
			}
			previousVerticesProcessed = vertices.size();
		}


		float centrePointX = (minBoundingPointX + maxBoundingPointX) / 2.f;
		float centrePointY = (minBoundingPointY + maxBoundingPointY) / 2.f;
		float centrePointZ = (minBoundingPointZ + maxBoundingPointZ) / 2.f;

		float objectRadius = sqrt(
			(minBoundingPointX - maxBoundingPointX)*(minBoundingPointX - maxBoundingPointX) +
			(minBoundingPointY - maxBoundingPointY)*(minBoundingPointY - maxBoundingPointY) +
			(minBoundingPointZ - maxBoundingPointZ)*(minBoundingPointZ - maxBoundingPointZ)
			);


		unsigned int vertexCount = vertices.size();
		unsigned int indexCount = indices.size();

		VMFHeader header;
		header.vertCount = vertexCount;
		header.indexCount = indexCount;
		header.objectRadius = objectRadius;
		header.centrePointX = centrePointX;
		header.centrePointY = centrePointY;
		header.centrePointZ = centrePointZ;

		ofstream OutputFile;
		string newPath = fileLocation;

		if (destination == NULL) //Go Overcast route:
		{
			toSpecialPath(&newPath);
			string newDir = newPath;
			newDir.erase(newDir.begin() + ((newPath.find("\\") == string::npos) ? newPath.rfind("/") : newPath.rfind("\\")), newDir.end());

			//newDir = newPath with no file name

			boost::filesystem::create_directories(newDir);
		}
		else //Go to custom destination:
		{
			newPath = destination;
		}

		OutputFile.open(newPath, ios::binary | ios::trunc);

		if (!OutputFile)
		{
			std::cerr << "Could not create location: " + newPath;
			return false;
		}

		OutputFile.seekp(0);

		OutputFile.write(reinterpret_cast<char*>(&header), sizeof(header));

		if (vertices.size() != 0)
			OutputFile.write(reinterpret_cast<char*>(&vertices[0]), vertices.size()*sizeof(vertices[0]));
		if (indices.size() != 0)
			OutputFile.write(reinterpret_cast<char*>(&indices[0]), indices.size() *sizeof(ElementIndexType));

		OutputFile.close();



	return true;
}

void CommenceModelFileSystem()
{
	char StructureIndexPath[] = "Game/PROCESSED_MODELS/StructureIndex.index";
	char ModelPath[] = "Game/Models/";


	std::cout << ":- Checking model filesystem consistency...\n";

	//Open/Recreate StructureIndex
	fstream StructureIndex(StructureIndexPath, ios::in | ios::out);
	if (!StructureIndex)
	{
		std::cout << ":- Index not found. Creating...\n";
		StructureIndex.close();

		//Create:
		StructureIndex.open(StructureIndexPath, ios::out);
		StructureIndex.close();
		StructureIndex.open(StructureIndexPath, ios::in | ios::out);
		//

		if (!StructureIndex)
		{
			std::cerr << "FATAL ERROR: Could not create StructureIndex.index\n";
			return;
		}
	}

	///////////////////////////////

	//Get list of models in /object
	recursive_directory_iterator rdi(ModelPath);
	recursive_directory_iterator end_rdi;

	typedef map<string, long long > IndexType; //path, modified time

	IndexType NormalObjectList;
	for (; rdi != end_rdi; rdi++)
	{
		string path = (*rdi).path().string();
		if (!isModel(path)) continue;

		unsigned lastWriteTime = (unsigned)last_write_time(path);

		NormalObjectList[path] = lastWriteTime;
	}
	//


	//Read in list of models in /object from INDEX
	IndexType NormalObjectIndex;
	{
		string line;
		while (getline(StructureIndex, line))
		{
			if (line.size() == 0) continue;
			string size, lastWriteTime;
			getline(StructureIndex, lastWriteTime);

			NormalObjectIndex[line] = stoull(lastWriteTime);
		}

	}
	IndexType OldNormalObjectIndex;


	bool modified = false;

	//Iterate through NormalObjectList and check whether it is indexed and the index matches
	for (auto it = NormalObjectList.begin(); it != NormalObjectList.end(); ++it)
	{
		//Check if indexed file's special version exists and is up to date. If not:
		auto it2 = NormalObjectIndex.find(it->first);
		if (it2 == NormalObjectIndex.end() || it->second != it2->second)
		{
			//If not, add to index:
			processModel(it->first.c_str());
			NormalObjectIndex[it->first] = it->second;
			modified = true;
		}

	}

	//Iterate through NormalObjectIndex and check whether it still exists. If not, delete the copy.
	for (auto it = NormalObjectIndex.begin(); it != NormalObjectIndex.end();)
	{
		//Check if indexed file's normal version exists:
		auto it2 = NormalObjectList.find(it->first);
		if (it2 == NormalObjectList.end())
		{
			//If original does not exist, delete special version (it):
			string path = it->first;
			toSpecialPath(&path);

			if (exists(path))
				remove(path);

			//Remove directory if it is empty
			if (path.rfind("\\") == string::npos)
				path.erase(path.begin() + path.rfind('/'), path.end());
			else
				path.erase(path.begin() + path.rfind('\\'), path.end());
			path += "/";

			recursive_directory_iterator rdi(path);
			recursive_directory_iterator end_rdi;

			bool isEmpty = true;
			for (; rdi != end_rdi; rdi++)
			{
				string subPath = (*rdi).path().string();

				if (isModel(subPath, true))
				{
					isEmpty = false;
					break;
				}
			}

			if (isEmpty)
				remove(path);

			NormalObjectIndex.erase(it++);

			modified = true;
		}
		else
			++it;
	}


	if (modified)
	{
		//Recreate index file using index map:
		StructureIndex.close();
		StructureIndex.open(StructureIndexPath, ios::out | ios::trunc);
		if (!StructureIndex)
		{
			std::cerr << ("Could not reopen Structure Index.\n");
			return;
		}
		for (auto it = NormalObjectList.begin(); it != NormalObjectList.end(); ++it)
		{
			StructureIndex << it->first << '\n' << it->second << '\n';
		}
	}

}
}


/*
Plan:
Scan through the index. The first thing the index contains is the list of files
and their sizes in the normal object folder. If a mismatch occurs, a change occured:
.Check if an item was removed. If so, remove the appropriate special copy
.Otherwise, item was created. Process and create new copy.

if the mismatch was in date modified, reprocess.

/////////////////////////////////
Index file structure:
Normal path
Normal date modified
/////////////////////////////////

/////////////////////////////////
New binary object file structure:
Header				  - vmfheader
Vertices			  - vertex3D
Indices				  - sizeof (ElementIndexType);
/////////////////////////////////
*/