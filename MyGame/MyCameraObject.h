#pragma once
#include <Thread/Define.h>
#include <Application/Define.h>

namespace Tempest
{

	class MyCameraObject :public Object
	{
	public:
		virtual void Boot() override;
		virtual void Update(float i_dt) override;

		Owner<CameraComponent> camera_component;
	};

	inline void MyCameraObject::Boot()
	{
		camera_component = Create<CameraComponent>();
		camera_component->owner = Entity::Query(this);
		Entity::RegisterCameraComponent(camera_component);		
	}

	inline void MyCameraObject::Update(float i_dt)
	{		

		if (UserInput.QueryKey(VirtualKey::KEY_W) == InputState::Pressing)
		{
			camera_component->MoveCamera(0.01f, camera_component->forwardvec);
		}

		if (UserInput.QueryKey(VirtualKey::KEY_S) == InputState::Pressing)
		{
			camera_component->MoveCamera(-0.01f, camera_component->forwardvec);
		}

		if (UserInput.QueryKey(VirtualKey::KEY_A) == InputState::Pressing)
		{
			camera_component->MoveCamera(-0.01f, camera_component->rightvec);
		}

		if (UserInput.QueryKey(VirtualKey::KEY_D) == InputState::Pressing)
		{
			camera_component->MoveCamera(0.01f, camera_component->rightvec);
		}

		if (UserInput.QueryKey(VirtualKey::KEY_Q) == InputState::Pressing)
		{
			camera_component->MoveCamera(0.01f, camera_component->upvec);
		}

		if (UserInput.QueryKey(VirtualKey::KEY_E) == InputState::Pressing)
		{
			camera_component->MoveCamera(-0.01f, camera_component->upvec);
		}

		if (UserInput.QueryKey(VirtualKey::KEY_RIGHTBUTTON) == InputState::Pressing)
		{
			Vec2f mousevelocity = Vec2f(UserInput.MouseVelocityX(i_dt), UserInput.MouseVelocityY(i_dt));

			Vec3f up = Vec3f(0, 1, 0);
			camera_component->RotateAround(mousevelocity.x, up);
			Vec3f right = camera_component->rightvec;
			camera_component->RotateAround(mousevelocity.y, right);
		}
	}

}