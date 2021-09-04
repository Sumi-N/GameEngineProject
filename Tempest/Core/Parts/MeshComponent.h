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
		OwningPointer<Resource::Mesh> mesh;

		ObservingPointer<Object> owner;			

		Mat4f model_mat;
		Mat4f model_inverse_transpose_mat;

		static  void ReplaceWithDummyMesh(OwningPointer<Resource::Mesh>&);
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
