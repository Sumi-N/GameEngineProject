#pragma once
#include <Configuration/Configuration.h>
#include <BoneStructure/SmartPointer.h>
#include <Debug/Assert.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>

#include <vector>

// Temporary API, might be replaced later
#include <APIs/GraphicAPI/tinyobjloader/tiny_obj_loader.h>
#include <APIs/GraphicAPI/loadpng/lodepng.h>

#define FILENAME_QUAD "quad.obj"
#define QUAD_VERT     "quad.vert.glsl"
#define QUAD_FRAG     "quad.frag.glsl"