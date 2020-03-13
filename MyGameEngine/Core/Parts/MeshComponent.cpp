#include "MeshComponent.h"
#include "../APIs/GraphicAPI/cyCodeBase/cyTriMesh.h"

void MeshComponent::Load(const char* filename)
{
	/*
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename))
	{
		DEBUG_ASSERT_WITHMESSAGE(false, warn.c_str());
		DEBUG_ASSERT_WITHMESSAGE(false, err.c_str());
	}

	for (const auto& shape : shapes)
	{
		for (const auto& index : shape.mesh.indices)
		{
			MeshData meshdata = {};

			meshdata.vertex = Vec3f
			(
				static_cast<float>(attrib.vertices[3 * index.vertex_index + 0]),
				static_cast<float>(attrib.vertices[3 * index.vertex_index + 1]),
				static_cast<float>(attrib.vertices[3 * index.vertex_index + 2])
			);

			meshdata.normal = Vec3f
			(
				static_cast<float>(attrib.normals[3 * index.vertex_index + 0]),
				static_cast<float>(attrib.normals[3 * index.vertex_index + 1]),
				static_cast<float>(attrib.normals[3 * index.vertex_index + 2])
			);

			meshdata.uv = Vec2f
			(
				static_cast<float>(attrib.texcoords[2 * index.texcoord_index + 0]),
				static_cast<float>(attrib.texcoords[2 * index.texcoord_index + 1])
			);

			data.push_back(meshdata);
			this->index.push_back(index.vertex_index);
		}
	}
	*/

	cy::TriMesh tmpdata;
	tmpdata.LoadFromFileObj(filename, true);

	// Get number of point data
	int facenum = tmpdata.NF();
	int vertnum = tmpdata.NV();
	int normalnum = tmpdata.NVN();

	index.resize(facenum * 3);
	data.resize(vertnum);

	for (int i = 0; i < vertnum; i++)
	{
		// Get normal data
		data[i].vertex.x = tmpdata.V(i).x;
		data[i].vertex.y = tmpdata.V(i).y;
		data[i].vertex.z = tmpdata.V(i).z;
	}

	for (int i = 0; i < facenum; i++)
	{
		// Get index data
		index[3 * i + 0] = tmpdata.F(i).v[0];
		index[3 * i + 1] = tmpdata.F(i).v[1];
		index[3 * i + 2] = tmpdata.F(i).v[2];

		if (tmpdata.NVN() != 0)
		{
			// Sort normal to vertex index
			data[tmpdata.F(i).v[0]].normal.x = tmpdata.VN(tmpdata.FN(i).v[0]).x;
			data[tmpdata.F(i).v[0]].normal.y = tmpdata.VN(tmpdata.FN(i).v[0]).y;
			data[tmpdata.F(i).v[0]].normal.z = tmpdata.VN(tmpdata.FN(i).v[0]).z;
			data[tmpdata.F(i).v[1]].normal.x = tmpdata.VN(tmpdata.FN(i).v[1]).x;
			data[tmpdata.F(i).v[1]].normal.y = tmpdata.VN(tmpdata.FN(i).v[1]).y;
			data[tmpdata.F(i).v[1]].normal.z = tmpdata.VN(tmpdata.FN(i).v[1]).z;
			data[tmpdata.F(i).v[2]].normal.x = tmpdata.VN(tmpdata.FN(i).v[2]).x;
			data[tmpdata.F(i).v[2]].normal.y = tmpdata.VN(tmpdata.FN(i).v[2]).y;
			data[tmpdata.F(i).v[2]].normal.z = tmpdata.VN(tmpdata.FN(i).v[2]).z;
		}

		if (tmpdata.NVT() != 0)
		{
			// Sort uv coordinate to vertex index
			data[tmpdata.F(i).v[0]].uv.x = cy::Point2f(tmpdata.VT(tmpdata.FT(i).v[0])).x;
			data[tmpdata.F(i).v[0]].uv.y = cy::Point2f(tmpdata.VT(tmpdata.FT(i).v[0])).y;
			data[tmpdata.F(i).v[1]].uv.x = cy::Point2f(tmpdata.VT(tmpdata.FT(i).v[1])).x;
			data[tmpdata.F(i).v[1]].uv.y = cy::Point2f(tmpdata.VT(tmpdata.FT(i).v[1])).y;
			data[tmpdata.F(i).v[2]].uv.x = cy::Point2f(tmpdata.VT(tmpdata.FT(i).v[2])).x;
			data[tmpdata.F(i).v[2]].uv.y = cy::Point2f(tmpdata.VT(tmpdata.FT(i).v[2])).y;
		}
	}

}

void MeshComponent::Init()
{

}

void MeshComponent::Update(float i_dt)
{

}

void MeshComponent::CleanUp()
{

}