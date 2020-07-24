#pragma once
#include "Define.h"
#include "Object.h"

class Camera : public Object 
{
public:
	Mat4f view, perspective, orthographics;
	Mat4f view_perspective_mat;

	Vec3f forwardvec, upvec, rightvec;

public:

	Camera()
	{
		forwardvec = Vec3f(0, 0, -1);
		upvec = Vec3f(0, 1, 0);
		rightvec = Vec3f::Normalize(forwardvec.Cross(upvec));

		// The parameters for lookAt function are position, target, up vector
		// target is equal to forwardvector + position;
		view = Mat4f::LookAt(pos, pos + forwardvec, upvec);

		perspective   = Mat4f::Perspective(FOV, (float)SCREEN_WIDTH / SCREEN_HEIGHT, NEARCLIP, FARCLIP);
		orthographics = Mat4f::Orthographic(-10.0f, 10.0f, -10.0f, 10.0f, NEARCLIP, FARCLIP);
	}

	void RotateAround(float amount, Vec3f& axis)
	{

		forwardvec = forwardvec.Rotate(axis, amount);
		upvec = upvec.Rotate(axis, amount);

		rightvec = Vec3f::Normalize(forwardvec.Cross(upvec));
	}

	void MoveCamera(float amount, Vec3f& dir)
	{
		vel = amount * dir;
	}

	void Update(float dt)
	{
		pos += (float)dt * vel;
		vel = Vec3f(0, 0, 0);

		view = Mat4f::LookAt(pos, pos + forwardvec, upvec);
		view_perspective_mat = perspective * view;
	}
};