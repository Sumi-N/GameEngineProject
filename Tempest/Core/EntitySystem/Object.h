#pragma once
#include "Define.h"

namespace Tempest
{
	class Object
	{
	public:

		Object();
		Object(const char*);
		virtual ~Object() {};

		Vec3f pos, scale, rot;
		Vec3f vel, acc;
		Vec3f angvel, angacc;
		String name;

		void Translate(Vec3f i_pos) {this->pos = i_pos; }

		virtual void Boot() {};
		virtual void Init() {};
		virtual void Update(float i_dt);
		virtual void CleanUp() {};
	};

	inline Object::Object()
	{
		pos   = Vec3f{};
		scale = Vec3f(1.0);
		rot   = Vec3f{};

		vel    = Vec3f{};
		acc    = Vec3f{};
		angvel = Vec3f{};
		angacc = Vec3f{};

		name   = { "Empty" };
	}

	inline Object::Object(const char* name)
	{
		pos = Vec3f{};
		scale = Vec3f(1.0);
		rot = Vec3f{};

		vel = Vec3f{};
		acc = Vec3f{};
		angvel = Vec3f{};
		angacc = Vec3f{};

		this->name = name;
	}

	inline void Object::Update(float i_dt)
	{
		pos += i_dt * vel;
	}	
}


