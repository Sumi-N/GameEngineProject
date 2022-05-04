#pragma once

#include <Thread/Define.h>

namespace Tempest
{
	class MyPointLight : public Object
	{
	public:
		void Boot() override;
		void Update(float i_dt) override;
		
		Owner<LightComponent> light_component;
	};

	inline void MyPointLight::Boot()
	{
		light_component = Create<LightComponent>();		
		light_component->light_type = LightComponent::LightType::PointLight;
		light_component->intensity = Vec3f(25.0f, 25.0f, 25.0f);		
		light_component->attenuation = Vec3f(1.0f, 0.07f, 0.017f);
		light_component->owner = Entity::Query(this);
		Entity::RegisterLightComponent(light_component);		
	}

	inline void MyPointLight::Update(float i_dt)
	{
		if (UserInput.QueryKey(VirtualKey::KEY_I) == InputState::Pressing)
		{
			Translate(Vec3f(pos.x, pos.y + 1.0f, pos.z));
		}

		if (UserInput.QueryKey(VirtualKey::KEY_K) == InputState::Pressing)
		{
			Translate(Vec3f(pos.x, pos.y - 1.0f, pos.z));
		}

		if (UserInput.QueryKey(VirtualKey::KEY_J) == InputState::Pressing)
		{
			Translate(Vec3f(pos.x + 1.0f, pos.y, pos.z));
		}

		if (UserInput.QueryKey(VirtualKey::KEY_L) == InputState::Pressing)
		{
			Translate(Vec3f(pos.x - 1.0f, pos.y, pos.z));
		}		
	}
}