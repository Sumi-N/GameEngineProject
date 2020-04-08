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

#define SKYBOX_POSX      "skyboxe/cubemap_posx.png"
#define SKYBOX_NEGX      "skyboxe/cubemap_negx.png"
#define SKYBOX_POSY      "skyboxe/cubemap_posy.png"
#define SKYBOX_NEGY      "skyboxe/cubemap_negy.png"
#define SKYBOX_POSZ      "skyboxe/cubemap_posz.png"
#define SKYBOX_NEGZ      "skyboxe/cubemap_negz.png"

#define RUSTED_IRON_ALBEDO "albedo/rustediron.png"
#define RUSTED_IRON_NORMAL "normal/rustediron.png"
#define RUSTED_IRON_METALIC "metalic/rustediron.png"
#define RUSTED_IRON_ROUGHNESS "roughness/rustediron.png"

//////////////////////////////
// Shader Data
//////////////////////////////
#define EMPTY_VERT     "empty_shader/empty.vert.glsl"
#define EMPTY_FRAG     "empty_shader/empty.frag.glsl"

#define SKYBOX_VERT    "skybox/skybox.vert.glsl"
#define SKYBOX_FRAG    "skybox/skybox.frag.glsl"

#define SHADOWMAP_VERT "shadow_mapping/shadowmap.vert.glsl"
#define SHADOWMAP_FRAG "shadow_mapping/shadowmap.frag.glsl"

#define SHADOW_CUBE_MAPPING_VERT "shadow_mapping/shadow_cube_mapping.vert.glsl"
#define SHADOW_CUBE_MAPPING_GEO  "shadow_mapping/shadow_cube_mapping.geo.glsl"
#define SHADOW_CUBE_MAPPING_FRAG "shadow_mapping/shadow_cube_mapping.frag.glsl"

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

#define EQUIRECTANGULAR_MAP_VERT "hdr/equirectangular_mapping.vert.glsl"
#define EQUIRECTANGULAR_MAP_FRAG "hdr/equirectangular_mapping.frag.glsl"

//////////////////////////////
// Debug Shader Data
//////////////////////////////

#define DEBUG_SHADOW_MAP_VERT "debug_purpose/debugshadowmap.vert.glsl"
#define DEBUG_SHADOW_MAP_FRAG "debug_purpose/debugshadowmap.frag.glsl"

#define DEBUG_POLYGON_VERT "debug_purpose/debug_polygon.vert.glsl"
#define DEBUG_POLYGON_GEO  "debug_purpose/debug_polygon.geo.glsl"
#define DEBUG_POLYGON_FRAG "debug_purpose/debug_polygon.frag.glsl"

#define DEBUG_NORMAL_COLOR_VERT "debug_purpose/debug_normal/debug_normal_color.vert.glsl"
#define DEBUG_NORMAL_COLOR_FRAG "debug_purpose/debug_normal/debug_normal_color.frag.glsl"

#define DEBUG_NORMAL_VECTOR_VERT "debug_purpose/debug_normal/debug_normal_vector.vert.glsl"
#define DEBUG_NORMAL_VECTOR_GEO  "debug_purpose/debug_normal/debug_normal_vector.geo.glsl"
#define DEBUG_NORMAL_VECTOR_FRAG "debug_purpose/debug_normal/debug_normal_vector.frag.glsl"

#define DEBUG_VIEW_VERT "debug_purpose/debug_viewdirection.vert.glsl"
#define DEBUG_VIEW_FRAG "debug_purpose/debug_viewdirection.frag.glsl"

#define DEBUG_LIGHT_DIRECTION_VERT "debug_purpose/debug_lightdirection.vert.glsl"
#define DEBUG_LIGHT_DIRECTION_FRAG "debug_purpose/debug_lightdirection.frag.glsl"

#define DEBUG_BP_BASIC_VERT "blinn_phong_model/blinn_phong_without_textures.vert.glsl"
#define DEBUG_BP_BASIC_FRAG "blinn_phong_model/blinn_phong_without_textures.frag.glsl"

#define DEBUG_PBR_BASIC_VERT "disney_pbr_model/disney_pbr_without_textures.vert.glsl"
#define DEBUG_PBR_BASIC_FRAG "disney_pbr_model/disney_pbr_without_textures.frag.glsl"



