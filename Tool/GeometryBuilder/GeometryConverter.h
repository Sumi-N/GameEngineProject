#pragma once
#include <vector>
#include <filesystem>

#include <ResourceManagement/ResourceData.h>

class GeometryConverter
{
public:
	GeometryConverter();
	~GeometryConverter();

	static std::vector<MeshData> data;
	static std::vector<int>      index;

	bool ReadGeometry(std::filesystem::path const) ;

	bool WriteBinary(std::filesystem::path const);

private:
	bool ReadOBJ(std::filesystem::path const);
	bool ReadFBX(std::filesystem::path const);
};

