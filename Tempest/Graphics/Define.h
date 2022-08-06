#pragma once
#include <Configuration/Configuration.h>

#include <Input/ApplicationEvent.h>
#include <Input/KeyEvent.h>
#include <Input/MouseEvent.h>
#include <Logging/DebugLog.h>
#include <Math/Matrix.h>
#include <MemoryManagement/SmartPointer.h>
#include <EntitySystem/Object.h>
#include <EntitySystem/MeshComponent.h>
#include <EntitySystem/Entity.h>
#include <Utility/Array.h>

// For reading shader data in shader class
#include <fstream>
#include <iostream>
#include <functional>
#include <optional>
#include <set>

#ifdef ENGINE_GRAPHIC_OPENGL

	#pragma comment(lib, "opengl32.lib")

	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
	#define GLFW_EXPOSE_NATIVE_WIN32
	#include <GLFW/glfw3native.h>


#else ENGINE_GRAPHIC_VULKAN

	#pragma comment(lib, "vulkan-1.lib")

	#include <vulkan/vulkan.h>
	#include <vulkan/vulkan_win32.h>
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
	#define GLFW_EXPOSE_NATIVE_WIN32
	#include <GLFW/glfw3native.h>	

#endif // ENGINE_GRAPHIC_OPENGL

// Texture unit
///////////////////
#define SKYBOX_BINDING_UNIT              0
#define IRRADIANCEMAP_BINDING_UNIT       1
#define SHADOWMAP_BINDING_UNIT1          2
#define SHADOWMAP_BINDING_UNIT2          3
#define SHADOWMAP_BINDING_UNIT3          4
#define SHADOWMAP_BINDING_UNIT4          5
#define SHADOWMAP_BINDING_UNIT5          6
#define SPECULAR_BINDING_UNIT            7
#define BRDF_BINDING_UNIT                8
#define IMAGE_BINDING_UNIT               9
