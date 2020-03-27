#pragma once
#include <Configuration/Configuration.h>

#include <Debug/DebugLog.h>
#include <Math/Matrix.h>
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
#define SKYBOXBINDINGUNIT            0
#define TEXTUREUNITBINDINGSTARTPOINT 1
#define SHADOWMAPBINDINGUNIT         3


/////////////////////
#define BASIC_TEXTURE_SIZE 1024