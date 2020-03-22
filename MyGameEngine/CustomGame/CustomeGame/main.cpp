#pragma once

#include <Core/Thread/EntryPoint.h>
#include <Parts/Object.h>
#include <Parts/Light.h>
#include <EntitySystem/Entity.h>

#include "Teapot.h"
#include "MyCamera.h"

#include <stdio.h>

int main()
{
	// Setting up skybox
	CubeMapMeshComponent skybox;
	// Setting up teapot
	Teapot teapot;
	// Setting up camera
	MyCamera camera;
	// Setting up lights
	AmbientLight ambientlight;
	ambientlight.intensity = Vec3f(0.1f, 0.1f, 0.1f);
	PointLight pointlight;
	pointlight.intensity = Vec3f(1.0f, 1.0f, 1.0f);
	pointlight.pos = Vec3f(20.f, 20.f, -50.f);
	PointLight pointlight2;
	pointlight2.intensity = Vec3f(0.8f, 0.8f, 0.8f);
	pointlight2.pos = Vec3f(-20.f, -20.f, -30.f);

	// Register data to Entity
	Entity::RegisterSkyBox(&skybox);
	Entity::Register(&teapot);
	Entity::RegisterCamera(&camera);
	Entity::RegisterAmbientLight(&ambientlight);
	Entity::RegisterPointLight(&pointlight);
	Entity::RegisterPointLight(&pointlight2);

	System::Boot();
	
	System::Start();
	return 0;
};