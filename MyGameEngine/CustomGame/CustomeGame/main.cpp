#pragma once

#include <Core/Thread/EntryPoint.h>
#include <Parts/MeshComponent.h>
#include <Parts/Object.h>
#include <Parts/Light.h>
#include <Parts/MaterialAttribute.h>
#include <Parts/TextureAttribute.h>
#include <EntitySystem/Entity.h>
#include <Graphics/Shader.h>
#include <Graphics/SceneEntity.h>

#include "Teapot.h"
#include "MyCamera.h"

#include <stdio.h>

int main()
{
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
	Entity::RegisterCamera(&camera);
	Entity::Register(&teapot);
	Entity::RegisterAmbientLight(&ambientlight);
	Entity::RegisterPointLight(&pointlight);
	Entity::RegisterPointLight(&pointlight2);



	System::Boot();
	
	System::Start();
	return 0;
};