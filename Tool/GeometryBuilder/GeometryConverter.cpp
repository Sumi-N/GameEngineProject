#include "GeometryConverter.h"
#include "FBXLoader.h"

Tempest::Result GeometryConverter::ConvertGeometry(ConversionType i_conversiontype, const char* i_filename, const char* o_filename)
{
	if (i_conversiontype == ConversionType::Mesh)
	{
		Array<Resource::MeshPoint> data;
		Array<int>                 index;

		Tempest::File in(i_filename, Tempest::File::Format::BinaryRead);

		if (in.GetExtensionName() == ".obj")
		{
			RETURN_IFNOT_SUCCESS(ReadMesh(ExtensionType::OBJ, i_filename, data, index));
		}
		else if (in.GetExtensionName() == ".fbx")
		{
			RETURN_IFNOT_SUCCESS(ReadMesh(ExtensionType::FBX, i_filename, data, index));
		}

		Tempest::File out(o_filename, Tempest::File::Format::BinaryWrite);

		size_t data_size = data.Size();
		size_t index_size = index.Size();

		if (data_size == 0 || index_size == 0)
		{
			return Tempest::ResultValue::Failure;
		}

		RETURN_IFNOT_SUCCESS(out.Open());

		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(&data_size), sizeof(size_t)));
		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(&index_size), sizeof(size_t)));
		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(data.Data()), data_size * sizeof(Resource::MeshPoint)));
		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(index.Data()), index_size * sizeof(int)));

		out.Close();

		return Tempest::ResultValue::Success;
	}
	else if (i_conversiontype == ConversionType::SkeletonMesh)
	{
		Array<Resource::SkeletonMeshPoint> data;
		Array<int>                 index;

		Tempest::File in(i_filename, Tempest::File::Format::BinaryRead);

		if (in.GetExtensionName() == ".fbx")
		{
			RETURN_IFNOT_SUCCESS(ReadSkeletonMesh(ExtensionType::FBX, i_filename, data, index));
		}

		Tempest::File out(o_filename, Tempest::File::Format::BinaryWrite);

		size_t data_size = data.Size();
		size_t index_size = index.Size();

		if (data_size == 0 || index_size == 0)
		{
			return Tempest::ResultValue::Failure;
		}

		RETURN_IFNOT_SUCCESS(out.Open());

		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(&data_size), sizeof(size_t)));
		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(&index_size), sizeof(size_t)));
		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(data.Data()), data_size * sizeof(Resource::MeshPoint)));
		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(index.Data()), index_size * sizeof(int)));

		out.Close();

		return Tempest::ResultValue::Success;
	}
	else
	{
		return Tempest::ResultValue::Failure;
	}
}

Tempest::Result GeometryConverter::ReadMesh(ExtensionType i_extension, const char* i_filename, Array<Resource::MeshPoint>& o_data, Array<int>& o_index)
{
	if (!o_data.Empty())
	{
		o_data.Clear();
	}

	if (!o_index.Empty())
	{
		o_index.Clear();
	}

	if (i_extension == ExtensionType::OBJ)
	{
		cy::TriMesh tmpdata;

		if (!tmpdata.LoadFromFileObj(i_filename, true))
		{
			return Tempest::ResultValue::Failure;
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

			o_index.PushBack(indexOffset + 0);
			o_index.PushBack(indexOffset + 1);
			o_index.PushBack(indexOffset + 2);

			Resource::MeshPoint tmp1, tmp2, tmp3;

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

			o_data.PushBack(tmp1);
			o_data.PushBack(tmp2);
			o_data.PushBack(tmp3);
		}

		for (size_t i = 0; i < facenum; i++)
		{
			Vec3f pos1 = o_data[o_index[3 * i + 0]].vertex;
			Vec3f pos2 = o_data[o_index[3 * i + 1]].vertex;
			Vec3f pos3 = o_data[o_index[3 * i + 2]].vertex;

			Vec3f edge1 = pos2 - pos1;
			Vec3f edge2 = pos3 - pos1;

			Vec2f uv1 = o_data[o_index[3 * i + 0]].uv;
			Vec2f uv2 = o_data[o_index[3 * i + 1]].uv;
			Vec2f uv3 = o_data[o_index[3 * i + 2]].uv;

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

			o_data[o_index[3 * i + 0]].tangent = tangent;
			o_data[o_index[3 * i + 0]].bitangent = bitangent;

			o_data[o_index[3 * i + 1]].tangent = tangent;
			o_data[o_index[3 * i + 1]].bitangent = bitangent;

			o_data[o_index[3 * i + 2]].tangent = tangent;
			o_data[o_index[3 * i + 2]].bitangent = bitangent;
		}
	}
	else if (i_extension == ExtensionType::FBX)
	{
		if (!FBXLoader::Init(i_filename))
		{
			return Tempest::ResultValue::Failure;
		}		

		if (!FBXLoader::LoadMesh(o_data, o_index))
		{
			return Tempest::ResultValue::Failure;
		}
	}

	return Tempest::ResultValue::Success;
}

Tempest::Result GeometryConverter::ReadSkeletonMesh(ExtensionType i_extension, const char* i_filename, Array<Resource::SkeletonMeshPoint>& o_data, Array<int>& o_index)
{
	if (i_extension == ExtensionType::FBX)
	{
		if (!FBXLoader::Init(i_filename))
		{
			return Tempest::ResultValue::Failure;
		}

		if (!FBXLoader::LoadSkeletonMesh(o_data, o_index))
		{
			return Tempest::ResultValue::Failure;
		}

		return Tempest::ResultValue::Success;
	}
	
	return Tempest::ResultValue::Failure;
}
