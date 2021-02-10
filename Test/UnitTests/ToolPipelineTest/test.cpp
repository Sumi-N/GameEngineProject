#include "pch.h"

#include <Tool/GeometryBuilder/OBJImporter.h>
#include <ResourceManagement/MeshLoader.h>

#define INTDATA "sphere.obj"
#define BINDAT  "sphere.tmd"

OBJImporter obj;

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(LoadSphereTest, TestName)
{
	std::string pathname = "../" + Importer::IntDir + INTDATA;

	EXPECT_TRUE(obj.LoadMesh(pathname));

	size_t data_size = Importer::data.size();

	EXPECT_EQ(data_size, 2880);
}

TEST(WriteBinaryTest, TestName)
{
	std::string pathname = "../" + Importer::BinDir + INTDATA;

	EXPECT_TRUE(obj.WriteToAFileAsBinary(pathname));
}

std::vector<MeshData> mesh_data;
std::vector<int> mesh_index;

TEST(ReadBinaryTest, TestName)
{
	std::string pathname = "../" + Importer::BinDir + BINDAT;

	MeshLoader loader;

	EXPECT_TRUE(loader.Load(pathname.c_str(),mesh_data, mesh_index));

	EXPECT_EQ(mesh_data.size(), 2880);
}