#pragma once

#include <Core/Thread/EntryPoint.h>
#include <Parts/Light.h>
#include <PremadeParts/Quad.h>
#include <PremadeParts/SkyBox.h>
#include <EntitySystem/Entity.h>

#include "Teapot.h"
#include "MyCamera.h"
#include "DepthMapDebugPlane.h"
#include "NormalMapDebugPlane.h"
#include "SpherePBR_Test.h"
#include "RastedSphere.h"

#include <stdio.h>

int main()
{
	//// Setting up camera
	MyCamera camera;
	Entity::RegisterCamera(&camera);

	//// Setting up skybox
	SkyBox skybox;
	//Entity::Register(&skybox);

	//// Setting up teapot
	Teapot teapot;
	//Entity::Register(&teapot);

	//// Setting up quad
	//Quad quad;
	//Entity::Register(&quad);

	//// Setting up quad2
	//DepthMapDebugPlane debugplane;
	//Entity::Register(&debugplane);

	//// Setting up quad3
	//NormalMapDebugPlane normalplane;
	//Entity::Register(&normalplane);

	////Setting up lights
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

	///////////////////////////////////////////////////////////

	SpherePBR_Test sphere[64];

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			sphere[8 * i + j].ChangePos(Vec3f(6.25f * i - 20.0f, 6.25f * j - 20.0f, -60.0f));
			sphere[8 * i + j].ChangeMaterialParameter(0.125f * i, 0.125f * j);
			sphere[8 * i + j].scale = Vec3f(0.1, 0.1, 0.1);
			//Entity::Register(&sphere[8 * i + j]);
		}
	}

	RastedSphere rastered;
	rastered.Translate(Vec3f(0, 0, -60));
	Entity::Register(&rastered);

	PointLight pointlight;
	pointlight.intensity = Vec3f(1.0f, 1.0f, 1.0f);
	pointlight.pos = Vec3f(60.f, 60.f, 0.f);

	PointLight pointlight2;
	pointlight2.intensity = Vec3f(1.0f, 1.0f, 1.0f);
	pointlight2.pos = Vec3f(60.f, -60.f, 0.f);

	PointLight pointlight3;
	pointlight3.intensity = Vec3f(1.0f, 1.0f, 1.0f);
	pointlight3.pos = Vec3f(-60.f, 60.f, 0.f);

	PointLight pointlight4;
	pointlight4.intensity = Vec3f(1.0f, 1.0f, 1.0f);
	pointlight4.pos = Vec3f(-60.f, -60.f, 0.f);

	AmbientLight ambientlight;
	ambientlight.intensity = Vec3f(0.03f, 0.03f, 0.03f);

	Entity::RegisterPointLight(&pointlight);
	//Entity::RegisterPointLight(&pointlight2);
	//Entity::RegisterPointLight(&pointlight3);
	//Entity::RegisterPointLight(&pointlight4);
	Entity::RegisterAmbientLight(&ambientlight);

	System::Boot();
	
	System::Start();
	return 0;
};