#pragma once
#include "Define.h"
#include <GL/glew.h>
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

	struct Light
	{
		Vec4f light_ambient_intensity;
		Vec4f light_point_intensity;
		Vec4f light_point_position;
		Vec4f padding;
		Mat4f light_view_perspective_matrix;
	};

	struct Image
	{
		Mat4f mirror_matrix;
	};

	/////////////////// Don't forget to add index and size data after adding a new uniform data //////////////

	enum class Index
	{
		Camera = 0,
		Object = 1,
		Material = 2,
		Light = 3,
		Image = 4,
	};

	enum class Size
	{
		Camera = sizeof(ConstantData::Camera),
		Object = sizeof(ConstantData::Model),
		Material = sizeof(ConstantData::Material),
		Light = sizeof(ConstantData::Light),
		Image = sizeof(ConstantData::Image),
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

