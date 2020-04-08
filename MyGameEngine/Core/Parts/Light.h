#pragma once
#include "Define.h"
#include "Object.h"

class Light : public Object
{
public:
	Vec3f intensity;
	//Mat4f light_space_mat;

	void Update(float i_dt) override {};
};

class AmbientLight : public Light
{

};

class PointLight : public Light
{
public:
	//Vec3f pos; <- inherit from Object
	Vec3f attenuation = Vec3f(1.0f, 0.07f, 0.017f);
	Mat4f light_space_mats[6];

	void Update(float i_dt) override
	{
		Mat4f light_projection = Mat4f::Perspective(90, 1, NEARCLIP, FARCLIP);
		
		Mat4f light_view;

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
		//light_space_mat = light_projection * light_view;
	}
};