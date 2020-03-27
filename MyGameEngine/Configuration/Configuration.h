#pragma once

//////////////////////////////
// Graphic API configuration
//////////////////////////////
#define ENGINE_GRAPHIC_OPENGL


// Asking GLEW to compile with static library
// This line should be put before #include <GL/glew.h>
#define GLEW_STATIC

//////////////////////////////
//  Math configuration
//////////////////////////////
#define _USEINTRINSIC_


//////////////////////////////
//  Platform configuration
//////////////////////////////
#define ENGINE_PLATFORM_WINDOWS


//////////////////////////////
// Screen Setting
//////////////////////////////
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NEARCLIP 0.1f
#define FARCLIP  100.0f
#define FOV      45.0f


//////////////////////////////
// Light Setting
//////////////////////////////

// Make sure to change the sharer's code if the number here got changed
#define MAX_POINT_LIGHT_NUM 5

//////////////////////////////
// General Asset Path
//////////////////////////////
#define PATH_SUFFIX      "../../"
#define MESH_PATH        "Assets/models/"
#define SHADER_PATH      "Assets/shaders/"
#define SKYBOX_PATH      "Assets/textures/skyboxes/"

//////////////////////////////
// Mesh Data
//////////////////////////////

#define FILENAME_CUBEMAP "cubemap.obj"
#define FILENAME_QUAD    "quad.obj"

//////////////////////////////
// Texture Data
//////////////////////////////

#define SKYBOX_POSX      "cubemap_posx.png"
#define SKYBOX_NEGX      "cubemap_negx.png"
#define SKYBOX_POSY      "cubemap_posy.png"
#define SKYBOX_NEGY      "cubemap_negy.png"
#define SKYBOX_POSZ      "cubemap_posz.png"
#define SKYBOX_NEGZ      "cubemap_negz.png"

//////////////////////////////
// Shader Data
//////////////////////////////

#define SKYBOX_VERT    "skybox.vert.glsl"
#define SKYBOX_FRAG    "skybox.frag.glsl"

#define SHADOWMAP_VERT "shadowmap.vert.glsl"
#define SHADOWMAP_FRAG "shadowmap.frag.glsl"

#define MIRROR_VERT    "mirror.vert.glsl"
#define MIRROR_FRAG    "mirror.frag.glsl"

#define DEBUG_SHADOW_MAP_VERT "debugshadowmap.vert.glsl"
#define DEBUG_SHADOW_MAP_FRAG "debugshadowmap.frag.glsl"

#define BLINN_PHONG_VERT      "blinn_phong.vert.glsl"
#define BLINN_PHONG_FRAG      "blinn_phong.frag.glsl"

#define QUAD_VERT             "quad.vert.glsl"
#define QUAD_FRAG             "quad.frag.glsl"