#pragma once
#include <Configuration/Configuration.h>

#include <Logging/DebugLog.h>
#include <Math/Matrix.h>
#include <Parts/Object.h>
#include <Parts/MeshComponent.h>
#include <Parts/TextureAttribute.h>
#include <MemoryManagement/SmartPointer.h>
#include <EntitySystem/Entity.h>

// For reading shader data in shader class
#include <vector>
#include <fstream>
#include <iostream>

#ifdef ENGINE_GRAPHIC_OPENGL

	#pragma comment(lib, "opengl32.lib")

	#include <APIs/GraphicAPI/glew-2.1.0/include/GL/glew.h>
	#include <APIs/GraphicAPI/glfw-3.3.bin.WIN32/include/GLFW/glfw3.h>
	#define GLFW_EXPOSE_NATIVE_WIN32
	#include <APIs/GraphicAPI/glfw-3.3.bin.WIN32/include/GLFW/glfw3native.h>


#elif ENGINE_GRAPHIC_VULKAN

	#pragma comment(lib, "vulkan-1.lib");

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


/////////////////////
#define BASIC_TEXTURE_SIZE 1024
#define HALF_TEXTURE_SIZE 512
#define MINI_TEXTURE_SIZE 32