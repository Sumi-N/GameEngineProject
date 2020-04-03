#pragma once
#include <Configuration/Configuration.h>

#include <Debug/DebugLog.h>
#include <Math/Matrix.h>
#include <Parts/Object.h>
#include <Parts/MeshComponent.h>
#include <Parts/CubeMapMeshComponent.h>
#include <Parts/TextureAttribute.h>
#include <BoneStructure/SmartPointer.h>
#include <EntitySystem/Entity.h>

// For reading shader data in shader class
#include <vector>
#include <fstream>
#include <iostream>

#ifdef ENGINE_GRAPHIC_OPENGL
	#include <APIs/GraphicAPI/glew-2.1.0/include/GL/glew.h>
	#include <APIs/GraphicAPI/glfw-3.3.bin.WIN32/include/GLFW/glfw3.h>
#endif // ENGINE_GRAPHIC_OPENGL

// Texture unit
///////////////////
#define SKYBOX_BINDING_UNIT              0
#define SHADOWMAP_BINDING_UNIT           1
#define IMAGE_BINDING_UNIT               2
#define TEXTURE_UNIT_BINDING_OFFSET 3


/////////////////////
#define BASIC_TEXTURE_SIZE 1024
