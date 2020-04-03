#pragma once

#include <Core/Thread/EntryPoint.h>
#include <Parts/Light.h>
#include <PremadeParts/Quad.h>
#include <EntitySystem/Entity.h>

#include "Teapot.h"
#include "MyCamera.h"
#include "DepthMapDebugPlane.h"
#include "NormalMapDebugPlane.h"
#include "SpherePBR_Test.h"

#include <stdio.h>

int main()
{
	// Setting up skybox
	CubeMapMeshComponent skybox;
	//Entity::RegisterSkyBox(&skybox);

	// Setting up camera
	MyCamera camera;
	Entity::RegisterCamera(&camera);

	// Setting up teapot
	Teapot teapot;
	//Entity::Register(&teapot);

	// Setting up quad
	Quad quad;
	//Entity::Register(&quad);

	// Setting up quad2
	DepthMapDebugPlane debugplane;
	//Entity::Register(&debugplane);

	// Setting up quad3
	NormalMapDebugPlane normalplane;
	//Entity::Register(&normalplane);

	// Setting up lights
	//AmbientLight ambientlight;
	//ambientlight.intensity = Vec3f(0.1f, 0.1f, 0.1f);
	//PointLight pointlight;
	//pointlight.intensity = Vec3f(1.0f, 1.0f, 1.0f);
	//pointlight.pos = Vec3f(50.f, 50.f, -50.f);
	//PointLight pointlight2;
	//pointlight2.intensity = Vec3f(0.8f, 0.8f, 0.8f);
	//pointlight2.pos = Vec3f(-20.f, -20.f, -30.f);
	//Entity::RegisterAmbientLight(&ambientlight);
	//Entity::RegisterPointLight(&pointlight);
	//Entity::RegisterPointLight(&pointlight2);


	SpherePBR_Test sphere[25];
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			sphere[5 * i + j].ChangePos(Vec3f(10 * i - 20, 10 * j - 20, -60));
			sphere[5 * i + j].ChangeMaterialParameter(0.2 * i, 0.2 * j);
			sphere[5 * i + j].scale = Vec3f(0.1, 0.1, 0.1);
			Entity::Register(&sphere[5 * i + j]);
		}
	}

	PointLight pointlight;
	pointlight.intensity = Vec3f(1.0f, 1.0f, 1.0f);
	pointlight.pos = Vec3f(0.f, 0.f, 0.f);
	Entity::RegisterPointLight(&pointlight);

	System::Boot();
	
	System::Start();
	return 0;
};