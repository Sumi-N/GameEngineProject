#include <fstream>
#include <iostream>
#include <filesystem>

#include "Importer.h"

std::string Importer::IntDir = "../../" INT_MESH_PATH;
std::string Importer::BinDir = "../../" BIN_MESH_PATH;
std::vector<MeshData> Importer::data;
std::vector<int>      Importer::index;

Importer::Importer()
{

}

Importer::~Importer()
{

}

bool Importer::WriteToAFileAsBinary(std::string o_filename)
{
	//Create the file if either directory or file doesn't exist
	std::filesystem::path path{ o_filename };
	std::filesystem::create_directories(path.parent_path());

	std::ofstream outfile(o_filename.c_str(), std::ifstream::binary);

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

