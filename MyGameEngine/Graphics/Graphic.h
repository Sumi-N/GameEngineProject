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
	ConstantData::CubeMap shadow[MAX_POINT_LIGHT_NUM];
};

class Graphic
{
public:
	static void Boot();
	static void Init();
	static void PreCompute();
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
	static ConstantBuffer constant_cubemap;

	static FrameBuffer    frame_shadowcubemaps[MAX_POINT_LIGHT_NUM];
	static FrameBuffer    frame_cubemap;
	static FrameBuffer    frame_irradiance;
	static FrameBuffer    frame_specular;
	static FrameBuffer    frame_brdf;
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
	constant_cubemap.Init(ConstantData::Index::CubeMap, ConstantData::Size::CubeMap);


	// Init frame buffers
	for (int i = 0; i < MAX_POINT_LIGHT_NUM; i++)
	{
		frame_shadowcubemaps[i].Init(FrameType::ShadowCubeMap, SHADOWMAP_BINDING_UNIT1 + i, BASIC_TEXTURE_SIZE, BASIC_TEXTURE_SIZE);
	}
	frame_cubemap.Init(FrameType::EquirectangularMap, SKYBOX_BINDING_UNIT, HALF_TEXTURE_SIZE, HALF_TEXTURE_SIZE);
	frame_irradiance.Init(FrameType::IrradianceMap, IRRADIANCEMAP_BINDING_UNIT, MINI_TEXTURE_SIZE, MINI_TEXTURE_SIZE);
	frame_specular.Init(FrameType::Specular, SPECULAR_BINDING_UNIT, 128, 128);
	frame_brdf.Init(FrameType::BRDF, BRDF_BINDING_UNIT, 512, 512);
	//frame_mirror.Init(FrameType::Image, SCREEN_WIDTH, SCREEN_HEIGHT, -1);
}
