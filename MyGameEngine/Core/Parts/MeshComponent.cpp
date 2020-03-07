#include "MeshComponent.h"

void MeshComponent::Load(const char* filename)
{
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
}
