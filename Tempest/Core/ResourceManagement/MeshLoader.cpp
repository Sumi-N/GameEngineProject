#include "MeshLoader.h"
#include <iostream>
#include <fstream>

namespace Tempest
{
	Result MeshLoader::Load(const char* o_filepath, std::vector<MeshData>& o_data, std::vector<int>& o_index)
	{
		std::ifstream infile(o_filepath, std::ios::out | std::ios::binary);

		if (!infile)
		{
			return ResultValue::Failure;
		}

		size_t data_size;
		size_t index_size;
		infile.read(reinterpret_cast<char*>(&data_size), sizeof(size_t));
		infile.read(reinterpret_cast<char*>(&index_size), sizeof(size_t));

		o_data.resize(data_size);
		o_index.resize(index_size);

		infile.read(reinterpret_cast<char*>(o_data.data()), data_size * sizeof(MeshData));
		infile.read(reinterpret_cast<char*>(o_index.data()), index_size * sizeof(MeshData));

		infile.close();

		return ResultValue::Success;
	}
}
