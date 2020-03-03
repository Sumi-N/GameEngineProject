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
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define NEARCLIP 0.1f
#define FARCLIP  100.0f

