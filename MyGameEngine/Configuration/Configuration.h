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
#define TEXTURE_PATH     "Assets/textures/"

//////////////////////////////
// Mesh Data
//////////////////////////////

#define FILENAME_CUBEMAP "cubemap.obj"
#define FILENAME_QUAD    "quad.obj"
#define FILENAME_SPHERE  "sphere.obj"

//////////////////////////////
// Texture Data
//////////////////////////////

#define SKYBOX_POSX      "skyboxes/cubemap_posx.png"
#define SKYBOX_NEGX      "skyboxes/cubemap_negx.png"
#define SKYBOX_POSY      "skyboxes/cubemap_posy.png"
#define SKYBOX_NEGY      "skyboxes/cubemap_negy.png"
#define SKYBOX_POSZ      "skyboxes/cubemap_posz.png"
#define SKYBOX_NEGZ      "skyboxes/cubemap_negz.png"

//////////////////////////////
// Shader Data
//////////////////////////////
#define EMPTY_VERT     "empty_shader/empty.vert.glsl"
#define EMPTY_FRAG     "empty_shader/empty.frag.glsl"

#define SKYBOX_VERT    "skybox/skybox.vert.glsl"
#define SKYBOX_FRAG    "skybox/skybox.frag.glsl"

#define SHADOWMAP_VERT "shadow_mapping/shadowmap.vert.glsl"
#define SHADOWMAP_FRAG "shadow_mapping/shadowmap.frag.glsl"

#define MIRROR_VERT     "mirror/mirror.vert.glsl"
#define MIRROR_FRAG     "mirror/mirror.frag.glsl"

#define BLINN_PHONG_VERT "blinn_phong_model/blinn_phong.vert.glsl"
#define BLINN_PHONG_FRAG "blinn_phong_model/blinn_phong.frag.glsl"

#define DISNEY_PBR_VERT  "disney_pbr_model/disney_pbr.vert.glsl"
#define DISNEY_PBR_FRAG  "disney_pbr_model/disney_pbr.frag.glsl"

#define QUAD_VERT        "quad/quad.vert.glsl"
#define QUAD_FRAG        "quad/quad.frag.glsl"

#define NORMAL_MAP_VERT  "test_purpose/normal_mapping.vert.glsl"
#define NORMAL_MAP_FRAG  "test_purpose/normal_mapping.frag.glsl"

#define DEBUG_SHADOW_MAP_VERT "debug_purpose/debugshadowmap.vert.glsl"
#define DEBUG_SHADOW_MAP_FRAG "debug_purpose/debugshadowmap.frag.glsl"

#define DEBUG_POLYGON_VERT "debug_purpose/debug_polygon.vert.glsl"
#define DEBUG_POLYGON_GEO  "debug_purpose/debug_polygon.geo.glsl"
#define DEBUG_POLYGON_FRAG "debug_purpose/debug_polygon.frag.glsl"

#define DEBUG_NORMAL_VERT "debug_purpose/debug_normal.vert.glsl"
#define DEBUG_NORMAL_FRAG "debug_purpose/debug_normal.frag.glsl"



