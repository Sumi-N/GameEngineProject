#pragma once

#include "SceneProxy.h"

void SceneProxy::Init()
{
	InitBuffer();
}

void SceneProxy::AddRenderState(OwningPointer<RenderState> i_state)
{
	states.PushBack(i_state);
}

void SceneProxy::ReplaceRenderState(OwningPointer<RenderState> i_state, int i_th_item = 0)
{
	states[i_th_item] = i_state;
}

void SceneProxy::CleanUp()
{

}

void SceneProxy::InitBuffer()
{
	if (vbuffer.CheckStructDataSize(sizeof(mesh->data[0])))
	{
		vbuffer.InitData(static_cast<uint32_t>(mesh->data.Size()) * sizeof(mesh->data[0]), mesh->data.Data());
	}
	ibuffer.InitData(static_cast<uint32_t>(mesh->index.Size()) * sizeof(mesh->index[0]), mesh->index.Data());

	// Memorize index size for Draw() fucntion
	indexsize = static_cast<unsigned int>(mesh->index.Size()) * sizeof(mesh->index[0]);
}

void SceneProxy::CheckDrawType(const Shader i_shader)
{
	if (i_shader.HasTessellationShader())
		drawtype = DrawType::PATCHES;
	else
		drawtype = defaulttype;
}

void SceneProxy::CleanUpBuffer() const
{
	vbuffer.CleanUp();
	ibuffer.CleanUp();
}