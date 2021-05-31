#include <Tool/GeometryBuilder/GeometryConverter.h>
#include <Tool/GeometryBuilder/FileAssistanceSystem.h>
#include <ResourceManagement/MeshLoader.h>

#define INTDATA "sphere.obj"
#define BINDAT  "sphere.tmd"

FileAssistanceSystem fas;
GeometryConverter obj;

int main()
{

	fas.input_dir = "../../" INT_MESH_PATH;
	fas.output_dir = "../../" BIN_MESH_PATH;

	fas.GetInputFiles();
  	fas.GetOutputPaths();

	std::filesystem::path infilepath = fas.input_dir.string() + std::filesystem::path("SK_PlayerCharacter.fbx").string();

	obj.ReadGeometry(infilepath);

	size_t data_size = GeometryConverter::data.size();

	std::filesystem::path outfilepath = fas.output_dir.string() + std::filesystem::path("SK_PlayerCharacter.tmd").string();
	obj.WriteBinary(outfilepath);

	return 0;
}