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

	virtual bool ReadGeometry(std::filesystem::path const) = 0;

	bool WriteBinary(std::filesystem::path const);
};

