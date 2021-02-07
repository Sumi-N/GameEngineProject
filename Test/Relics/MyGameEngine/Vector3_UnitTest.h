#pragma once
#include "Vector3D.h"

#include <stdlib.h>

namespace UnitTest {
	void Vector3IntrinsicTest() {
		Vector3D vec1 = Vector3D(static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 5)), static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 5)), static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 5)));
		Vector3D vec2 = Vector3D(static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 5)), static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 5)), static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 5)));
		Vector3D vec3 = vec1 + vec2;
	}
}