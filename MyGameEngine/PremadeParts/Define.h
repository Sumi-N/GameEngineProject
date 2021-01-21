#pragma once

#include <Configuration/Configuration.h>

#include <Math/Quaternion.h>

#include <Parts/MeshComponent.h>
#include <Parts/EffectComponent.h>
#include <Parts/Object.h>
#include <Parts/CubeMap.h>
#include <Parts/TextureAttribute.h>
#include <Parts/MaterialAttribute.h>

#include <EntitySystem/Entity.h>
#include <Graphics/SceneEntity.h>


//////////////////////////////
// Shader Macro
//////////////////////////////

#define SHOW_DEBUG_POLYGON \
{\
	const char* debugshader[] = \
	{ \
		PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_VERT, \
		nullptr, \
		nullptr, \
		PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_GEO, \
		PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_FRAG, \
	}; \
 \
	OwningPointer<EffectComponent> debugeffect = OwningPointer<EffectComponent>::Create(debugeffect); \
	debugeffect->owner = Entity::Query(this).p; \
	debugeffect->RegisterShaderPath(debugshader); \
	Entity::RegisterEffectComponent(debugeffect); \
}

#define SHOW_DEBUG_NORMAL_COLOR \
{\
	const char* debugshader[] = \
	{ \
		PATH_SUFFIX SHADER_PATH DEBUG_NORMAL_COLOR_VERT, \
		nullptr, \
		nullptr, \
		nullptr, \
		PATH_SUFFIX SHADER_PATH DEBUG_NORMAL_COLOR_FRAG, \
	}; \
 \
	OwningPointer<EffectComponent> debugeffect = OwningPointer<EffectComponent>::Create(debugeffect); \
	debugeffect->owner = Entity::Query(this).p; \
	debugeffect->RegisterShaderPath(debugshader); \
	Entity::RegisterEffectComponent(debugeffect); \
}

#define SHOW_DEBUG_NORMAL_VECTOR \
{\
	const char* debugshader[] = \
	{ \
		PATH_SUFFIX SHADER_PATH DEBUG_NORMAL_VECTOR_VERT, \
		nullptr, \
		nullptr, \
		PATH_SUFFIX SHADER_PATH DEBUG_NORMAL_VECTOR_GEO, \
		PATH_SUFFIX SHADER_PATH DEBUG_NORMAL_VECTOR_FRAG, \
	}; \
 \
	OwningPointer<EffectComponent> debugeffect = OwningPointer<EffectComponent>::Create(debugeffect); \
	debugeffect->owner = Entity::Query(this).p; \
	debugeffect->RegisterShaderPath(debugshader); \
	Entity::RegisterEffectComponent(debugeffect); \
}

#define SHOW_DEBUG_VIEWDIRECTION \
{\
	const char* debugshader[] = \
	{ \
		PATH_SUFFIX SHADER_PATH DEBUG_VIEW_VERT, \
		nullptr, \
		nullptr, \
		nullptr, \
		PATH_SUFFIX SHADER_PATH DEBUG_VIEW_FRAG, \
	}; \
 \
	OwningPointer<EffectComponent> debugeffect = OwningPointer<EffectComponent>::Create(debugeffect); \
	debugeffect->owner = Entity::Query(this).p; \
	debugeffect->RegisterShaderPath(debugshader); \
	Entity::RegisterEffectComponent(debugeffect); \
}

#define SHOW_DEBUG_LIGHTDIRECTION \
{\
	const char* debugshader[] = \
	{ \
		PATH_SUFFIX SHADER_PATH DEBUG_LIGHT_DIRECTION_VERT, \
		nullptr, \
		nullptr, \
		nullptr, \
		PATH_SUFFIX SHADER_PATH DEBUG_LIGHT_DIRECTION_FRAG, \
	}; \
 \
	OwningPointer<EffectComponent> debugeffect = OwningPointer<EffectComponent>::Create(debugeffect); \
	debugeffect->owner = Entity::Query(this).p; \
	debugeffect->RegisterShaderPath(debugshader); \
	Entity::RegisterEffectComponent(debugeffect); \
}

#define SHOW_DEBUG_BP_BASIC \
{\
	const char* debugshader[] = \
	{ \
	PATH_SUFFIX SHADER_PATH DEBUG_BP_BASIC_VERT, \
	nullptr, \
	nullptr, \
	nullptr, \
	PATH_SUFFIX SHADER_PATH DEBUG_BP_BASIC_FRAG, \
	}; \
\
	OwningPointer<EffectComponent> debugeffect = OwningPointer<EffectComponent>::Create(debugeffect); \
	debugeffect->owner = Entity::Query(this).p; \
	debugeffect->RegisterShaderPath(debugshader); \
	Entity::RegisterEffectComponent(debugeffect); \
}