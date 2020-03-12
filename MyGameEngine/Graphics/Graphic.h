#pragma once
#include "Define.h"
#include "SceneProxy.h"
#include "SceneFormat.h"

class Graphic
{
public:
	static void Init();
	static void PostInit();
	static void Update();
	static void CleanUP();

#ifdef  ENGINE_GRAPHIC_OPENGL
	static GLFWwindow* window;
#endif //  ENGINE_GRAPHIC_OPENGL

};

inline void Graphic::PostInit()
{
	SceneFormat::Init();
}