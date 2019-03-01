#pragma once
#include "Object2D.h"
#include "SmartPointers.h"

#include <list>
#include <iterator>

namespace Engine {
	class EntityObject2D {
	public:
		OwningPointer<Object2D> point;
	private:
	};
}