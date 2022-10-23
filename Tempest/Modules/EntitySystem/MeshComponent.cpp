#include "MeshComponent.h"
#include "ResourceManagement/AssetManager.h"

namespace Tempest
{
	void ReplaceWithDummyMesh(OwningPointer<Mesh>& o_mesh)
	{
		o_mesh = OwningPointer<Mesh>::Create(o_mesh);
		o_mesh->data.Resize(6);
		o_mesh->index.Resize(6);
		o_mesh->data[0].vertex = Vec3f( 10,  10, 0);
		o_mesh->data[1].vertex = Vec3f(-10, -10, 0);
		o_mesh->data[2].vertex = Vec3f( 10, -10, 0);
		o_mesh->data[3].vertex = Vec3f( 10,  10, 0);
		o_mesh->data[4].vertex = Vec3f(-10,  10, 0);
		o_mesh->data[5].vertex = Vec3f(-10, -10, 0);

		o_mesh->index[0] = 0;
		o_mesh->index[1] = 1;
		o_mesh->index[2] = 2;
		o_mesh->index[3] = 3;
		o_mesh->index[4] = 4;
		o_mesh->index[5] = 5;
	}

	void MeshComponent::Boot()
	{
		Load();
	}

	void MeshComponent::Init()
	{
	}

	void MeshComponent::Update(float i_dt)
	{
		Mat4f translation_mat = Mat4f::Translate(owner->pos);
		Mat4f rotation_mat_x = Mat4f::Roll(owner->rot.x);
		Mat4f rotation_mat_y = Mat4f::Pitch(owner->rot.y);
		Mat4f rotation_mat_z = Mat4f::Yaw(owner->rot.z);
		Mat4f translation_scale = Mat4f::Scale(owner->scale);

		model_mat = translation_mat * rotation_mat_z * rotation_mat_y * rotation_mat_x * translation_scale;
		model_inverse_transpose_mat = Mat4f::Transpose(Mat4f::Inverse(model_mat));
	}

	void MeshComponent::CleanUp()
	{

	}

	void MeshComponent::RegisterMesh(const char* i_path)
	{
		DEBUG_ASSERT(i_path);
		mesh_path = i_path;
	}

	Result MeshComponent::Load()
	{
		if (IsLoaded())
		{
			DEBUG_PRINT("The data in this mesh is cleaned");
			CleanMesh();
		}

		if (File::GetExtensionName(mesh_path) == ".tm")
		{
			mesh_type = MeshType::Mesh;
			mesh = AssetManager<Mesh>::Load(mesh_path);
		}
		else if (File::GetExtensionName(mesh_path) == ".tsm")
		{
			mesh_type = MeshType::SkeletonMesh;
			mesh = static_cast<Owner<Mesh>>(AssetManager<SkeletonMesh>::Load(mesh_path));
		}

		if (!mesh)
		{
			DEBUG_PRINT("Failed to load the mesh data %s, replaced it with dummy mesh", mesh_path);
			ReplaceWithDummyMesh(mesh);

			return ResultValue::FileDoesntExist;
		}

		DEBUG_PRINT("Succeed loading the mesh data %s", mesh_path);
		return ResultValue::Success;
	}

	bool MeshComponent::IsLoaded()
	{
		if (mesh)
		{
			if (!mesh->data.Empty() || !mesh->index.Empty())
			{
				return true;
			}
		}

		return false;
	}

	void MeshComponent::CleanMesh()
	{
		mesh->data.Clear();
		mesh->index.Clear();
	}
}