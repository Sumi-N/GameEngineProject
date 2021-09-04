#pragma once

#include "Define.h"
#include "Component.h"
#include "MeshComponent.h"

namespace Tempest
{

	class AnimationComponent : public Component
	{
	public:
		AnimationComponent() : is_looping(false), frame_per_second(0), frame_count(0) {};
		~AnimationComponent() = default;

		OwningPointer<Resource::AnimationClip> clip;
		ObservingPointer<MeshComponent> mesh;
		
		virtual void Boot() override;
		virtual void Init() override;
		virtual void Update(float i_dt) override;
		virtual void CleanUp() override;

		Result Load(const char* i_filename);		

	private:
		bool  is_looping;
		float frame_per_second;
		int   frame_count;

		bool IsLoaded();
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

	inline Result AnimationComponent::Load(const char* i_filename)
	{
		if (IsLoaded())
		{
			DEBUG_PRINT("There is a clip that is already loaded");
			DEBUG_ASSERT(false);
		}

		clip = OwningPointer<Resource::AnimationClip>::Create(clip);
		return Resource::AnimationClip::Load(i_filename, *clip);
	}

	inline bool AnimationComponent::IsLoaded()
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