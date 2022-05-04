#pragma once

#include "Define.h"
#include "Component.h"

namespace Tempest
{

	class MeshComponent : public Component
	{
	public:
		MeshComponent() = default;
		~MeshComponent() = default;
		
		enum class MeshType : uint8_t
		{
			Mesh,
			SkeletonMesh,
		};

		MeshType type;
		Owner<Resource::Mesh> mesh;

		Mat4f model_mat;
		Mat4f model_inverse_transpose_mat;

		static  void ReplaceWithDummyMesh(Owner<Resource::Mesh>&);
		virtual void Boot() override;
		virtual void Init() override;
		virtual void Update(float i_dt) override;
		virtual void CleanUp() override;

		Result Load(const char* i_filename);

	private:
		bool IsLoaded();
		void CleanMesh();
	};

}
