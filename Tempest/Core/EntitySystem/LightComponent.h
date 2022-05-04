#pragma once
#include "Define.h"
#include "Component.h"

namespace Tempest
{		
	class LightComponent : public Component
	{
	public:
		LightComponent() = default;
		~LightComponent() = default;

		enum class LightType : uint8_t
		{
			Uninitialized,
			AmbientLight,
			PointLight,
			DirectionalLight,
		};
		
		virtual void Update(float i_dt) override;		
		
		LightType light_type {LightType::Uninitialized};
		Mat4f light_space_mats[6];
		Vec3f intensity;
		Vec3f attenuation;
		Vec3f direction;
	};

	inline void LightComponent::Update(float i_dt)
	{
		switch (light_type)
		{
		case LightComponent::LightType::Uninitialized:
			DEBUG_ASSERT(false);
			break;
		case LightComponent::LightType::AmbientLight:
			break;
		case LightComponent::LightType::PointLight:
		{
			Mat4f light_projection = Mat4f::Perspective(90, 1, NearClip, FarClip);
			Mat4f light_view;
			Vec3f pos = owner->pos;

			{
				light_view = Mat4f::LookAt(pos, pos + Vec3f(1, 0, 0), Vec3f(0, -1, 0));
				light_space_mats[0] = light_projection * light_view;
			}

			{
				light_view = Mat4f::LookAt(pos, pos + Vec3f(-1, 0, 0), Vec3f(0, -1, 0));
				light_space_mats[1] = light_projection * light_view;
			}

			{
				light_view = Mat4f::LookAt(pos, pos + Vec3f(0, 1, 0), Vec3f(0, 0, 1));
				light_space_mats[2] = light_projection * light_view;
			}

			{
				light_view = Mat4f::LookAt(pos, pos + Vec3f(0, -1, 0), Vec3f(0, 0, -1));
				light_space_mats[3] = light_projection * light_view;
			}

			{
				light_view = Mat4f::LookAt(pos, pos + Vec3f(0, 0, 1), Vec3f(0, -1, 0));
				light_space_mats[4] = light_projection * light_view;
			}

			{
				light_view = Mat4f::LookAt(pos, pos + Vec3f(0, 0, -1), Vec3f(0, -1, 0));
				light_space_mats[5] = light_projection * light_view;
			}
		}
			break;
		case LightComponent::LightType::DirectionalLight:
		{
			//Mat4f light_projection = Mat4f::Orthographic(-30.0f, 30.0f, -30.0f, 30.0f, NearClip, FarClip);
			// Temporary solution
			//Mat4f light_view = Mat4f::LookAt(pos, pos + Vec3f(0, 0, -50), Vec3f(20, -20, 0));
			//light_space_mat = light_projection * light_view;
		}
			break;
		default:
			DEBUG_ASSERT(false);
			break;
		}		
	}
}

