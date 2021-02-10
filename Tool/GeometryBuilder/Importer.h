#pragma once
#include <vector>

#include <ResourceManagement/ResourceData.h>

class Importer
{
public:
	Importer();
	~Importer();

	static std::string IntDir;
	static std::string BinDir;
	static std::vector<MeshData> data;
	static std::vector<int>      index;

	virtual bool LoadMesh(std::string) = 0;

	bool WriteToAFileAsBinary(std::string);
};

