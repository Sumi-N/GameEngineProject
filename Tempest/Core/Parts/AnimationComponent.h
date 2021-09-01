#pragma once

#include "Define.h"
#include "Component.h"

namespace Tempest
{

	class AnimationComponent : public Component
	{
	public:
		AnimationComponent() = default;
		~AnimationComponent() = default;

		OwningPointer<Resource::Mesh> mesh;

		ObservingPointer<Object> owner;
		
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
		void CleanMesh();
	};

	inline Result AnimationComponent::Load(const char* i_filename)
	{

	}

}