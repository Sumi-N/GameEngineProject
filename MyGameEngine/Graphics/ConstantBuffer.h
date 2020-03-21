#pragma once
#include "Define.h"
#include <Math/Matrix.h>

namespace ConstantData
{
	struct Camera
	{
		Mat4f view_matrix;
		Mat4f perspective_matrix;
		Vec3f camera_position_vector;
		float padding;
	};

	struct Model
	{
		Mat4f model_position_matrix;
		Mat4f model_view_perspective_matrix;
		Mat4f model_inverse_transpose_matrix;
	};

	struct Material
	{
		Vec4f diffuse;
		Vec4f specular;
	};

	struct AmbientLight
	{
		Vec4f ambient_intensity;
	};

	struct PointLight
	{
		Mat4f point_view_perspective_matrix;
		Vec4f point_intensity;
		Vec4f point_position;
	};

	struct DirectionalLight
	{
		Mat4f directional_view_perspective_matrix;
		Vec4f directional_intensity;
		Vec4f directional_direction;
	};

	struct Image
	{
		Mat4f mirror_matrix;
	};

	/////////////////// Don't forget to add index and size data after adding a new uniform data //////////////

	enum class Index : uint8_t
	{
		Camera = 0,
		Model = 1,
		Material = 2,
		AmbientLight = 3,
		PointLight = 4,
		DirectionalLight = 5,
		Image = 6,
	};

	enum class Size : uint8_t
	{
		Camera           = sizeof(ConstantData::Camera),
		Model            = sizeof(ConstantData::Model),
		Material         = sizeof(ConstantData::Material),
		AmbientLight     = sizeof(ConstantData::AmbientLight),
		PointLight       = sizeof(ConstantData::PointLight),
		DirectionalLight = sizeof(ConstantData::DirectionalLight),
		Image            = sizeof(ConstantData::Image),
	};
}

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

#ifdef  ENGINE_GRAPHIC_OPENGL
	GLuint bufferid = 0;
	GLuint index;
	GLsizeiptr size;
#endif // 

	void Init(ConstantData::Index, ConstantData::Size);
	void Update(const void* const);
};

