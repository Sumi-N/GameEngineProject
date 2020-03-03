#pragma once
#include <Configuration/Configuration.h>

#include <Core/Debug/DebugLog.h>

// For reading shader data in shader class
#include <vector>
#include <fstream>
#include <iostream>

#ifdef ENGINE_GRAPHIC_OPENGL
	#pragma comment( lib, "Opengl32.lib" )
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>	
#endif // ENGINE_GRAPHIC_OPENGL