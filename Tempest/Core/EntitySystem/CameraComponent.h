#pragma once
#include "Define.h"
#include "Component.h"

namespace Tempest
{
	class CameraComponent : public Component
	{
	public:
		CameraComponent() = default;
		~CameraComponent() = default;
		
		virtual void Init() override;
		virtual void Update(float i_dt) override;		

		void MoveCamera(const float, const Vec3f&);
		void RotateAround(const float, const Vec3f&);

		Mat4f view, perspective, orthographics;		
		Vec3f forwardvec, upvec, rightvec;
	};

	inline void CameraComponent::Init()
	{
		forwardvec = Vec3f(0, 0, -1);
		upvec = Vec3f(0, 1, 0);
		rightvec = Vec3f::Normalize(forwardvec.Cross(upvec));

		// The parameters for lookAt function are position, target, up vector
		// target is equal to forwardvector + position;
		view = Mat4f::LookAt(owner->pos, owner->pos + forwardvec, upvec);

		perspective = Mat4f::Perspective(FieldOfView, (float)ScreenWidth / ScreenHeight, NearClip, FarClip);
		orthographics = Mat4f::Orthographic(-10.0f, 10.0f, -10.0f, 10.0f, NearClip, FarClip);
	}

	inline void CameraComponent::Update(float i_dt)
	{
		owner->pos += (float)i_dt * owner->vel;
		owner->vel = Vec3f(0, 0, 0);

		view = Mat4f::LookAt(owner->pos, owner->pos + forwardvec, upvec);		
	}

	inline void CameraComponent::MoveCamera(const float amount, const Vec3f& dir)
	{
		owner->vel = amount * dir;
	}

	inline void CameraComponent::RotateAround(const float amount, const Vec3f& axis)
	{

		forwardvec = forwardvec.Rotate(axis, amount);
		upvec = upvec.Rotate(axis, amount);

		rightvec = Vec3f::Normalize(forwardvec.Cross(upvec));
	}
}

