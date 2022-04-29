#pragma once

#include "Define.h"
#include "Entity.h"

namespace Tempest {
	class EntityCopy
	{
	public:
		static Array<ObjectHandler>             ObjectListCopy;
		static Array<Owner<CameraObject>>       CamerasObjectsCopy;
		static Array<Owner<PointLight>>         PointLightListCopy;
		static Array<Owner<MeshComponent>>      MeshComponentListCopy;
		static Array<Owner<EffectComponent>>    EffectComponentListCopy;

		static Owner<CubeMap>                   SkyboxCopy;
		static Owner<AmbientLight>              AmbientLightCopy;
		static Owner<DirectionalLight>          DirectionalLightCopy;
		
		static void Init();
	};
}

