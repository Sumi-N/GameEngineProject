#pragma once

#include <Configuration/Configuration.h>

#include <Parts/MeshComponent.h>
#include <Parts/Object.h>
#include <Parts/TextureAttribute.h>
#include <Parts/MaterialAttribute.h>

#include <EntitySystem/Entity.h>
#include <Graphics/SceneEntity.h>


//////////////////////////////
// Shader Macro
//////////////////////////////

#define SHOW_DEBUG_POLYGON \
{\
	Shader * debugshader = new Shader(PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_VERT, PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_GEO, PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_FRAG);\
	format->AddShader(debugshader);\
}

#define SHOW_DEBUG_NORMAL \
{\
	Shader * debugshader = new Shader(PATH_SUFFIX SHADER_PATH DEBUG_NORMAL_VERT, PATH_SUFFIX SHADER_PATH DEBUG_NORMAL_FRAG);\
	format->AddShader(debugshader);\
}