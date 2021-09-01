#pragma once
#include "Define.h"

using namespace Resource;

class AnimationSystem
{
public:
	AnimationSystem() = default;
	~AnimationSystem() = default;

	void Update();

private:
	Result InterpolateMatrixOfAFrame(const AnimationClip, const float, Mat4f*);
};

