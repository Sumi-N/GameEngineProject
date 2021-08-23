#pragma once

#include "Define.h"
#include "Component.h"
#include "MaterialAttribute.h"
#include "TextureAttribute.h"

namespace Tempest
{

	class MeshComponent : public Component
	{
	public:
		MeshComponent() = default;
		~MeshComponent() = default;

		OwningPointer<Resource::Mesh> mesh;

		ObservingPointer<Object> owner;
		OwningPointer<MaterialAttribute> material_attribute;		

		Mat4f model_mat;
		Mat4f model_inverse_transpose_mat;

		static  void ReplaceWithDummyMesh(OwningPointer<Resource::Mesh>&);
		virtual void Boot() override;
		virtual void Init() override;
		virtual void Update(float i_dt) override;
		virtual void CleanUp() override;

		Result Load(const char* filename);
		void SetMaterial(MaterialAttribute*);
		void SetMaterial(OwningPointer<MaterialAttribute>);

	private:
		bool IsLoaded();
		void CleanMesh();
	};

}
