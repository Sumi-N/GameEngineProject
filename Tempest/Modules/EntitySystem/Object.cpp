#include "Object.h"
#include "EffectComponent.h"
#include "Entity.h"
#include "DebugMacro.h"

namespace Tempest
{
	Object::Object(const char* name)
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

	void Object::Boot()
	{
#ifdef ENGINE_USE_EDITOR
		SHOW_EDITOR_OUTLINE
#endif // ENGINE_USE_EDITOR
	}

	void Object::Update(float i_dt)
	{
		pos += i_dt * vel;
	}
}