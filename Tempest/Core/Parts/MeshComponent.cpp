#include "MeshComponent.h"
#include "ResourceManagement/AssetManager.h"

namespace Tempest
{
	void MeshComponent::ReplaceWithDummyMesh(OwningPointer<Resource::Mesh>& o_mesh)
	{
		o_mesh = OwningPointer<Resource::Mesh>::Create(o_mesh);
		o_mesh->data.resize(6);
		o_mesh->index.resize(6);
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

	bool MeshComponent::Load(const char* i_filename)
	{
		if (IsLoaded())
		{
			DEBUG_PRINT("The data in this mesh is cleaned");
			CleanMesh();
		}

		mesh = AssetManager<Resource::Mesh>::Load(i_filename);

		if (mesh == nullptr)
		{
			DEBUG_PRINT("Failed to load the mesh data %s, replaced it with dummy mesh", i_filename);
			ReplaceWithDummyMesh(mesh);

			return true;
		}

		return true;
	}

	void MeshComponent::SetMaterial(MaterialAttribute* i_material)
	{
		material_attribute = i_material;
	}

	void MeshComponent::SetMaterial(OwningPointer<MaterialAttribute> i_material)
	{
		material_attribute = i_material;
	}

	bool MeshComponent::IsLoaded() 
	{
		if (mesh)
		{
			if (!mesh->data.empty() || !mesh->index.empty())
			{
				return true;
			}
		}

		return false;
	}

	void MeshComponent::CleanMesh()
	{	
		mesh->data.clear();
		mesh->index.clear();
	}
}