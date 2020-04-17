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
			Vec4f position;
			Vec3f point_attenuation; // Doesn't require padding
		};
	}

	struct Camera
	{
		Mat4f view_matrix;
		Mat4f perspective_matrix;
		Vec3f camera_position_vector; // Doesn't require padding 
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

		Vec4f albedo;
		float metalic;
		float roughness;
		float padding1;
		float padding2;
	};

	struct Light
	{
		Vec4f ambient_intensity;
		Vec4f directional_intensity;
		Vec4f directional_direction;
		SubData::PointLight pointlights[MAX_POINT_LIGHT_NUM];
		int   point_num;
		int   nth_point;
	};

	struct SkyBox
	{
		Mat4f skybox_view_perspective_matrix;
	};

	struct CubeMap
	{
		Mat4f view_perspective_matrix[6];
		Vec4f position;
		//Mat4f directional_view_perspective_matrix;
	};

	/////////////////// Don't forget to add index and size data after adding a new uniform data //////////////

	enum class Index : uint8_t
	{
		Camera = 0,
		Model = 1,
		Material = 2,
		Light = 3,
		SkyBox = 4,
		CubeMap = 5,
	};

	enum class Size : uint16_t
	{
		Camera           = sizeof(ConstantData::Camera),
		Model            = sizeof(ConstantData::Model),
		Material         = sizeof(ConstantData::Material),
		Light            = sizeof(ConstantData::Light),
		SkyBox           = sizeof(ConstantData::SkyBox),
		CubeMap           = sizeof(ConstantData::CubeMap),
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

