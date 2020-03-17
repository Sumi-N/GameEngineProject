#pragma once
#include "Define.h"
#include "SceneProxy.h"
#include "SceneFormat.h"
#include "ConstantBuffer.h"

// The data container data requires for render thread 
struct GraphicRequiredData
{
	ConstantData::Camera camera;
	ConstantData::Light  light;
	std::vector<ConstantData::Model> model_data;
};

class Graphic
{
public:
	static void Init();
	static void PostInit();
	static void PreUpdate();
	static void Update(GraphicRequiredData*);
	static void PostUpdate();
	static void CleanUP();

#ifdef  ENGINE_GRAPHIC_OPENGL
	static GLFWwindow* window;
#endif //  ENGINE_GRAPHIC_OPENGL

	// Constant buffer variable
	static ConstantBuffer buffer_camera;
	static ConstantBuffer buffer_light;
	static ConstantBuffer buffer_model;
};

inline void Graphic::PostInit()
{
	SceneFormat::Init();
}