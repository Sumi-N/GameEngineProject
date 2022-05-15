#include "TextureConverter.h"
#include <Utility/File.h>

using namespace Tempest;

const String path_in = INT_TEXTURE_PATH;
const String path_out = BIN_TEXTURE_PATH;

int main()
{
	String fullpath = "..\\..\\" + path_in;

	Array<String> filepaths = File::GetAllFilePathsBelowTheDirectory(fullpath);

	for (auto i_entry = filepaths.Begin(); i_entry != filepaths.End(); i_entry++)
	{
		String o_entry = File::ReplaceExtension(*i_entry, "tt");

		String copy_from_path = "..\\..\\" + path_in + *i_entry;
		String copy_to_path   = "..\\..\\" + path_out + o_entry;


		Result result;
		result = TextureConverter::ConvertTexture(copy_from_path.c_str(), copy_to_path.c_str());

		if (result != ResultValue::Success)
		{
			DEBUG_PRINT("Failed to convert texture %c", *i_entry);
			//DEBUG_ASSERT(false);
		}
	}

	return 0;
}