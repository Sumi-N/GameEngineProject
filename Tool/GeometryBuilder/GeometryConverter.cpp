#include <fstream>
#include <iostream>

#include "GeometryConverter.h"

std::vector<MeshData> GeometryConverter::data;
std::vector<int>      GeometryConverter::index;

GeometryConverter::GeometryConverter()
{

}

GeometryConverter::~GeometryConverter()
{

}

bool GeometryConverter::ReadGeometry(std::filesystem::path const i_filepath)
{
	bool result;
	std::string extention = i_filepath.filename().extension().string();
	std::transform(extention.begin(), extention.end(), extention.begin(), ::tolower);

	if (extention == ".obj")
	{
		result = ReadOBJ(i_filepath);
	}
	else if (extention == ".fbx")
	{
		result = ReadFBX(i_filepath);
	}
	else
	{
		DEBUG_ASSERT(false);
	}

	return result;
}

bool GeometryConverter::WriteBinary(std::filesystem::path const o_filepath)
{
	//Create the file if directory doesn't exist
	if (!std::filesystem::exists(o_filepath.parent_path()))
	{
		std::filesystem::create_directories(o_filepath.parent_path());
	}

	std::ofstream outfile(o_filepath.c_str(), std::ifstream::binary);

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

bool GeometryConverter::ReadOBJ(std::filesystem::path const i_filepath)
{
	if (!data.empty())
	{
		data.clear();
	}

	if (!index.empty())
	{
		index.clear();
	}

	cy::TriMesh tmpdata;

	if (!tmpdata.LoadFromFileObj(i_filepath.string().c_str(), true))
	{
		return false;
	}
	tmpdata.ComputeNormals();

	// Get number of point data
	unsigned int facenum = tmpdata.NF();
	unsigned int vertnum = tmpdata.NV();
	unsigned int normalnum = tmpdata.NVN();


	// Map All Data
	std::map<unsigned, cy::Point3f> vertexMap;
	std::map<unsigned, cy::Point3f> normalMap;
	std::map<unsigned, cy::Point2f> textCoordMap;
	for (size_t i = 0; i < facenum; i++)
	{
		// Vertex Face
		cy::TriMesh::TriFace vertexFace = tmpdata.F((int)i);
		vertexMap[vertexFace.v[0]] = tmpdata.V(vertexFace.v[0]);
		vertexMap[vertexFace.v[1]] = tmpdata.V(vertexFace.v[1]);
		vertexMap[vertexFace.v[2]] = tmpdata.V(vertexFace.v[2]);

		// Normal Face
		if (tmpdata.HasNormals())
		{
			cy::TriMesh::TriFace normalFace = tmpdata.FN((int)i);
			normalMap[normalFace.v[0]] = tmpdata.VN(normalFace.v[0]);
			normalMap[normalFace.v[1]] = tmpdata.VN(normalFace.v[1]);
			normalMap[normalFace.v[2]] = tmpdata.VN(normalFace.v[2]);
		}

		// Texture Face
		if (tmpdata.HasTextureVertices())
		{
			cy::TriMesh::TriFace textureFace = tmpdata.FT((int)i);
			textCoordMap[textureFace.v[0]] = cy::Point2f(tmpdata.VT(textureFace.v[0]));
			textCoordMap[textureFace.v[1]] = cy::Point2f(tmpdata.VT(textureFace.v[1]));
			textCoordMap[textureFace.v[2]] = cy::Point2f(tmpdata.VT(textureFace.v[2]));
		}
	}

	for (size_t i = 0; i < facenum; i++)
	{
		unsigned indexOffset = (unsigned int)i * 3;

		index.push_back(indexOffset + 0);
		index.push_back(indexOffset + 1);
		index.push_back(indexOffset + 2);

		MeshData tmp1, tmp2, tmp3;

		cy::TriMesh::TriFace vertexFace = tmpdata.F((int)i);

		tmp1.vertex.x = vertexMap[vertexFace.v[0]].x;
		tmp1.vertex.y = vertexMap[vertexFace.v[0]].y;
		tmp1.vertex.z = vertexMap[vertexFace.v[0]].z;

		tmp2.vertex.x = vertexMap[vertexFace.v[1]].x;
		tmp2.vertex.y = vertexMap[vertexFace.v[1]].y;
		tmp2.vertex.z = vertexMap[vertexFace.v[1]].z;

		tmp3.vertex.x = vertexMap[vertexFace.v[2]].x;
		tmp3.vertex.y = vertexMap[vertexFace.v[2]].y;
		tmp3.vertex.z = vertexMap[vertexFace.v[2]].z;

		if (tmpdata.HasNormals())
		{
			cy::TriMesh::TriFace normalFace = tmpdata.FN((int)i);

			tmp1.normal.x = normalMap[normalFace.v[0]].x;
			tmp1.normal.y = normalMap[normalFace.v[0]].y;
			tmp1.normal.z = normalMap[normalFace.v[0]].z;

			tmp2.normal.x = normalMap[normalFace.v[1]].x;
			tmp2.normal.y = normalMap[normalFace.v[1]].y;
			tmp2.normal.z = normalMap[normalFace.v[1]].z;

			tmp3.normal.x = normalMap[normalFace.v[2]].x;
			tmp3.normal.y = normalMap[normalFace.v[2]].y;
			tmp3.normal.z = normalMap[normalFace.v[2]].z;
		}

		if (tmpdata.HasTextureVertices())
		{
			cy::TriMesh::TriFace textureFace = tmpdata.FT((int)i);

			tmp1.uv.x = textCoordMap[textureFace.v[0]].x;
			tmp1.uv.y = textCoordMap[textureFace.v[0]].y;

			tmp2.uv.x = textCoordMap[textureFace.v[1]].x;
			tmp2.uv.y = textCoordMap[textureFace.v[1]].y;

			tmp3.uv.x = textCoordMap[textureFace.v[2]].x;
			tmp3.uv.y = textCoordMap[textureFace.v[2]].y;
		}

		data.push_back(tmp1);
		data.push_back(tmp2);
		data.push_back(tmp3);
	}

	for (size_t i = 0; i < facenum; i++)
	{
		Vec3f pos1 = data[index[3 * i + 0]].vertex;
		Vec3f pos2 = data[index[3 * i + 1]].vertex;
		Vec3f pos3 = data[index[3 * i + 2]].vertex;

		Vec3f edge1 = pos2 - pos1;
		Vec3f edge2 = pos3 - pos1;

		Vec2f uv1 = data[index[3 * i + 0]].uv;
		Vec2f uv2 = data[index[3 * i + 1]].uv;
		Vec2f uv3 = data[index[3 * i + 2]].uv;

		Vec2f deltauv1 = uv2 - uv1;
		Vec2f deltauv2 = uv3 - uv1;

		float f = 1.0f / (deltauv1.x * deltauv2.y - deltauv2.x * deltauv1.y);

		Vec3f tangent;
		tangent.x = f * (deltauv2.y * edge1.x - deltauv1.y * edge2.x);
		tangent.y = f * (deltauv2.y * edge1.y - deltauv1.y * edge2.y);
		tangent.z = f * (deltauv2.y * edge1.z - deltauv1.y * edge2.z);
		tangent.Normalize();

		Vec3f bitangent;
		bitangent.x = f * (-deltauv2.x * edge1.x + deltauv1.x * edge2.x);
		bitangent.y = f * (-deltauv2.x * edge1.y + deltauv1.x * edge2.y);
		bitangent.z = f * (-deltauv2.x * edge1.z + deltauv1.x * edge2.z);
		bitangent.Normalize();

		data[index[3 * i + 0]].tangent = tangent;
		data[index[3 * i + 0]].bitangent = bitangent;

		data[index[3 * i + 1]].tangent = tangent;
		data[index[3 * i + 1]].bitangent = bitangent;

		data[index[3 * i + 2]].tangent = tangent;
		data[index[3 * i + 2]].bitangent = bitangent;
	}

	return true;
}

bool GeometryConverter::ReadFBX(std::filesystem::path const i_filepath)
{
	return false;
}

