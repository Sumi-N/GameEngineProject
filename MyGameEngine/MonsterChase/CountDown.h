#pragma once
#include "DebugLog.h"
#include "Object3D.h"
#include "Time.h"

class CountDown : public Object3D
{
public:
	void init();
	void update();
private:
	float timer;
};

inline void CountDown::init() {
	timer = 0.0f;
}

inline void CountDown::update() {
	timer += static_cast<float>(Time::dt);

	if (timer < 10000) {
		DEBUG_PRINT("%f", timer / 1000);
	}
}