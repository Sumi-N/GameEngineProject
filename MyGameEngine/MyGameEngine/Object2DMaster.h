#pragma once
#include "Object2D.h"
#include "SmartPointers.h"

#include <list>
#include <iterator>

namespace Engine {
	class Object2DMaster {
	public:
		OwningPointer<Object2D> pointer;
	private:
	};
}