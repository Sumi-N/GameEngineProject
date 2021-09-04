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
	}
	else if(num == 1)
	{			
		Resource::SkeletonMesh* skmesh = reinterpret_cast<Resource::SkeletonMesh*>(&*mesh);
		vbuffer.InitData(VertexBufferType::SkeletonMesh, static_cast<uint32_t>(skmesh->data.Size()) * sizeof(skmesh->data[0]), skmesh->data.Data());
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