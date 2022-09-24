#pragma once
#include "Define.h"

namespace Tempest
{
	namespace ConstantData
	{

		struct PointLight
		{
			Vec4f intensity;
			Vec4f position;
			Vec3f attenuation; // Doesn't require padding
		};

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
		public:
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
			PointLight pointlights[NUM_MAX_POINT_LIGHT];
			int   point_num;
			int   nth_point;
		};

		struct SkyBox
		{
			Mat4f skybox_view_perspective_matrix;
		};

		struct CubeMap
		{
			Mat4f view_perspective_matrix[NUM_DICE_FACES];
			Vec4f position;
		};

		struct AnimationBone
		{
			Mat4f global_inversed_matrix[NUM_MAX_BONES];
		};

		//---------------------------------------------------------------------------------------------------//
		//The size and index number of constant data
		//---------------------------------------------------------------------------------------------------//

		enum class Index : uint8_t
		{
			Camera = 0,
			Model = 1,
			Material = 2,
			Light = 3,
			SkyBox = 4,
			CubeMap = 5,
			AnimationBone = 6,
		};

		static uint32_t GetDataSize(Index index)
		{
			switch (index)
			{
			case Index::Camera:           return sizeof(ConstantData::Camera);
			case Index::Model:            return sizeof(ConstantData::Model);
			case Index::Material:         return sizeof(ConstantData::Material);
			case Index::Light:            return sizeof(ConstantData::Light);
			case Index::SkyBox:           return sizeof(ConstantData::SkyBox);
			case Index::CubeMap:          return sizeof(ConstantData::CubeMap);
			case Index::AnimationBone:    return sizeof(ConstantData::AnimationBone);
			}

			DEBUG_ASSERT(false);
			return 0;
		}
	}

	class ConstantBuffer
	{
	public:
		ConstantBuffer() = default;
		~ConstantBuffer() = default;

#ifdef ENGINE_GRAPHIC_VULKAN

#endif // ENGINE_GRAPHIC_OPENGL

		void Init(ConstantData::Index);
		void Update(const void* const);
	};
}
