#pragma once
#include "Define.h"
#include "SceneProxy.h"
#include "SceneFormat.h"
#include "ConstantBuffer.h"

// The data container data requires for render thread 
struct GraphicRequiredData
{
	ConstantData::Camera camera;
	ConstantData::AmbientLight  ambientlight;
	ConstantData::PointLight pointlight;
	ConstantData::DirectionalLight directionallight;
	std::vector<ConstantData::Model> model_data;
	std::vector<ConstantData::Material> material_data;
};

class Graphic
{
public:
	static void Init();
	static bool PreUpdate();
	static void PostInit();
	static void Update(GraphicRequiredData*);
	static void PostUpdate();
	static void CleanUP();

#ifdef  ENGINE_GRAPHIC_OPENGL
	static GLFWwindow* window;
#endif //  ENGINE_GRAPHIC_OPENGL

	// Constant buffer variable
	static ConstantBuffer buffer_camera;
	static ConstantBuffer buffer_ambientlight;
	static ConstantBuffer buffer_pointlight;
	static ConstantBuffer buffer_directionallight;
	static ConstantBuffer buffer_model;
	static ConstantBuffer buffer_material;
};

inline void Graphic::PostInit()
{
	SceneFormat::Init();

	// Init uniform buffers
	buffer_camera.Init(ConstantData::Index::Camera, ConstantData::Size::Camera);
	buffer_ambientlight.Init(ConstantData::Index::AmbientLight, ConstantData::Size::AmbientLight);
	buffer_pointlight.Init(ConstantData::Index::PointLight, ConstantData::Size::PointLight);
	buffer_directionallight.Init(ConstantData::Index::DirectionalLight, ConstantData::Size::DirectionalLight);
	buffer_model.Init(ConstantData::Index::Model, ConstantData::Size::Model);
	buffer_material.Init(ConstantData::Index::Material, ConstantData::Size::Material);
}
