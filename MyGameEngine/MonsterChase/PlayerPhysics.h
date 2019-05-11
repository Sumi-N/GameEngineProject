#pragma once
#include "DebugLog.h"
#include "Physics3D.h"

class PlayerPhysics : public Physics3D {
public:
	void collision(Physics3D *);
};

inline void PlayerPhysics::collision(Physics3D *) {
}