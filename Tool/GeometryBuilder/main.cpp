#include "GeometryConverter.h"
#include <Utility/File.h>

using namespace Tempest;

const String path_in = INT_MESH_PATH;
const String path_out = BIN_MESH_PATH;

int main()
{
	//String fullpath = "..\\..\\" + path_in;

	//Array<String> filepaths = File::GetAllFilePathsBelowTheDirectory(fullpath);

	//for (auto i_entry = filepaths.Begin(); i_entry != filepaths.End(); i_entry++)
	//{
	//	String o_entry = File::ReplaceExtension(*i_entry, "tmd");

	//	String copy_from_path = "..\\..\\" + path_in + *i_entry;
	//	String copy_to_path = "..\\..\\" + path_out + o_entry;
	//	
	//	Result result = GeometryConverter::ConvertGeometry(ConversionType::Mesh, copy_from_path.c_str(), copy_to_path.c_str());

	//	if (result != ResultValue::Success)
	//	{
	//		DEBUG_PRINT("Failed to convert mesh %s", copy_from_path.c_str());
	//	}
	//}

	{
		String copy_from_path = "..\\..\\" + path_in + "SK_PlayerCharacter.fbx";
		String o_entry1 = File::ReplaceExtension(copy_from_path, "tmd");
		String o_entry2 = File::ReplaceExtension(copy_from_path, "tsm");
		String copy_to_path1 = "..\\..\\" + path_out + o_entry1;
		String copy_to_path2 = "..\\..\\" + path_out + o_entry2;

		Result result = GeometryConverter::ConvertGeometry(ConversionType::SkeletonMesh, copy_from_path.c_str(), copy_to_path.c_str());

		if (result != ResultValue::Success)
		{
			DEBUG_PRINT("Failed to convert skeleton mesh %s", copy_from_path.c_str());
		}
	}

	{
		String copy_from_path = "..\\..\\" + path_in + "Anim_PlayerCharacter_run.fbx";
		String o_entry = File::ReplaceExtension(copy_from_path, "tac");		
		String copy_to_path = "..\\..\\" + path_out + o_entry;		

		Result result = GeometryConverter::ConvertGeometry(ConversionType::AnimationClip, copy_from_path.c_str(), copy_to_path.c_str());

		if (result != ResultValue::Success)
		{
			DEBUG_PRINT("Failed to convert animation clip %s", copy_from_path.c_str());
		}
	}
	
	return 0;
}