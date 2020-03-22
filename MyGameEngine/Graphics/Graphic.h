#pragma once
#include "Define.h"
#include "SceneProxy.h"
#include "SceneEntity.h"
#include "ConstantBuffer.h"

// The data container data requires for render thread 
struct GraphicRequiredData
{
	ConstantData::Camera camera;
	ConstantData::Light  light;
	std::vector<ConstantData::Model> model_data;
	std::vector<ConstantData::Material> material_data;
};

class Graphic
{
public:
	static void Boot();
	static bool PreUpdate();
	static void Init();
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
	static ConstantBuffer buffer_material;
};

inline void Graphic::Init()
{
	// Init uniform buffers
	buffer_camera.Init(ConstantData::Index::Camera, ConstantData::Size::Camera);
	buffer_light.Init(ConstantData::Index::Light, ConstantData::Size::Light);
	buffer_model.Init(ConstantData::Index::Model, ConstantData::Size::Model);
	buffer_material.Init(ConstantData::Index::Material, ConstantData::Size::Material);
}
