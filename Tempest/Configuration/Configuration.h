#pragma once
#include <stdint.h>

//----------------------------
//  Custom heap allocator
//----------------------------
#define ENABLE_CUSTOM_ALLOCATOR

#ifndef ENABLE_CUSTOM_ALLOCATOR
	#define USE_STANDARD_ARRAY
#else	
	#define HEAP_SIZE      1024*1024*1024
	#define NUM_DESCRIPTOR 2048
	
#endif // ENABLE_CUSTOM_ALLOCATOR

//----------------------------
//  Graphic API configuration
//----------------------------

#define ENGINE_GRAPHIC_OPENGL
// #define ENGINE_GRAPHIC_VULKAN


//  Asking GLEW to compile with static library
// This line should be put before #include <GL/glew.h>
#define GLEW_STATIC

//----------------------------
//   Math configuration
//----------------------------
// #define _USEINTRINSIC_


//----------------------------
//  Platform configuration
//----------------------------
#define ENGINE_PLATFORM_WINDOWS

//----------------------------
//  Editor configuration
//----------------------------
#define ENGINE_USE_EDITOR

//----------------------------
//  Screen Setting
//----------------------------
constexpr uint32_t ScreenWidth = 1920;
constexpr uint32_t ScreenHeight = 1080;
constexpr float NearClip = 0.1f;
constexpr float FarClip = 100.0f;
constexpr float FieldOfView = 45.0f;
constexpr float FramePerSecond = 60.0f;

//----------------------------
//  Graphics Setting
//----------------------------

//  Make sure to change the shader codes if the number here have been changed
#define NUM_MAX_POINT_LIGHT 5
#define BASIC_TEXTURE_SIZE 1024
#define HALF_TEXTURE_SIZE 512
#define MINI_TEXTURE_SIZE 32
#define NUM_DICE_FACES 6
#define NUM_MAX_BONES 256

//----------------------------
//  General Asset Path
//----------------------------
#define PATH_SUFFIX      "..\\"
#define SHADER_PATH      "Assets\\shaders\\"
#define INT_MESH_PATH    "Assets\\int\\mesh\\"
#define BIN_MESH_PATH    "Assets\\bin\\mesh\\"
#define INT_TEXTURE_PATH "Assets\\int\\texture\\"
#define BIN_TEXTURE_PATH "Assets\\bin\\texture\\"
#define FONT_PATH        "Assets\\fonts\\"

//----------------------------
// Mesh Data
//----------------------------

#define FILENAME_CUBEMAP "cubemap.tm"
#define FILENAME_QUAD    "quad.tm"
#define FILENAME_SPHERE  "sphere.tm"
#define FILENAME_CAMERA  "camera.tm"

//----------------------------
//  Texture Data
//----------------------------

#define SKYBOX_POSX      "skybox\\cubemap_posx.png"
#define SKYBOX_NEGX      "skybox\\cubemap_negx.png"
#define SKYBOX_POSY      "skybox\\cubemap_posy.png"
#define SKYBOX_NEGY      "skybox\\cubemap_negy.png"
#define SKYBOX_POSZ      "skybox\\cubemap_posz.png"
#define SKYBOX_NEGZ      "skybox\\cubemap_negz.png"

#define SKYBOX_HDR_BLACK            "hdr\\black.tt"
#define SKYBOX_HDR_PINTREE          "hdr\\Arches_E_PineTree_3k.tt"
#define SKYBOX_HDR_FROZEN_WATERFALL "hdr\\Frozen_Waterfall_Ref.tt"

//----------------------------
//  Shader Data
//----------------------------
#define EMPTY_VERT     "empty_shader\\empty.vert.glsl"
#define EMPTY_FRAG     "empty_shader\\empty.frag.glsl"

#define SKYBOX_VERT    "skybox\\skybox.vert.glsl"
#define SKYBOX_FRAG    "skybox\\skybox.frag.glsl"

#define SHADOWMAP_VERT "shadow_mapping\\shadowmap.vert.glsl"
#define SHADOWMAP_FRAG "shadow_mapping\\shadowmap.frag.glsl"

#define SHADOW_CUBE_MAPPING_VERT "shadow_mapping\\shadow_cube_mapping.vert.glsl"
#define SHADOW_CUBE_MAPPING_GEO  "shadow_mapping\\shadow_cube_mapping.geo.glsl"
#define SHADOW_CUBE_MAPPING_FRAG "shadow_mapping\\shadow_cube_mapping.frag.glsl"

#define MIRROR_VERT     "mirror\\mirror.vert.glsl"
#define MIRROR_FRAG     "mirror\\mirror.frag.glsl"

#define BLINN_PHONG_VERT "blinn_phong_model\\blinn_phong.vert.glsl"
#define BLINN_PHONG_FRAG "blinn_phong_model\\blinn_phong.frag.glsl"

#define DISNEY_PBR_VERT  "disney_pbr_model\\disney_pbr.vert.glsl"
#define DISNEY_PBR_FRAG  "disney_pbr_model\\disney_pbr.frag.glsl"

#define PBR_ANIMATION_VERT "disney_pbr_model\\disney_pbr_animation.vert.glsl"
#define PBR_ANIMATION_FRAG "disney_pbr_model\\disney_pbr_animation.frag.glsl"

#define NORMAL_MAP_VERT  "test_purpose\\normal_mapping.vert.glsl"
#define NORMAL_MAP_FRAG  "test_purpose\\normal_mapping.frag.glsl"

#define EQUIRECTANGULAR_MAP_VERT "image_base_rendering\\equirectangular_mapping.vert.glsl"
#define EQUIRECTANGULAR_MAP_GEO  "image_base_rendering\\equirectangular_mapping.geo.glsl"
#define EQUIRECTANGULAR_MAP_FRAG "image_base_rendering\\equirectangular_mapping.frag.glsl"
#define CUBEMAP_CONVOLUTION_DIFFUSE_FRAG "image_base_rendering\\cubemap_diffuse_convolution.frag.glsl"
#define CUBEMAP_CONVOLUTION_SPECULAR_FRAG "image_base_rendering\\cubemap_specular_convolution.frag.glsl"
#define IBL_BRDF_VERT "image_base_rendering\\brdf_integration_map.vert.glsl"
#define IBL_BRDF_FRAG "image_base_rendering\\brdf_integration_map.frag.glsl"

//----------------------------
// Debug Shader Data
//----------------------------

#define DEBUG_SHADOW_MAP_VERT "debug_purpose\\debugshadowmap.vert.glsl"
#define DEBUG_SHADOW_MAP_FRAG "debug_purpose\\debugshadowmap.frag.glsl"

#define DEBUG_POLYGON_VERT "debug_purpose\\debug_polygon.vert.glsl"
#define DEBUG_POLYGON_GEO  "debug_purpose\\debug_polygon.geo.glsl"
#define DEBUG_POLYGON_FRAG "debug_purpose\\debug_polygon.frag.glsl"

#define DEBUG_NORMAL_COLOR_VERT "debug_purpose\\debug_normal\\debug_normal_color.vert.glsl"
#define DEBUG_NORMAL_COLOR_FRAG "debug_purpose\\debug_normal\\debug_normal_color.frag.glsl"

#define DEBUG_NORMAL_VECTOR_VERT "debug_purpose\\debug_normal\\debug_normal_vector.vert.glsl"
#define DEBUG_NORMAL_VECTOR_GEO  "debug_purpose\\debug_normal\\debug_normal_vector.geo.glsl"
#define DEBUG_NORMAL_VECTOR_FRAG "debug_purpose\\debug_normal\\debug_normal_vector.frag.glsl"

#define DEBUG_VIEW_VERT "debug_purpose\\debug_viewdirection.vert.glsl"
#define DEBUG_VIEW_FRAG "debug_purpose\\debug_viewdirection.frag.glsl"

#define DEBUG_LINE_VERT "debug_purpose\\debug_line.vert.glsl"
#define DEBUG_LINE_FRAG "debug_purpose\\debug_line.frag.glsl"

#define DEBUG_LIGHT_DIRECTION_VERT "debug_purpose\\debug_lightdirection.vert.glsl"
#define DEBUG_LIGHT_DIRECTION_FRAG "debug_purpose\\debug_lightdirection.frag.glsl"

#define DEBUG_BP_BASIC_VERT "blinn_phong_model\\blinn_phong_without_textures.vert.glsl"
#define DEBUG_BP_BASIC_FRAG "blinn_phong_model\\blinn_phong_without_textures.frag.glsl"

#define DEBUG_PBR_BASIC_VERT "disney_pbr_model\\disney_pbr_without_textures.vert.glsl"
#define DEBUG_PBR_BASIC_FRAG "disney_pbr_model\\disney_pbr_without_textures.frag.glsl"

#define DEBUG_PBR_ANIMATION_VERT "disney_pbr_model\\disney_pbr_animation_without_textures.vert.glsl"
#define DEBUG_PBR_ANIMATION_FRAG "disney_pbr_model\\disney_pbr_animation_without_textures.frag.glsl"
