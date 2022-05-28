#pragma once
#include "Define.h"
#include "SceneEntity.h"
#include "ConstantBuffer.h"
#include "FrameBuffer.h"
#include "DrawPrimitives.h"

// The data container data requires for render thread
struct GraphicRequiredData
{
public:
	ConstantData::Camera camera;
	ConstantData::Light  light;	
	Array<ConstantData::AnimationBone> animation_bone_data;
	Array<ConstantData::Model> model_data;
	Array<ConstantData::Material> material_data;
	ConstantData::CubeMap shadow[NUM_MAX_POINT_LIGHT];
	ConstantData::Camera editor_camera;
	Array<bool> is_shader_enable;
};

class Graphic
{
public:
	static void Boot();
	static void Init(unsigned int, unsigned int);
	static void PreCompute();
	static void PreUpdate(GraphicRequiredData*);
	static void Update(GraphicRequiredData*);
	static void PostUpdate(GraphicRequiredData*);
	static void CleanUp();
	static void ChangeViewPortSize(unsigned int, unsigned int);

	// Constant buffer variable
	static ConstantBuffer ConstBufferCamera;
	static ConstantBuffer ConstBufferModel;
	static ConstantBuffer ConstBufferMaterial;
	static ConstantBuffer ConstBufferLight;
	static ConstantBuffer ConstBufferSkybox;
	static ConstantBuffer ConstBufferCubeMap;
	static ConstantBuffer ConstBufferAnimationBone;

	static ConstantData::Camera ConstDataCamera;

	static FrameBuffer    FrameBufferShadowMaps[NUM_MAX_POINT_LIGHT];
	static FrameBuffer    FrameBufferCubeMap;
	static FrameBuffer    FrameBufferIrradiance;
	static FrameBuffer    FrameBufferSpecular;
	static FrameBuffer    FrameBufferBrdf;
	static FrameBuffer    FrameBufferImage;

private:
	static unsigned int ViewportWidth;
	static unsigned int ViewportHeight;
};

inline void Graphic::Init(unsigned int i_width, unsigned int i_height)
{
	// Init viewport size for OpenGL
	ViewportWidth = i_width;
	ViewportHeight = i_height;

	// Init uniform buffers
	ConstBufferCamera.Init(ConstantData::Index::Camera);
	ConstBufferModel.Init(ConstantData::Index::Model);
	ConstBufferMaterial.Init(ConstantData::Index::Material);
	ConstBufferLight.Init(ConstantData::Index::Light);
	ConstBufferSkybox.Init(ConstantData::Index::SkyBox);
	ConstBufferCubeMap.Init(ConstantData::Index::CubeMap);
	ConstBufferAnimationBone.Init(ConstantData::Index::AnimationBone);

	// Init frame buffers
	for (int i = 0; i < NUM_MAX_POINT_LIGHT; i++)
	{
		FrameBufferShadowMaps[i].Init(FrameType::ShadowCubeMap, SHADOWMAP_BINDING_UNIT1 + i, BASIC_TEXTURE_SIZE, BASIC_TEXTURE_SIZE);
	}
	FrameBufferCubeMap.Init(FrameType::EquirectangularMap, SKYBOX_BINDING_UNIT, HALF_TEXTURE_SIZE, HALF_TEXTURE_SIZE);
	FrameBufferIrradiance.Init(FrameType::IrradianceMap, IRRADIANCEMAP_BINDING_UNIT, MINI_TEXTURE_SIZE, MINI_TEXTURE_SIZE);
	FrameBufferSpecular.Init(FrameType::Specular, SPECULAR_BINDING_UNIT, 128, 128);
	FrameBufferBrdf.Init(FrameType::BRDF, BRDF_BINDING_UNIT, 512, 512);
	FrameBufferImage.Init(FrameType::Image, IMAGE_BINDING_UNIT, ViewportWidth, ViewportHeight);

	// This class holds some of the basic geometry shapes (like cube line and quad) that will be used during the rendering
	DrawPrimitive::Init();
	DrawPrimitive::DebugInit();
}

inline void Graphic::ChangeViewPortSize(unsigned int i_width, unsigned int i_height)
{
	ViewportWidth = i_width;
	ViewportHeight = i_height;
}
