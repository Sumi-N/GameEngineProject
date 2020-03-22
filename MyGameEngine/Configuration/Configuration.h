#pragma once

////////////////////////////
// Graphic API configuration
////////////////////////////
#define ENGINE_GRAPHIC_OPENGL


// Asking GLEW to compile with static library
// This line should be put before #include <GL/glew.h>
#define GLEW_STATIC

///////////////////////////
//  Math configuration
///////////////////////////
#define _USEINTRINSIC_


////////////////////////////
//  Platform configuration
////////////////////////////
#define ENGINE_PLATFORM_WINDOWS


//////////////////////////////
// Screen Setting
//////////////////////////////
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NEARCLIP 0.1f
#define FARCLIP  100.0f


//////////////////////////////
// Light Setting
//////////////////////////////

// Make sure to change the sharer's code if the number here got changed
#define MAX_POINT_LIGHT_NUM 5


//////////////////////////////
// Asset Addresses
//////////////////////////////
#define MESH_PATH        "Assets/models/"
#define FILENAME_CUBEMAP "cubemap.obj"

#define SKYBOX_PATH      "Assets/textures/skyboxes/"
#define SKYBOX_POSX      "cubemap_posx.png"
#define SKYBOX_NEGX      "cubemap_negx.png"
#define SKYBOX_POSY      "cubemap_posy.png"
#define SKYBOX_NEGY      "cubemap_negy.png"
#define SKYBOX_POSZ      "cubemap_posz.png"
#define SKYBOX_NEGZ      "cubemap_negz.png"