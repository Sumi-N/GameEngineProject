#pragma once
#include <Configuration/Configuration.h>

#include <Logging/DebugLog.h>
#include <Math/Matrix.h>
#include <ResourceManagement/ResourceData.h>
#include <MemoryManagement/SmartPointer.h>
#include <Utility/Array.h>

#if ENGINE_GRAPHIC_VULKAN
	#pragma comment(lib, "vulkan-1.lib")

	#include <vulkan/vulkan.h>
#ifdef ENGINE_PLATFORM_WINDOWS
	#include <vulkan/vulkan_win32.h>
#endif // ENGINE_PLATFORM_WINDOWS

	//#include <GL/glew.h>
	#include <GLFW/glfw3.h>
	#define GLFW_EXPOSE_NATIVE_WIN32
	#include <GLFW/glfw3native.h>

#endif // ENGINE_GRAPHIC_VULKAN
