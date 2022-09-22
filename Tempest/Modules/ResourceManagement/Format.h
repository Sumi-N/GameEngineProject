#pragma once

namespace Tempest
{
	enum class LightType : uint8_t
	{
		Uninitialized = 0,
		AmbientLight = 1,
		PointLight = 2,
		DirectionalLight = 3,
		Size,
	};

	enum class TextureType : uint8_t
	{
		Default = 0,
		SkyBox = 1,
		Albedo = 2,
		Normal = 3,
		Roughness = 4,
		Metalic = 5,
		AmbientOcclusion = 6,
		Size,
	};

	enum class MeshType : uint8_t
	{
		Mesh = 0,
		SkeletonMesh = 1,
		Size,
	};

	enum class ShaderType : uint8_t
	{
		Vertex = 0,
		Control = 1,
		Evaluation = 2,
		Geometry = 3,
		Fragment = 4,
		Compute = 5,
		Size,
	};

	enum class ShaderDescriptorType : uint8_t
	{
		Sampler,
		CombinedImageSampler,
		SapmledImage,
		StorageImage,
		UniformTexelBuffer,
		StorageTexelBuffer,
		UniformBuffer,
		StorageBuffer,
		Size,
	};

	enum class TextureFormat : uint32_t
	{
		R8G8A8_SRGB = 3,
		R8G8B8A8_SRGB = 4,
		R16G16_SFLOAT = 8,
		R32G32B32_SFLOAT = 12,
		D32_SFLOAT = 8,
		D32_SFLOAT_S8_UINT = 10,
		D24_UNORM_S8_UINT = 8,
		Size,
	};

	enum TextureAspect
	{
		COLOR_BIT_ASPECT   = 0x00000001,
		DEPTH_BIT_ASPECT   = 0x00000002,
		STENCIL_BIT_ASPECT = 0x00000004,
	};

	enum TextureUsage
	{
		USAGE_TRANSFER_SRC_BIT = 0x00000001,
		USAGE_TRANSFER_DST_BIT = 0x00000002,
		USAGE_SAMPLED_BIT = 0x00000004,
		USAGE_STORAGE_BIT = 0x00000008,
		USAGE_COLOR_ATTACHMENT_BIT = 0x00000010,
		USAGE_DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000020,
		USAGE_TRANSIENT_ATTACHMENT_BIT = 0x00000040,
		USAGE_INPUT_ATTACHMENT_BIT = 0x00000080,
	};
}
