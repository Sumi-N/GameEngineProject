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

		Owner<Resource::Skeleton> skeleton;
		Owner<Resource::AnimationClip> clip;
		Observer<MeshComponent> mesh;

		virtual void Boot() override;
		virtual void Init() override;
		virtual void Update(float i_dt) override;
		virtual void CleanUp() override;

		Result LoadSkeleton(const char* i_filename);
		Result LoadClip(const char* i_filename);

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

	inline Result AnimationComponent::LoadSkeleton(const char* i_filename)
	{
		if (IsSkeletonLoaded())
		{
			DEBUG_PRINT("There is a skeleton that is already loaded");
			DEBUG_ASSERT(false);
		}

		skeleton = Owner<Resource::Skeleton>::Create(skeleton);
		return Resource::Skeleton::Load(i_filename, *skeleton);
	}

	inline Result AnimationComponent::LoadClip(const char* i_filename)
	{
		if (IsClipLoaded())
		{
			DEBUG_PRINT("There is a clip that is already loaded");
			DEBUG_ASSERT(false);
		}

		clip = Owner<Resource::AnimationClip>::Create(clip);
		return Resource::AnimationClip::Load(i_filename, *clip);
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