#pragma once
#include "Object3D.h"
#include "SmartPointers.h"

#include <list>
#include <iterator>

namespace Engine {
	class Object3DPointer {
	public:
		OwningPointer<Object3D> pointer;
	private:
	};
}