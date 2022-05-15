#include "GeometryConverter.h"
#include <Utility/File.h>

using namespace Tempest;

const String path_in = INT_MESH_PATH;
const String path_out = BIN_MESH_PATH;

int main()
{
	{
		String fullpath = "..\\..\\" + path_in;

		Array<String> filepaths = File::GetAllFilePathsBelowTheDirectory(fullpath);

		for (auto i_entry = filepaths.Begin(); i_entry != filepaths.End(); i_entry++)
		{
			String o_entry = File::ReplaceExtension(*i_entry, "tm");

			String copy_from_path = "..\\..\\" + path_in + *i_entry;
			String copy_to_path = "..\\..\\" + path_out + o_entry;

			Result result = GeometryConverter::ConvertMesh(copy_from_path.c_str(), copy_to_path.c_str());

			if (result != ResultValue::Success)
			{
				DEBUG_PRINT("Failed to convert mesh %s", copy_from_path.c_str());
			}
		}
	}

	////-------- Skeleton Animation ----------------

	{
		String copy_from_path = "..\\..\\" + path_in + "xbot.fbx";
		String filename = File::GetFileName(copy_from_path);
		String o_mesh = File::ReplaceExtension(filename, "tsm");
		String o_skeleton = File::ReplaceExtension(filename, "ts");
		String copy_to_path_mesh = "..\\..\\" + path_out + o_mesh;
		String copy_to_path_skeleton = "..\\..\\" + path_out + o_skeleton;

		Result result = GeometryConverter::ConvertSkeletonAndSkeletonMesh(copy_from_path.c_str(), copy_to_path_skeleton.c_str(), copy_to_path_mesh.c_str());

		if (result != ResultValue::Success)
		{
			DEBUG_PRINT("Failed to convert skeleton mesh %s", copy_from_path.c_str());
		}
	}

	//-------- Animation Clip ----------------

	{
		String copy_from_path = "..\\..\\" + path_in + "RumbaDancing.fbx";
		String filename = File::GetFileName(copy_from_path);
		String o_entry = File::ReplaceExtension(filename, "tac");
		String copy_to_path = "..\\..\\" + path_out + o_entry;

		Result result = GeometryConverter::ConvertAnimationClip(copy_from_path.c_str(), copy_to_path.c_str());

		if (result != ResultValue::Success)
		{
			DEBUG_PRINT("Failed to convert animation clip %s", copy_from_path.c_str());
		}
	}

	return 0;
}