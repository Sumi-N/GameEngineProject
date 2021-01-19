#pragma once
#include "Physics3D.h"
#include "Process.h"

class MonsterPhysics : public Physics3D {
	void init();
	void collision(Physics3D *);
};

inline void MonsterPhysics::init() {

}

inline void MonsterPhysics::collision(Physics3D * collide_obj) {
	System::Process::BQuit = true;
}
