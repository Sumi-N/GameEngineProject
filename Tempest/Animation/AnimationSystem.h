#pragma once
#include "Define.h"

namespace Tempest
{
	class AnimationComponent;

	class AnimationSystem
	{
	public:
		AnimationSystem() = default;
		~AnimationSystem() = default;

		void Register(const Owner<AnimationComponent>&);

		void Boot();
		void Init();
		void Update(float i_dt);
		void CleanUp();
		void Clear();

		auto Begin() { return list.Begin(); }
		auto End()   { return list.End(); }

		Mat4f bones[NUM_MAX_BONES];

	private:
		Result InterpolateMatrixBetweenFrames(const Resource::AnimationClip&, const float, float&, Mat4f*, const bool&);

		Array<Owner<AnimationComponent>> list;
		float animation_current_time = 0;
	};
}
