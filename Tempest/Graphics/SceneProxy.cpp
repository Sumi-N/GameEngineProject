#pragma once

#include "SceneProxy.h"

void SceneProxy::Init()
{
	InitBuffer();
	InitMeshData();
}

void SceneProxy::AddRenderState(OwningPointer<RenderState> i_state)
{
	states.push_back(i_state);
}

void SceneProxy::ReplaceRenderState(OwningPointer<RenderState> i_state, int i_th_item = 0)
{
	states[i_th_item] = i_state;
}

void SceneProxy::CleanUp()
{

}

void SceneProxy::CheckDrawType(Shader i_shader)
{
	if (i_shader.HasTessellationShader())
		drawtype = DrawType::PATCHES;
	else
		drawtype = originaltype;
}