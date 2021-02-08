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

		// Index data
		std::vector<MeshData> data;
		std::vector<int>   index;

		Mat4f model_mat;
		Mat4f model_inverse_transpose_mat;

		bool Load(const char* filename);
		void Boot() override;
		void Init() override;
		void Update(float i_dt) override;
		void CleanUp() override;

		void SetMaterial(MaterialAttribute*);
		void SetMaterial(OwningPointer<MaterialAttribute>);
	};

}
