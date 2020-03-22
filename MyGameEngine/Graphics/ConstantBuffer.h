#pragma once
#include "Define.h"
#include <Math/Matrix.h>

namespace ConstantData
{
	namespace SubData
	{
		struct PointLight
		{
			Vec4f point_intensity;
			Vec4f point_position;
		};
	}

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
		Vec4f ambient_intensity;
		Vec4f directional_intensity;
		Vec4f directional_direction;
		SubData::PointLight pointlights[MAX_POINT_LIGHT_NUM];
		int   point_num;
	};

	struct SkyBox
	{
		Mat4f skybox_view_perspective_matrix;
	};

	struct ShadowMap
	{
		Mat4f point_view_perspective_matrix;
		Mat4f directional_view_perspective_matrix;
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
		Light = 3,
		SkyBox = 4,
		ShadowMap = 6,
		Image = 7,
	};

	enum class Size : uint8_t
	{
		Camera           = sizeof(ConstantData::Camera),
		Model            = sizeof(ConstantData::Model),
		Material         = sizeof(ConstantData::Material),
		Light            = sizeof(ConstantData::Light),
		SkyBox           = sizeof(ConstantData::SkyBox),
		ShadowMap        = sizeof(ConstantData::ShadowMap),
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

