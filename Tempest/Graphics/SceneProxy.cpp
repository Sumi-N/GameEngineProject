#pragma once

#include "SceneProxy.h"

void SceneProxy::Init(const int num)
{
	InitBuffer(num);
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

void SceneProxy::InitBuffer(const int num)
{		
	if(num == 0)
	{
		vbuffer.InitData(VertexBufferType::Mesh, static_cast<uint32_t>(mesh->data.Size()) * sizeof(mesh->data[0]), mesh->data.Data());

		ibuffer.InitData(static_cast<uint32_t>(mesh->index.Size()) * sizeof(mesh->index[0]), mesh->index.Data());

		// Memorize index size for Draw() fucntion
		indexsize = static_cast<unsigned int>(mesh->index.Size()) * sizeof(mesh->index[0]);
	}
	else if(num == 1)
	{					
		vbuffer.InitData(VertexBufferType::SkeletonMesh, static_cast<uint32_t>(skeleton_mesh->data.Size()) * sizeof(skeleton_mesh->data[0]), skeleton_mesh->data.Data());

		ibuffer.InitData(static_cast<uint32_t>(skeleton_mesh->index.Size()) * sizeof(skeleton_mesh->index[0]), skeleton_mesh->index.Data());

		// Memorize index size for Draw() fucntion
		indexsize = static_cast<unsigned int>(skeleton_mesh->index.Size()) * sizeof(skeleton_mesh->index[0]);
	}
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