#pragma once

#include "Define.h"
#include "Component.h"

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
	std::vector<MeshData> data;
	std::vector<int>   index;

	Mat4f model_mat;
	Mat4f model_inverse_transpose_mat;

	void Load(const char* filename);
	void Init() override;
	void CleanUp() override;
};

