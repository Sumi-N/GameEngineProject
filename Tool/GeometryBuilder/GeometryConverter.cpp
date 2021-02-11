#include <fstream>
#include <iostream>

#include "GeometryConverter.h"

std::vector<MeshData> GeometryConverter::data;
std::vector<int>      GeometryConverter::index;

GeometryConverter::GeometryConverter()
{

}

GeometryConverter::~GeometryConverter()
{

}

bool GeometryConverter::WriteBinary(std::filesystem::path const io_filepath)
{
	//Create the file if directory doesn't exist
	if (!std::filesystem::exists(io_filepath.parent_path()))
	{
		std::filesystem::create_directories(io_filepath.parent_path());
	}

	std::ofstream outfile(io_filepath.c_str(), std::ifstream::binary);

	if (!outfile)
	{
		DEBUG_ASSERT(false);
		return false;
	}

	size_t data_size = data.size();
	size_t index_size = index.size();

	if (data_size == 0 || index_size == 0)
	{
		return false;
	}

	outfile.write(reinterpret_cast<char*>(&data_size), sizeof(size_t));
	outfile.write(reinterpret_cast<char*>(&index_size), sizeof(size_t));

	outfile.write(reinterpret_cast<char*>(data.data()), data_size * sizeof(MeshData));
	outfile.write(reinterpret_cast<char*>(index.data()), index_size * sizeof(int));

	outfile.close();

	return true;
}

