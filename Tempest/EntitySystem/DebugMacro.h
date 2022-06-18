#pragma once

#include <Configuration/Configuration.h>

//////////////////////////////
// Shader Macro
//////////////////////////////

namespace Tmpest
{
	class EffectComponent;
}

#define SHOW_DEBUG_POLYGON \
{\
	const char* debugshader[] = \
	{ \
		PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_VERT, \
		"", \
		"", \
		PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_GEO, \
		PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_FRAG, \
	}; \
 \
	OwningPointer<EffectComponent> debugeffect = OwningPointer<EffectComponent>::Create(debugeffect); \
	debugeffect->owner = Entity::Query(this); \
	debugeffect->RegisterShaderPath(debugshader); \
	Entity::RegisterEffectComponent(debugeffect); \
}

#define SHOW_DEBUG_NORMAL_COLOR \
{\
	const char* debugshader[] = \
	{ \
		PATH_SUFFIX SHADER_PATH DEBUG_NORMAL_COLOR_VERT, \
		"", \
		"", \
		"", \
		PATH_SUFFIX SHADER_PATH DEBUG_NORMAL_COLOR_FRAG, \
	}; \
 \
	OwningPointer<EffectComponent> debugeffect = OwningPointer<EffectComponent>::Create(debugeffect); \
	debugeffect->owner = Entity::Query(this); \
	debugeffect->RegisterShaderPath(debugshader); \
	Entity::RegisterEffectComponent(debugeffect); \
}

#define SHOW_DEBUG_NORMAL_VECTOR \
{\
	const char* debugshader[] = \
	{ \
		PATH_SUFFIX SHADER_PATH DEBUG_NORMAL_VECTOR_VERT, \
		"", \
		"", \
		PATH_SUFFIX SHADER_PATH DEBUG_NORMAL_VECTOR_GEO, \
		PATH_SUFFIX SHADER_PATH DEBUG_NORMAL_VECTOR_FRAG, \
	}; \
 \
	OwningPointer<EffectComponent> debugeffect = OwningPointer<EffectComponent>::Create(debugeffect); \
	debugeffect->owner = Entity::Query(this); \
	debugeffect->RegisterShaderPath(debugshader); \
	Entity::RegisterEffectComponent(debugeffect); \
}

#define SHOW_DEBUG_VIEWDIRECTION \
{\
	const char* debugshader[] = \
	{ \
		PATH_SUFFIX SHADER_PATH DEBUG_VIEW_VERT, \
		"", \
		"", \
		"", \
		PATH_SUFFIX SHADER_PATH DEBUG_VIEW_FRAG, \
	}; \
 \
	OwningPointer<EffectComponent> debugeffect = OwningPointer<EffectComponent>::Create(debugeffect); \
	debugeffect->owner = Entity::Query(this); \
	debugeffect->RegisterShaderPath(debugshader); \
	Entity::RegisterEffectComponent(debugeffect); \
}

#define SHOW_DEBUG_LIGHTDIRECTION \
{\
	const char* debugshader[] = \
	{ \
		PATH_SUFFIX SHADER_PATH DEBUG_LIGHT_DIRECTION_VERT, \
		"", \
		"", \
		"", \
		PATH_SUFFIX SHADER_PATH DEBUG_LIGHT_DIRECTION_FRAG, \
	}; \
 \
	OwningPointer<EffectComponent> debugeffect = OwningPointer<EffectComponent>::Create(debugeffect); \
	debugeffect->owner = Entity::Query(this); \
	debugeffect->RegisterShaderPath(debugshader); \
	Entity::RegisterEffectComponent(debugeffect); \
}

#define SHOW_DEBUG_BP_BASIC \
{\
	const char* debugshader[] = \
	{ \
	PATH_SUFFIX SHADER_PATH DEBUG_BP_BASIC_VERT, \
	"", \
	"", \
	"", \
	PATH_SUFFIX SHADER_PATH DEBUG_BP_BASIC_FRAG, \
	}; \
\
	OwningPointer<EffectComponent> debugeffect = OwningPointer<EffectComponent>::Create(debugeffect); \
	debugeffect->owner = Entity::Query(this); \
	debugeffect->RegisterShaderPath(debugshader); \
	Entity::RegisterEffectComponent(debugeffect); \
}

#define SHOW_EDITOR_OUTLINE \
{\
	const char* debugshader[] = \
	{ \
	PATH_SUFFIX SHADER_PATH "debug_purpose\\outlinehighlight.vert.glsl", \
	"", \
	"", \
	"", \
	PATH_SUFFIX SHADER_PATH "debug_purpose\\outlinehighlight.frag.glsl", \
	}; \
\
	Owner<EffectComponent> debugeffect = Create<EffectComponent>(); \
	debugeffect->owner = Entity::Query(this); \
	debugeffect->RegisterShaderPath(debugshader); \
	debugeffect->is_enable = false;\
	debugeffect->is_debug_function = true;\
	Entity::RegisterEffectComponent(debugeffect); \
}