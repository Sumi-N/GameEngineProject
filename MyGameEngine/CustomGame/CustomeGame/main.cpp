#pragma once

#include <Core/Thread/EntryPoint.h>
#include <Parts/MeshComponent.h>
#include <Parts/Object.h>
#include <EntitySystem/Entity.h>
#include <Graphics/Shader.h>
#include <Graphics/SceneFormat.h>

#include "Teapot.h"
#include "MyCamera.h"

#include <stdio.h>

int main()
{
	// Setting up teapot
	Teapot teapot;
	MeshComponent teapotmesh;
	Entity::Register(&teapot);
	teapotmesh.owner = Entity::ObjectList[0].p;
	teapotmesh.Load("../../Assets/models/teapot.obj");
	//teapotmesh.Load("../../Assets/models/plane.obj");

	SceneProxy proxy;
	proxy.mesh = &teapotmesh;

	Shader shader;
	SceneFormat::Register(&proxy, &shader);

	// Setting up camera
	MyCamera camera;
	Entity::RegisterCamera(&camera);

	System::Boot();

	Shader::LoadShader(shader, "../../Assets/shaders/test.vert.glsl", "../../Assets/shaders/test.frag.glsl");

	System::RunRenderThread();
	return 0;
};