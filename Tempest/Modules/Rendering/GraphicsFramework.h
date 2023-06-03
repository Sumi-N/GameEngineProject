#pragma once

#include <Graphics/Buffer.h>
#include <Graphics/CommandBuffer.h>
#include <Graphics/ConstantBuffer.h>
#include <Graphics/Descriptor.h>
#include <Graphics/Device.h>
#include <Graphics/FrameBuffer.h>
#include <Graphics/Pipeline.h>
#include <Graphics/RenderPass.h>
#include <Graphics/SwapChain.h>
#include <Graphics/Sync.h>
#include <Graphics/UniformBuffer.h>
#include <Graphics/VertexBuffer.h>

namespace Tempest
{
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

	class GraphicsFramework
	{
	public:
		void Boot(Window* i_window);
		void Init(uint32_t, uint32_t);
		void CleanUp();
		void PreCompute();
		void PreUpdate(GraphicRequiredData*);
		void Update(GraphicRequiredData*);
		void PostUpdate(GraphicRequiredData*);
		void ChangeViewportSize(uint32_t, uint32_t);

		const Device&    GetDevice()    { return device; };
		const SwapChain& GetSwapChain() { return swapChain; };

	private:
		Device device;
		SwapChain swapChain;
		CommandBuffer commandBuffers[Graphics::BufferingCount];
		RenderPass renderPass;
		Array<FrameBuffer> frameBuffers;
		Fence frameworkFence[Graphics::BufferingCount];
		Semaphore imageDoneSemaphore[Graphics::BufferingCount];
		Semaphore presentableSemaphore[Graphics::BufferingCount];

		uint32_t currentFrame;
	};

	//inline void Framework::Init(uint32_t i_width, uint32_t i_height)
	//{
	//	// Init viewport size for OpenGL
	//	ViewportWidth = i_width;
	//	ViewportHeight = i_height;

	//	// Init uniform buffers
	//	ConstBufferCamera.Init(ConstantData::Index::Camera);
	//	ConstBufferModel.Init(ConstantData::Index::Model);
	//	ConstBufferMaterial.Init(ConstantData::Index::Material);
	//	ConstBufferLight.Init(ConstantData::Index::Light);
	//	ConstBufferSkybox.Init(ConstantData::Index::SkyBox);
	//	ConstBufferCubeMap.Init(ConstantData::Index::CubeMap);
	//	ConstBufferAnimationBone.Init(ConstantData::Index::AnimationBone);

	//	// Init frame buffers
	//	for (int i = 0; i < NUM_MAX_POINT_LIGHT; i++)
	//	{
	//		FrameBufferShadowMaps[i].Init(FrameType::ShadowCubeMap, SHADOWMAP_BINDING_UNIT1 + i, BASIC_TEXTURE_SIZE, BASIC_TEXTURE_SIZE);
	//	}
	//	FrameBufferCubeMap.Init(FrameType::EquirectangularMap, SKYBOX_BINDING_UNIT, HALF_TEXTURE_SIZE, HALF_TEXTURE_SIZE);
	//	FrameBufferIrradiance.Init(FrameType::IrradianceMap, IRRADIANCEMAP_BINDING_UNIT, MINI_TEXTURE_SIZE, MINI_TEXTURE_SIZE);
	//	FrameBufferSpecular.Init(FrameType::Specular, SPECULAR_BINDING_UNIT, 128, 128);
	//	FrameBufferBrdf.Init(FrameType::BRDF, BRDF_BINDING_UNIT, 512, 512);
	//	FrameBufferImage.Init(FrameType::Image, IMAGE_BINDING_UNIT, ViewportWidth, ViewportHeight);

	//	// This class holds some of the basic geometry shapes (like cube line and quad) that will be used during the rendering
	//	DrawPrimitive::Init();
	//	DrawPrimitive::DebugInit();
	//}
}