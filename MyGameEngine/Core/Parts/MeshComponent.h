#pragma once

#include "Define.h"
#include "Component.h"
#include "MaterialAttribute.h"

//// Forward declaration
//class SceneProxy;

struct MeshData
{
	Vec3f vertex;
	Vec3f normal;
	Vec2f uv;
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
	void Init() override;
	void Update(float i_dt) override;
	void CleanUp() override;

	void SetMaterial(MaterialAttribute *);
};

