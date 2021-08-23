#include "GeometryConverter.h"
#include <Utility/File.h>

using namespace Tempest;

const String path_in = INT_MESH_PATH;
const String path_out = BIN_MESH_PATH;

int main()
{
	String fullpath = "..\\..\\" + path_in;

	Array<String> filepaths = File::GetAllFilePathsBelowTheDirectory(fullpath);

	for (auto i_entry = filepaths.Begin(); i_entry != filepaths.End(); i_entry++)
	{
		String o_entry = File::ReplaceExtension(*i_entry, "tmd");

		String copy_from_path = "..\\..\\" + path_in + *i_entry;
		String copy_to_path = "..\\..\\" + path_out + o_entry;
		
		Result result = GeometryConverter::ConvertGeometry(ConversionType::Mesh, copy_from_path.c_str(), copy_to_path.c_str());

		if (result != ResultValue::Success)
		{
			DEBUG_PRINT("Failed to convert texture %s", copy_from_path.c_str());
		}
	}

	return 0;
}