#pragma once
#include "Define.h"
#include "Object.h"

class Camera : public Object 
{
public:
	Mat4f view, perspective, orthographics;
	Mat4f view_perspective_mat;

	Vec3f forwardvec, upvec, rightvec;

	float fov, nearestclip, farestclip;

public:

	Camera()
	{
		forwardvec = Vec3f(0, 0, -1);
		upvec = Vec3f(0, 1, 0);
		rightvec = Vec3f::Normalize(forwardvec.Cross(upvec));

		fov = 45.0f;
		nearestclip = 0.1f;
		farestclip = 100.0f;

		// The parameters for lookAt function are position, target, up vector
		// target is equal to forwardvector + position;
		//view = glm::lookAt(pos, pos + forwardvec, upvec);
		//perspective = glm::perspective(glm::radians(fov), (float)WIDTH / HEIGHT, nearestclip, farestclip);
		//orthographics = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
	}

	void RotateAround(float amount, Vec3f& axis)
	{
		//forwardvec = glm::rotate(forwardvec, -1 * glm::radians(amount), axis);
		//upvec = glm::rotate(upvec, -1 * glm::radians(amount), axis);
		//rightvec = glm::cross(forwardvec, upvec);
	}

	void MoveCamera(float amount, Vec3f& dir)
	{
		vel = amount * dir;
	}

	void Update(float dt)
	{
		pos += (float)dt * vel;
		//view = glm::lookAt(pos, pos + forwardvec, upvec);
		view_perspective_mat = perspective * view;
	}
};