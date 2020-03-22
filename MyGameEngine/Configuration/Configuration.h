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

