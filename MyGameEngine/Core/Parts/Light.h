#pragma once
#include "Define.h"
#include "Object.h"

class Light : public Object
{
public:
	Vec3f intensity;
	Mat4f light_space_mat;

	void Update(float i_dt) override {};
};

class AmbientLight : public Light
{

};

class PointLight : public Light
{
public:
	//Vec3f pos; <- inherit from Object

	void Update(float i_dt) override
	{
		Mat4f light_projection = Mat4f::Perspective(FOV, (float)SCREEN_WIDTH / SCREEN_HEIGHT, NEARCLIP, FARCLIP);
		// Temporary solution
		Mat4f light_view = Mat4f::LookAt(pos, pos + Vec3f(0, 0, -50), Vec3f(20, -20, 0));
		light_space_mat = light_projection * light_view;
	}
};

class DirectionalLight : public Light
{
public:
	Vec3f direction;

	void Update(float i_dt) override
	{
		Mat4f light_projection = Mat4f::Orthographic(-30.0f, 30.0f, -30.0f, 30.0f, NEARCLIP, FARCLIP);
		// Temporary solution
		Mat4f light_view = Mat4f::LookAt(pos, pos + Vec3f(0, 0, -50), Vec3f(20, -20, 0));
		light_space_mat = light_projection * light_view;
	}
};