#pragma once
#include "Define.h"
#include "SceneProxy.h"

class Graphic
{
public:
	static void Init();
	static void Load(ObservingPointer<MeshComponent>);
	static void Update();
	static void Unload();
	static void CleanUP();

#ifdef  ENGINE_GRAPHIC_OPENGL
	static GLFWwindow* window;
#endif //  ENGINE_GRAPHIC_OPENGL

};
