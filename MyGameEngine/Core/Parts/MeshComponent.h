#pragma once

#include "Define.h"
#include "Component.h"
#include "MaterialAttribute.h"
#include "TextureAttribute.h"

//// Forward declaration
//class SceneProxy;

__declspec(align(16)) struct MeshData
{
	Vec3f vertex;
	Vec3f normal;
	Vec2f uv;
	Vec2f padding; //For alignment purpose
	Vec3f tangent;
	Vec3f bitangent;
};

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

	void Load(const char* filename);
	void Boot() override;
	void Init() override;
	void Update(float i_dt) override;
	void CleanUp() override;

	void SetMaterial(MaterialAttribute *);
	void SetMaterial(OwningPointer<MaterialAttribute>);
};

