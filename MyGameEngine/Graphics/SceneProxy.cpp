#pragma once

#include "SceneProxy.h"

void SceneProxy::Init()
{
	InitBuffer();
	InitMeshData();
	InitTexture();
}

void SceneProxy::AddRenderState(OwningPointer<RenderState> i_state)
{
	states.push_back(i_state);
}

void SceneProxy::CleanUp()
{

}