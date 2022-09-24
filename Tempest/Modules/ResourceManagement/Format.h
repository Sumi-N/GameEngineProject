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
		R8G8A8_SRGB,
		R8G8B8A8_SRGB,
		R16G16_SFLOAT,
		R32G32B32_SFLOAT,
		D32_SFLOAT,
		D32_SFLOAT_S8_UINT,
		D24_UNORM_S8_UINT,
		Size,
	};

	static uint32_t GetTextureFormatSize(TextureFormat i_format)
	{
		switch (i_format)
		{
		case TextureFormat::R8G8A8_SRGB:           return 3;
		case TextureFormat::R8G8B8A8_SRGB:         return 4;
		case TextureFormat::R16G16_SFLOAT:         return 8;
		case TextureFormat::R32G32B32_SFLOAT:      return 12;
		case TextureFormat::D32_SFLOAT:            return 8;
		case TextureFormat::D32_SFLOAT_S8_UINT:    return 10;
		case TextureFormat::D24_UNORM_S8_UINT:     return 8;
		}
		DEBUG_ASSERT(false);
		return 0;
	}

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
