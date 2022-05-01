#pragma once
#include "Define.h"

using namespace Resource;

namespace Tempest
{
	class AnimationComponent;

	class AnimationSystem
	{
	public:
		AnimationSystem() = default;
		~AnimationSystem() = default;

		void Register(const OwningPointer<AnimationComponent>&);

		void Boot();
		void Init();		
		void Update(float i_dt);
		void CleanUp();

		Mat4f bones[NUM_MAX_BONES];

	private:
		Result InterpolateMatrixBetweenFrames(const AnimationClip&, const float, float&, Mat4f*, const bool&);

		Array<OwningPointer<AnimationComponent>> list;
		float animation_current_time = 0;
	};
}
