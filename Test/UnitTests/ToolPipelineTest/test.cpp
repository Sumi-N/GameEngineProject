#include "pch.h"

#include <Tool/GeometryBuilder/OBJConverter.h>
#include <Tool/GeometryBuilder/FileAssistanceSystem.h>
#include <ResourceManagement/MeshLoader.h>

#define INTDATA "sphere.obj"
#define BINDAT  "sphere.tmd"

class GeometryBuilderTest : public ::testing::Test
{

protected:

	FileAssistanceSystem fas;
	OBJConverter obj;

	GeometryBuilderTest() {}
	virtual ~GeometryBuilderTest() {}

	virtual void SetUp() override
	{
		fas.input_dir = "../../../" INT_MESH_PATH;
		fas.output_dir = "../../../" BIN_MESH_PATH;

		fas.GetInputFiles();
		fas.GetOutputPaths();
	}

	virtual void TearDown() override
	{
	}

};

TEST_F(GeometryBuilderTest, SetupFileAssistanceSystemTest) {
	fas.input_dir = "../../../" INT_MESH_PATH;
	fas.output_dir = "../../../" BIN_MESH_PATH;

	EXPECT_TRUE(fas.GetInputFiles());
	EXPECT_TRUE(fas.GetOutputPaths());
}

TEST_F(GeometryBuilderTest, ReadOBJTest)
{
	std::filesystem::path filepath = fas.input_dir.string() + std::filesystem::path(INTDATA).string();

	EXPECT_TRUE(obj.ReadGeometry(filepath));

	size_t data_size = GeometryConverter::data.size();

	EXPECT_EQ(data_size, 2880);
}

TEST_F(GeometryBuilderTest, WriteBinaryTest)
{
	std::filesystem::path filepath = fas.output_dir.string() + std::filesystem::path(BINDAT).string();

	EXPECT_TRUE(obj.WriteBinary(filepath));
}

std::vector<MeshData> mesh_data;
std::vector<int> mesh_index;

TEST_F(GeometryBuilderTest, ReadBinaryTest)
{
	std::string pathname = fas.output_dir.string() + std::filesystem::path(BINDAT).string();

	MeshLoader loader;

	EXPECT_TRUE(loader.Load(pathname.c_str(),mesh_data, mesh_index));

	EXPECT_EQ(mesh_data.size(), 2880);
}

TEST_F(GeometryBuilderTest, ConvertAllOBJFileTest)
{
	for (int i = 0; i < fas.output_path.size(); i++)
	{
		std::filesystem::path input_fullpath = fas.input_dir.string() + fas.input_files[i].string();
		EXPECT_TRUE(obj.ReadGeometry(input_fullpath));
	
		EXPECT_TRUE(obj.WriteBinary(fas.output_path[i]));
	}
}