#include "MeshComponent.h"
#include "ResourceManagement/AssetManager.h"

namespace Tempest
{

	bool MeshComponent::Load(const char* i_filename)
	{
		if (IsLoaded())
		{
			DEBUG_PRINT("The data in this mesh is cleaned");
			CleanMesh();
		}

		//mesh = OwningPointer<Resource::Mesh>(pmesh);
		mesh = AssetManager<Resource::Mesh>::Load(i_filename);		
		
		if (mesh == nullptr)
		{
			DEBUG_PRINT("Failed to load the mesh data %s", i_filename);
			return false;
		}

		return true;
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