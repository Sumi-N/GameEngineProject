#include <Core/Utility/Result.h>
#include <Core/Utility/Array.h>
#include <Core/Utility/File.h>

#include <External/SPIRV-Reflect/spirv_reflect.h>

using namespace Tempest;

const String path_in = INT_SHADER_PATH;
const String path_out = BIN_SHADER_PATH;

int main()
{
	String fullpath = "..\\..\\" + path_in;
	Array<String> filepaths = File::GetAllFilePathsBelowTheDirectory(fullpath);

	for (auto i_entry = filepaths.Begin(); i_entry != filepaths.End(); i_entry++)
	{
		String o_entry = File::ReplaceExtension(*i_entry, "autogen.h");
		String o_filename = File::GetFileName(o_entry);

		String copy_from_path = "..\\..\\" + path_in + *i_entry;
		String copy_to_path = "..\\..\\" + path_out + "shaderinfo\\" + o_filename;

		{
			File out(copy_to_path, File::Format::BinaryWrite);

			size_t data_size = 0;
			size_t index_size = 0;

			RETURN_IFNOT_SUCCESS(out.Open());

			RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(&data_size), sizeof(size_t)));
			RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(&index_size), sizeof(size_t)));

			out.Close();
		}

		/*if (result != ResultValue::Success)
		{
			DEBUG_PRINT("Failed to convert mesh %s", copy_from_path.c_str());
		}*/
	}

	/*const char* shader_path = "";
	size_t shader_size;
	Array<char> shader_binary;

	File in(shader_path, File::Format::BinaryRead);
	RETURN_IFNOT_SUCCESS(in.Open());

	shader_size = in.GetFileSize();
	shader_binary.Resize(shader_size);
	RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(shader_binary.Data()), shader_size));

	in.Close();*/

	return 0;
}