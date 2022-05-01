#pragma once
#include "Define.h"
#include "Object.h"
#include "MeshComponent.h"
#include "EffectComponent.h"

namespace Tempest
{

	class CameraObject : public Object
	{
	public:
		Mat4f view, perspective, orthographics;
		Mat4f view_perspective_mat;
	public:

		CameraObject()
		{
			forwardvec = Vec3f(0, 0, -1);
			upvec = Vec3f(0, 1, 0);
			rightvec = Vec3f::Normalize(forwardvec.Cross(upvec));

			// The parameters for lookAt function are position, target, up vector
			// target is equal to forwardvector + position;
			view = Mat4f::LookAt(pos, pos + forwardvec, upvec);

			perspective = Mat4f::Perspective(FieldOfView, (float)ScreenWidth / ScreenHeight, NearClip, FarClip);
			orthographics = Mat4f::Orthographic(-10.0f, 10.0f, -10.0f, 10.0f, NearClip, FarClip);
		}

		Vec3f GetForwardVec()
		{
			return forwardvec;
		}
		Vec3f GetRightVec()
		{
			return rightvec;
		}
		Vec3f GetUpVec()
		{
			return upvec;
		}

		void Boot() override;
		void Init() override;
		void Update(float) override;

		void MoveCamera(float, Vec3f&);
		void RotateAround(float, Vec3f&);

	protected:
		Vec3f forwardvec, upvec, rightvec;

	private:
		OwningPointer<MeshComponent> mesh;
		OwningPointer<EffectComponent> effect;
	};

	inline void CameraObject::Boot()
	{
		Object::Boot();
	}

	inline void CameraObject::Init()
	{
		Object::Init();
	}

	inline void CameraObject::Update(float i_dt)
	{
		Object::Update(i_dt);

		pos += (float)i_dt * vel;
		vel = Vec3f(0, 0, 0);

		view = Mat4f::LookAt(pos, pos + forwardvec, upvec);
		view_perspective_mat = perspective * view;
	}

	inline void CameraObject::MoveCamera(float amount, Vec3f& dir)
	{
		vel = amount * dir;
	}

	inline void CameraObject::RotateAround(float amount, Vec3f& axis)
	{

		forwardvec = forwardvec.Rotate(axis, amount);
		upvec = upvec.Rotate(axis, amount);

		rightvec = Vec3f::Normalize(forwardvec.Cross(upvec));
	}

}