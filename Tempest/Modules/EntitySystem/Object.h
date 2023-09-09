#pragma once
#include "Define.h"

namespace Tempest
{
	class Object
	{
	public:

		Object() = default;
		Object(const char*);
		virtual ~Object() {};

		Vec3f pos{}, scale{1.0}, rot{};
		Vec3f vel{}, acc{};
		Vec3f angvel{}, angacc{};
		String name{"Empty"};

		void Translate(Vec3f i_pos) {this->pos = i_pos; }

		virtual void Boot();
		virtual void Init() {};
		virtual void Update(float i_dt);
		virtual void CleanUp() {};
	};
}