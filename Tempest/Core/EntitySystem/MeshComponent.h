#pragma once

#include "Define.h"
#include "Component.h"
#include <ResourceManagement/ResourceData.h>

namespace Tempest
{

	class MeshComponent : public Component
	{
	public:
		MeshComponent() = default;
		~MeshComponent() = default;		
		
		const char* mesh_path;
		Resource::MeshType mesh_type;
		Owner<Resource::Mesh> mesh;

		Mat4f model_mat;
		Mat4f model_inverse_transpose_mat;
		
		virtual void Boot() override;
		virtual void Init() override;
		virtual void Update(float i_dt) override;
		virtual void CleanUp() override;

		void RegisterMesh(const char* i_path);
		Result Load();

	private:
		bool IsLoaded();
		void CleanMesh();
	};

}
