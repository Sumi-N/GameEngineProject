#pragma once

#include <Core/Thread/EntryPoint.h>
#include <Parts/MeshComponent.h>
#include <Parts/Object.h>
#include <Parts/Camera.h>
#include <EntitySystem/Entity.h>
#include <Graphics/Shader.h>
#include <Graphics/SceneFormat.h>

#include "Teapot.h"

#include <stdio.h>

int main()
{
	Teapot teapot;
	MeshComponent teapotmesh;
	Entity::Register(&teapot);
	teapotmesh.owner = Entity::ObjectList[0].p;
	teapotmesh.Load("../../Assets/models/teapot.obj");
	//teapotmesh.Load("../../Assets/models/plane.obj");

	Camera camera;

	SceneProxy proxy;
	proxy.mesh = &teapotmesh;

	Shader shader;
	SceneFormat::Register(&proxy, &shader);

	System::Boot();

	Shader::LoadShader(shader, "../../Assets/shaders/test.vert.glsl", "../../Assets/shaders/test.frag.glsl");

	System::RunRenderThread();
	return 0;
};