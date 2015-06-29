#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#ifdef OVERCAST_DLL
#define MYLIBRARY_EXPORT __declspec(dllexport)
#else
#define MYLIBRARY_EXPORT __declspec(dllimport)
#endif

namespace FileSystem
{
#define CUSTOM_OBJECT_FORMAT "vmf"
#define COLLISION_KEYWORD "_COLLIDE"

	bool MYLIBRARY_EXPORT isModel(std::string& name, bool vmf = false);

	void MYLIBRARY_EXPORT toSpecialPath(std::string* path);
	bool MYLIBRARY_EXPORT processModel(const char fileLocation[], const char* destination = NULL); //If destination==NULL, uses automatic Overcast path.

	void MYLIBRARY_EXPORT CommenceModelFileSystem();

}


/*
Plan:
Scan through the index. The first thing the index contains is the list of files
and their sizes in the normal object folder. If a mismatch occurs, a change occured:
.Check if an item was removed. If so, remove the appropriate special copy
.Otherwise, item was created. Process and create new copy.

if the mismatch was in size, OR DATE MODIFIED, reprocess.

/////////////////////////////////
Index file structure:
Normal path
Normal size
Normal date modified
#
Special path
/////////////////////////////////

/////////////////////////////////
New binary object file structure:
Vert count		      - uint
Vet collision count   - uint
UV count		      - uint
Normal count	      - uint
Indices count		  - uint
Vert values		      - float
Vert collision values - float
UV values		      - float
Normal values	   	  - float
Indices				  - sizeof (ElementIndexType);
/////////////////////////////////

/////////////////////////////////
Load special object:
Reserve vert and uv
Traverse vert and grab data into vector
Traverse UV and grab data into vector
Generate normals
/////////////////////////////////

/////////////////////////////////
Save special object:
Just read .obj using old method.
Save vert count
Save UV count
Write all vertex values
Write all UV values
/////////////////////////////////
*/