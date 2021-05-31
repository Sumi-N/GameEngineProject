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
		ObservingPointer<Object> owner;
		OwningPointer<MaterialAttribute> material;

		std::vector<Resource::Mesh> data;
		std::vector<int>   index;

		Mat4f model_mat;
		Mat4f model_inverse_transpose_mat;

		virtual void Boot() override;
		virtual void Init() override;
		virtual void Update(float i_dt) override;
		virtual void CleanUp() override;

		bool Load(const char* filename);
		void SetMaterial(MaterialAttribute*);
		void SetMaterial(OwningPointer<MaterialAttribute>);

	private:
		bool IsLoaded() const;
		void CleanMesh();
	};

}
