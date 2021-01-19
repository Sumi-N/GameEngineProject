#pragma once

#include <stdio.h>

#include <Logging/DebugLog.h>
#include <Logging/Assert.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Math/Quaternion.h>

#include <APIs/ImporterAPI/FBX SDK/2020.0.1/include/fbxsdk.h>
#include <APIs/ImporterAPI/tinyobjloader/tiny_obj_loader.h>
#include <APIs/ImporterAPI/loadpng/lodepng.h>
#pragma warning(disable : 4996)
#include <APIs/ImporterAPI/cyCodeBase/cyTriMesh.h>