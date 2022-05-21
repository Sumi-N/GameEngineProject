#pragma once

#include "Define.h"
#include "Object.h"
#include "MeshComponent.h"
#include "EffectComponent.h"
#include "Entity.h"
#include "DebugMacro.h"

namespace Tempest
{

	class DebugObject : public Object
	{
	public:

		virtual void Boot() override;
		virtual void Init() override;
		virtual void Update(float i_dt) override;	
	};

	inline void DebugObject::Boot()
	{
		Object::Boot();

#if defined(_DEBUG) && !defined(NDEBUG)
		//SHOW_DEBUG_POLYGON
		//SHOW_DEBUG_NORMAL_COLOR
		//SHOW_DEBUG_NORMAL_VECTOR
		//SHOW_DEBUG_VIEWDIRECTION
		//SHOW_DEBUG_LIGHTDIRECTION
		//SHOW_DEBUG_BP_BASIC		
#endif // DEBUG

#ifdef ENGINE_USE_EDITOR
		SHOW_EDITOR_OUTLINE
#endif

	}

	inline void DebugObject::Init()
	{
		Object::Init();
	}

	inline void DebugObject::Update(float i_dt)
	{
		Object::Update(i_dt);
	}
}