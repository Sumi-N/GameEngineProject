#pragma once

#include "Define.h"
#include "Component.h"
#include "MeshComponent.h"

namespace Tempest
{
	class MeshComponent;

	class AnimationComponent : public Component
	{
	public:
		AnimationComponent() : is_looping(false), frame_per_second(0), frame_count(0) {};
		~AnimationComponent() = default;

		String skeleton_path;
		String animation_clip_path;

		Owner<Skeleton> skeleton;
		Owner<AnimationClip> clip;
		Observer<MeshComponent> mesh;

		virtual void Boot() override;
		virtual void Init() override;
		virtual void Update(float i_dt) override;
		virtual void CleanUp() override;

		Result LoadSkeleton();
		Result LoadClip();

	private:
		bool  is_looping;
		float frame_per_second;
		int   frame_count;

		bool IsSkeletonLoaded();
		bool IsClipLoaded();
	};

	inline void AnimationComponent::Boot()
	{
		Component::Boot();
		LoadSkeleton();
		LoadClip();
	}

	inline void AnimationComponent::Init()
	{
		Component::Init();
	}

	inline void AnimationComponent::Update(float i_dt)
	{
		Component::Update(i_dt);
	}

	inline void AnimationComponent::CleanUp()
	{
		Component::CleanUp();
	}

	inline Result AnimationComponent::LoadSkeleton()
	{
		if (IsSkeletonLoaded())
		{
			DEBUG_PRINT("There is a skeleton that is already loaded");
			DEBUG_ASSERT(false);
		}

		skeleton = Owner<Skeleton>::Create(skeleton);
		return Skeleton::Load(skeleton_path.c_str(), *skeleton);
	}

	inline Result AnimationComponent::LoadClip()
	{
		if (IsClipLoaded())
		{
			DEBUG_PRINT("There is a clip that is already loaded");
			DEBUG_ASSERT(false);
		}

		clip = Owner<AnimationClip>::Create(clip);
		return AnimationClip::Load(animation_clip_path.c_str(), *clip);
	}

	inline bool AnimationComponent::IsSkeletonLoaded()
	{
		if (skeleton)
		{
			if (!skeleton->joints.Empty())
			{
				return true;
			}
		}

		return false;
	}

	inline bool AnimationComponent::IsClipLoaded()
	{
		if (clip)
		{
			if (!clip->samples.Empty())
			{
				if(!clip->samples[0].jointposes.Empty()){
					return true;
				}
			}
		}

		return false;
	}
}