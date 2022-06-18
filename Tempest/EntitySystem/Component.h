#pragma once
#include "Define.h"
#include "Object.h"

namespace Tempest
{
	class Object;

	class Component
	{
	public:
		Component() {};
		virtual ~Component(){};

		virtual void Boot(){};
		virtual void Init(){};
		virtual void Update(float){};
		virtual void CleanUp(){};

		Observer<Object> owner;
		bool is_enable{true};

#ifdef ENGINE_USE_EDITOR
		bool is_debug_function{false};
#endif // ENGINE_USE_EDITOR

	};
}