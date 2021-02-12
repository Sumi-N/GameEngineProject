#pragma once

#include "Define.h"
#include "Object.h"

namespace Tempest
{

	class Component
	{
	public:

		virtual ~Component(){};

		ObservingPointer<Object> pointer;

		virtual void Boot(){};
		virtual void Init(){};
		virtual void Update(float){};
		virtual void CleanUp(){};
	};
}