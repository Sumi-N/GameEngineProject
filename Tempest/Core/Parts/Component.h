#pragma once

#include "Define.h"
#include "Object.h"

namespace Tempest
{

	class Component
	{
	public:
		Component() {};
		virtual ~Component(){};		

		virtual void Boot(){};
		virtual void Init(){};
		virtual void Update(float){};
		virtual void CleanUp(){};

		ObservingPointer<Object> pointer;
	};
}