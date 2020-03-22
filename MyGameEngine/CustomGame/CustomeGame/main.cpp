#pragma once

#include <Core/Thread/EntryPoint.h>
#include <Parts/MeshComponent.h>
#include <Parts/Object.h>
#include <Parts/Light.h>
#include <Parts/MaterialAttribute.h>
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
	teapot.pos = Vec3f(0, 0, -50);
	teapot.scale = Vec3f(1.0, 1.0, 1.0);

	MeshComponent teapotmesh;
	MaterialAttribute teapotmaterial;
	teapotmesh.SetMaterial(&teapotmaterial);

	// Setting up camera
	MyCamera camera;

	// Setting up lights
	AmbientLight ambientlight;
	ambientlight.intensity = Vec3f(0.1, 0.1, 0.1);
	PointLight pointlight;
	pointlight.intensity = Vec3f(1.0, 1.0, 1.0);
	pointlight.pos = Vec3f(20, 20, -50);
	PointLight pointlight2;
	pointlight2.intensity = Vec3f(0.8, 0.8, 0.8);
	pointlight2.pos = Vec3f(-20, -20, -30);


	SceneProxy proxy;
	proxy.mesh = &teapotmesh;
	Shader shader;
	SceneFormat::Register(&proxy, &shader);

	// Register data to Entity
	Entity::RegisterCamera(&camera);
	Entity::Register(&teapot);
	Entity::RegisterMeshComponent(&teapotmesh);
	Entity::RegisterAmbientLight(&ambientlight);
	Entity::RegisterPointLight(&pointlight);
	Entity::RegisterPointLight(&pointlight2);

	teapotmesh.owner = Entity::ObjectList[0].p;
	teapotmesh.Load("../../Assets/models/teapot.obj");

	System::Boot();

	Shader::LoadShader(shader, "../../Assets/shaders/blinn_phong.vert.glsl", "../../Assets/shaders/blinn_phong.frag.glsl");
	
	System::RunRenderThread();
	return 0;
};