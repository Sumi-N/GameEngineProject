#pragma once

#include "SceneProxy.h"

void SceneProxy::Init(const int num)
{
	InitBuffer(num);
}

void SceneProxy::ReplaceRenderState(Owner<RenderState> i_state)
{
	state = i_state;
}

void SceneProxy::CleanUp()
{
}

void SceneProxy::InitBuffer(const int num)
{
	if(num == 0)
	{
		auto mesh = static_cast<Observer<Resource::Mesh>>(meshes[meshes.Size() - 1]);

		VertexBuffer vbuffer;
		vbuffer.InitData(VertexBufferType::Mesh, static_cast<uint32_t>(mesh->data.Size()) * sizeof(mesh->data[0]), mesh->data.Data());
		vbuffers.PushBack(vbuffer);

		IndexBuffer ibuffer;
		ibuffer.InitData(static_cast<uint32_t>(mesh->index.Size()) * sizeof(mesh->index[0]), mesh->index.Data());
		ibuffers.PushBack(ibuffer);

		// Memorize index size for Draw() fucntion
		indexsizes.PushBack(static_cast<unsigned int>(mesh->index.Size()) * sizeof(mesh->index[0]));
	}
	else if(num == 1)
	{
		Observer<Resource::SkeletonMesh> skeleton_mesh = static_cast<Observer<Resource::SkeletonMesh>>(meshes[meshes.Size() - 1]);

		VertexBuffer vbuffer;
		vbuffer.InitData(VertexBufferType::SkeletonMesh, static_cast<uint32_t>(skeleton_mesh->data.Size()) * sizeof(skeleton_mesh->data[0]), skeleton_mesh->data.Data());
		vbuffers.PushBack(vbuffer);

		IndexBuffer ibuffer;
		ibuffer.InitData(static_cast<uint32_t>(skeleton_mesh->index.Size()) * sizeof(skeleton_mesh->index[0]), skeleton_mesh->index.Data());
		ibuffers.PushBack(ibuffer);

		// Memorize index size for Draw() fucntion
		indexsizes.PushBack(static_cast<unsigned int>(skeleton_mesh->index.Size()) * sizeof(skeleton_mesh->index[0]));
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
	for (int i = 0; i < vbuffers.Size(); i++)
	{
		vbuffers[i].CleanUp();
		ibuffers[i].CleanUp();
	}
}