#pragma once
#include <Configuration/Configuration.h>

#include <Debug/DebugLog.h>

// For reading shader data in shader class
#include <vector>
#include <fstream>
#include <iostream>

#ifdef ENGINE_GRAPHIC_OPENGL
	#include <GraphicAPI/glew-2.1.0/include/GL/glew.h>
	#include <GraphicAPI/glfw-3.3.bin.WIN32/include/GLFW/glfw3.h>
#endif // ENGINE_GRAPHIC_OPENGL