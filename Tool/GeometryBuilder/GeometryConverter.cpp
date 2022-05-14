#include "GeometryConverter.h"
#include "FBXLoader.h"

using namespace Tempest::Resource;

Tempest::Result GeometryConverter::ConvertMesh(const char* i_filename, const char* o_filename)
{
	Array<MeshPoint> data;
	Array<int> index;

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
	RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(data.Data()), data_size * sizeof(MeshPoint)));
	RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(index.Data()), index_size * sizeof(int)));

	out.Close();

	return Tempest::ResultValue::Success;
}

Tempest::Result GeometryConverter::ConvertSkeletonAndSkeletonMesh(const char* i_filename, const char* o_file_skeleton, const char* o_file_mesh)
{
	Skeleton skeleton;
	Array<SkeletonMeshPoint> skeleton_mesh;
	Array<int>      index;

	Tempest::File in(i_filename, Tempest::File::Format::BinaryRead);

	if (in.GetExtensionName() == ".fbx")
	{
		RETURN_IFNOT_SUCCESS(ReadSkeletonMesh(ExtensionType::FBX, i_filename, skeleton, skeleton_mesh, index));
	}

	{
		Tempest::File out(o_file_skeleton, Tempest::File::Format::BinaryWrite);

		RETURN_IFNOT_SUCCESS(out.Open());

		size_t num_joint = skeleton.joints.Size();
		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(&num_joint), sizeof(size_t)));
		
		for (int i = 0; i < num_joint; i++)
		{
			RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(&skeleton.joints[i]), sizeof(Joint)));
		}

		out.Close();
	}

	{
		Tempest::File out(o_file_mesh, Tempest::File::Format::BinaryWrite);

		size_t data_size = skeleton_mesh.Size();
		size_t index_size = index.Size();

		if (data_size == 0 || index_size == 0)
		{
			return Tempest::ResultValue::Failure;
		}

		RETURN_IFNOT_SUCCESS(out.Open());

		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(&data_size), sizeof(size_t)));
		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(&index_size), sizeof(size_t)));
		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(skeleton_mesh.Data()), data_size * sizeof(SkeletonMeshPoint)));
		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(index.Data()), index_size * sizeof(int)));

		out.Close();
	}

	return Tempest::ResultValue::Success;
}

Tempest::Result GeometryConverter::ConvertAnimationClip(const char* i_filename, const char* o_filename)
{
	AnimationClip animation_clip;

	Tempest::File in(i_filename, Tempest::File::Format::BinaryRead);

	if (in.GetExtensionName() == ".fbx")
	{
		RETURN_IFNOT_SUCCESS(ReadAnimationClip(ExtensionType::FBX, i_filename, animation_clip));
	}

	Tempest::File out(o_filename, Tempest::File::Format::BinaryWrite);

	size_t num_samples = animation_clip.samples.Size();
	size_t num_joints = animation_clip.samples[0].jointposes.Size();	

	if (num_samples == 0)
	{
		return Tempest::ResultValue::Failure;
	}

	RETURN_IFNOT_SUCCESS(out.Open());

	RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(&num_samples), sizeof(size_t)));
	RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(&num_joints), sizeof(size_t)));

	for (int i = 0; i < num_samples; i++)
	{
		RETURN_IFNOT_SUCCESS(out.Write(static_cast<void*>(animation_clip.samples[i].jointposes.Data()), num_joints * sizeof(JointPose)));
	}

	out.Close();

	return Tempest::ResultValue::Success;
}

Tempest::Result GeometryConverter::ReadMesh(ExtensionType i_extension, const char* i_filename, Array<MeshPoint>& o_data, Array<int>& o_index)
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
			for (size_t j = 0; j < 3; j++)
			{				
				vertexMap[vertexFace.v[j]] = tmpdata.V(vertexFace.v[j]);				
			}

			// Normal Face
			if (tmpdata.HasNormals())
			{
				cy::TriMesh::TriFace normalFace = tmpdata.FN((int)i);
				for (size_t j = 0; j < 3; j++)
				{
					normalMap[normalFace.v[j]] = tmpdata.VN(normalFace.v[j]);					
				}
			}

			// Texture Face
			if (tmpdata.HasTextureVertices())
			{
				cy::TriMesh::TriFace textureFace = tmpdata.FT((int)i);
				for (size_t j = 0; j < 3; j++)
				{
					textCoordMap[textureFace.v[j]] = cy::Point2f(tmpdata.VT(textureFace.v[j]));					
				}
			}
		}

		for (size_t i = 0; i < facenum; i++)
		{
			unsigned indexOffset = (unsigned int)i * 3;

			o_index.PushBack(indexOffset + 0);
			o_index.PushBack(indexOffset + 1);
			o_index.PushBack(indexOffset + 2);

			MeshPoint p[3];

			cy::TriMesh::TriFace vertexFace = tmpdata.F((int)i);

			for (size_t j = 0; j < 3; j++)
			{
				p[j].vertex.x = vertexMap[vertexFace.v[j]].x;
				p[j].vertex.y = vertexMap[vertexFace.v[j]].y;
				p[j].vertex.z = vertexMap[vertexFace.v[j]].z;
			}			

			if (tmpdata.HasNormals())
			{
				cy::TriMesh::TriFace normalFace = tmpdata.FN((int)i);

				for (size_t j = 0; j < 3; j++)
				{
					p[j].normal.x = normalMap[normalFace.v[j]].x;
					p[j].normal.y = normalMap[normalFace.v[j]].y;
					p[j].normal.z = normalMap[normalFace.v[j]].z;
				}				
			}

			if (tmpdata.HasTextureVertices())
			{
				cy::TriMesh::TriFace textureFace = tmpdata.FT((int)i);

				for (size_t j = 0; j < 3; j++)
				{
					p[j].uv.x = textCoordMap[textureFace.v[j]].x;
					p[j].uv.y = textCoordMap[textureFace.v[j]].y;
				}				
			}

			o_data.PushBack(p[0]);
			o_data.PushBack(p[1]);
			o_data.PushBack(p[2]);
		}

		for (size_t i = 0; i < facenum; i++)
		{
			Vec3f pos[3];
			pos[0] = o_data[o_index[3 * i + 0]].vertex;
			pos[1] = o_data[o_index[3 * i + 1]].vertex;
			pos[2] = o_data[o_index[3 * i + 2]].vertex;

			Vec3f edge[2];
			edge[0] = pos[1] - pos[0];
			edge[1] = pos[2] - pos[0];

			Vec2f uv[3];
			uv[0] = o_data[o_index[3 * i + 0]].uv;
			uv[1] = o_data[o_index[3 * i + 1]].uv;
			uv[2] = o_data[o_index[3 * i + 2]].uv;

			Vec2f deltauv[2];
			deltauv[0] = uv[1] - uv[0];
			deltauv[1] = uv[2] - uv[0];

			float f = 1.0f / (deltauv[0].x * deltauv[1].y - deltauv[1].x * deltauv[0].y);

			Vec3f tangent;
			tangent.x = f * (deltauv[1].y * edge[0].x - deltauv[0].y * edge[1].x);
			tangent.y = f * (deltauv[1].y * edge[0].y - deltauv[0].y * edge[1].y);
			tangent.z = f * (deltauv[1].y * edge[0].z - deltauv[0].y * edge[1].z);
			tangent.Normalize();

			Vec3f bitangent;
			bitangent.x = f * (-deltauv[1].x * edge[0].x + deltauv[0].x * edge[1].x);
			bitangent.y = f * (-deltauv[1].x * edge[0].y + deltauv[0].x * edge[1].y);
			bitangent.z = f * (-deltauv[1].x * edge[0].z + deltauv[0].x * edge[1].z);
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

Tempest::Result GeometryConverter::ReadSkeletonMesh(ExtensionType i_extension, const char* i_filename, Skeleton& o_skeleton, Array<SkeletonMeshPoint>& o_data, Array<int>& o_index)
{
	if (i_extension == ExtensionType::FBX)
	{
		std::map<String, int> joint_map;

		if (!FBXLoader::Init(i_filename))
		{
			return Tempest::ResultValue::Failure;
		}

		if (!FBXLoader::LoadSkeleton(o_skeleton, joint_map))
		{
			return Tempest::ResultValue::Failure;
		}

		if (!FBXLoader::LoadSkeletonMesh(o_data, o_index, joint_map))
		{
			return Tempest::ResultValue::Failure;
		}

		return Tempest::ResultValue::Success;
	}
	
	return Tempest::ResultValue::Failure;
}

Tempest::Result GeometryConverter::ReadAnimationClip(ExtensionType i_extension, const char* i_filename, AnimationClip& o_animationclip)
{
	if (i_extension == ExtensionType::FBX)
	{
		if (!FBXLoader::Init(i_filename))
		{
			return Tempest::ResultValue::Failure;
		}

		if (!FBXLoader::LoadAnimationClip(o_animationclip))
		{
			return Tempest::ResultValue::Failure;
		}

		return Tempest::ResultValue::Success;
	}

	return Tempest::ResultValue::Failure;
}

Tempest::Result GeometryConverter::MatchBoneStructure(const Skeleton& i_skeleton, AnimationClip& io_animationclip)
{
	return Tempest::ResultValue::Failure;
}
