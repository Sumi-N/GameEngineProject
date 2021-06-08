#pragma once

#include "SceneProxy.h"

void SceneProxy::Init()
{
	InitBuffer();
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
		drawtype = defaulttype;
}

void SceneProxy::InitBuffer()
{
	if (vbuffer.CheckStructDataSize(sizeof(mesh->data[0])))
	{
		vbuffer.InitData(mesh->data.size() * sizeof(mesh->data[0]), mesh->data.data());
	}
	ibuffer.InitData(mesh->index.size() * sizeof(mesh->index[0]), mesh->index.data());

	// Memorize index size for Draw() fucntion
	indexsize = static_cast<unsigned int>(mesh->index.size()) * sizeof(mesh->index[0]);
}

void SceneProxy::CleanUpBuffer() const
{
	vbuffer.CleanUp();
	ibuffer.CleanUp();
}