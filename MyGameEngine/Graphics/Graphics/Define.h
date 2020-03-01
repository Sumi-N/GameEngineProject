#pragma once

#define ENGINE_GRAPHIC_OPENGL
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

#ifdef ENGINE_GRAPHIC_OPENGL
	#pragma comment( lib, "Opengl32.lib" )
#endif // ENGINE_GRAPHIC_OPENGL
