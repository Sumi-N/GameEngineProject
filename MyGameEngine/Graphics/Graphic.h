#pragma once
#include "Define.h"
#include "SceneProxy.h"
#include "SceneEntity.h"
#include "ConstantBuffer.h"
#include "FrameBuffer.h"

// The data container data requires for render thread 
struct GraphicRequiredData
{
	ConstantData::Camera camera;
	std::vector<ConstantData::Model> model_data;
	std::vector<ConstantData::Material> material_data;
	ConstantData::Light  light;
	ConstantData::Shadow shadow;
};

class Graphic
{
public:
	static void Boot();
	static void Init();
	static bool PreUpdate();
	static void Update(GraphicRequiredData*);
	static void PostUpdate(GraphicRequiredData*);
	static void CleanUP();

#ifdef  ENGINE_GRAPHIC_OPENGL
	static GLFWwindow* window;
#endif //  ENGINE_GRAPHIC_OPENGL

	// Constant buffer variable
	static ConstantBuffer constant_camera;
	static ConstantBuffer constant_model;
	static ConstantBuffer constant_material;
	static ConstantBuffer constant_light;
	static ConstantBuffer constant_skybox;
	static ConstantBuffer constant_shadow;

	static FrameBuffer    frame_shadow;
	static FrameBuffer    frame_mirror;
};

inline void Graphic::Init()
{
	// Init uniform buffers
	constant_camera.Init(ConstantData::Index::Camera, ConstantData::Size::Camera);
	constant_model.Init(ConstantData::Index::Model, ConstantData::Size::Model);
	constant_material.Init(ConstantData::Index::Material, ConstantData::Size::Material);
	constant_light.Init(ConstantData::Index::Light, ConstantData::Size::Light);
	constant_skybox.Init(ConstantData::Index::SkyBox, ConstantData::Size::SkyBox);
	constant_shadow.Init(ConstantData::Index::Shadow, ConstantData::Size::Shadow);

	frame_shadow.Init(FrameType::Shadow, BASIC_TEXTURE_SIZE, BASIC_TEXTURE_SIZE);
	frame_mirror.Init(FrameType::Image, SCREEN_WIDTH, SCREEN_HEIGHT);
}
