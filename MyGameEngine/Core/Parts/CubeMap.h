#pragma once

#include "Define.h"
#include "Object.h"
#include "MeshComponent.h"
#include "EffectComponent.h"

class CubeMap : public Object
{
public:
	CubeMap(): mesh(nullptr), effect(nullptr){}
	virtual void Boot() override;
	OwningPointer<MeshComponent> mesh;
	OwningPointer<EffectComponent> effect;
};

inline void CubeMap::Boot()
{
	Object::Boot();
}
