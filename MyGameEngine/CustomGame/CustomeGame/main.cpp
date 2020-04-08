#pragma once

#include <Core/Thread/EntryPoint.h>
#include <Parts/Light.h>
#include <PremadeParts/Quad.h>
#include <PremadeParts/SkyBox.h>
#include <PremadeParts/TexturedQuad.h>
#include <EntitySystem/Entity.h>

#include "Teapot.h"
#include "MyCamera.h"
#include "DepthMapDebugPlane.h"
#include "NormalMapDebugPlane.h"
#include "SpherePBR_Test.h"
#include "RastedSphere.h"
#include "MyPointLight.h"

#include <stdio.h>

int main()
{
	//// Setting up camera
	MyCamera camera;
	Entity::RegisterCamera(&camera);

	//// Setting up skybox
	SkyBox skybox;
	//Entity::Register(&skybox);

	///////////////////////////////////////////////////////////

		// Setting up quad2
	DepthMapDebugPlane debugplane;
	//Entity::Register(&debugplane);

	// Setting up quad3
	NormalMapDebugPlane normalplane;
	//Entity::Register(&normalplane);

	//////////////////////////////////////////////////////////

	//// Setting up teapot
	//Teapot teapot1;
	//Entity::Register(&teapot1);
	//teapot1.pos = Vec3f(-25, 0, 0);
	//teapot1.rot = Vec3f(-90, 0, 0);
	//teapot1.scale = Vec3f(0.5, 0.5, 0.5);

	////Setting up teapot
	//Teapot teapot2;
	//Entity::Register(&teapot2);
	//teapot2.pos = Vec3f(0, 0, -25);
	//teapot2.rot = Vec3f(-90, 0, 0);
	//teapot2.scale = Vec3f(0.5, 0.5, 0.5);

	//// Setting up teapot
	//Teapot teapot3;
	//Entity::Register(&teapot3);
	//teapot3.pos = Vec3f(25, 0, 0);
	//teapot3.rot = Vec3f(-90, 0, 0);
	//teapot3.scale = Vec3f(0.5, 0.5, 0.5);

	//// Setting up teapot
	//Teapot teapot4;
	//Entity::Register(&teapot4);
	//teapot4.pos = Vec3f(0, 25, 0);
	//teapot4.rot = Vec3f(-90, 0, 0);
	//teapot4.scale = Vec3f(0.5, 0.5, 0.5);

	//// Setting up teapot
	//Teapot teapot5;
	//Entity::Register(&teapot5);
	//teapot5.pos = Vec3f(0, -25, 0);
	//teapot5.rot = Vec3f(-90, 0, 0);
	//teapot5.scale = Vec3f(0.5, 0.5, 0.5);

	//// Setting up teapot
	//Teapot teapot6;
	//Entity::Register(&teapot6);
	//teapot6.pos = Vec3f(0, 0, 25);
	//teapot6.rot = Vec3f(-90, 0, 0);
	//teapot6.scale = Vec3f(0.5, 0.5, 0.5);

	//TexturedQuad frontwall;
	//Entity::Register(&frontwall);
	//frontwall.pos = Vec3f(0, 0, -40);
	//frontwall.rot = Vec3f(0, 0, 0);
	//frontwall.scale = Vec3f(50.0f, 50.0f, 50.0f);

	//TexturedQuad backwall;
	//Entity::Register(&backwall);
	//backwall.pos = Vec3f(0, 0, 40);
	//backwall.rot = Vec3f(0, 180, 0);
	//backwall.scale = Vec3f(50.0f, 50.0f, 50.0f);

	//TexturedQuad leftwall;
	//Entity::Register(&leftwall);
	//leftwall.pos = Vec3f(-40, 0, 0);
	//leftwall.rot = Vec3f(0, 90, 0);
	//leftwall.scale = Vec3f(50.0f, 50.0f, 50.0f);

	//TexturedQuad rightwall;
	//Entity::Register(&rightwall);
	//rightwall.pos = Vec3f(40, 0, 0);
	//rightwall.rot = Vec3f(0, -90, 0);
	//rightwall.scale = Vec3f(50.0f, 50.0f, 50.0f);

	//TexturedQuad topwall;
	//Entity::Register(&topwall);
	//topwall.pos = Vec3f(0, 40, 0);
	//topwall.rot = Vec3f(90, 0, 0);
	//topwall.scale = Vec3f(50.0f, 50.0f, 50.0f);

	//Quad bottomwall;
	//Entity::Register(&bottomwall);
	//bottomwall.pos = Vec3f(0, -40, 0);
	//bottomwall.rot = Vec3f(-90, 0, 0);
	//bottomwall.scale = Vec3f(50.0f, 50.0f, 50.0f);

	////Setting up lights
	//AmbientLight ambientlight;
	//ambientlight.intensity = Vec3f(0.5f, 0.5f, 0.5f);

	//MyPointLight pointlight;
	//pointlight.intensity = Vec3f(10.0f, 10.0f, 10.0f);
	//pointlight.pos = Vec3f(0.f, 0.f, 0.f);

	//MyPointLight pointlight2;
	//pointlight2.intensity = Vec3f(30.0f, 30.0f, 30.0f);
	//pointlight2.pos = Vec3f(20.f, 20.f, 20.f);

	//Entity::RegisterAmbientLight(&ambientlight);
	//Entity::RegisterPointLight(&pointlight);
	//Entity::RegisterPointLight(&pointlight2);

	///////////////////////////////////////////////////////////

	//SpherePBR_Test sphere[64];

	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		sphere[8 * i + j].ChangePos(Vec3f(6.25f * i - 20.0f, 6.25f * j - 20.0f, -60.0f));
	//		sphere[8 * i + j].ChangeMaterialParameter(0.125f * i, 0.125f * j);
	//		sphere[8 * i + j].scale = Vec3f(0.1, 0.1, 0.1);
	//		Entity::Register(&sphere[8 * i + j]);
	//	}
	//}

	RastedSphere rastered;
	rastered.Translate(Vec3f(0, 0, -80));
	Entity::Register(&rastered);

	PointLight pointlight;
	pointlight.intensity = Vec3f(40.0f, 40.0f, 40.0f);
	pointlight.pos = Vec3f(30.f, 30.f, -40.f);

	PointLight pointlight2;
	pointlight2.intensity = Vec3f(40.0f, 40.0f, 40.0f);
	pointlight2.pos = Vec3f(30.f, -30.f, -40.f);

	PointLight pointlight3;
	pointlight3.intensity = Vec3f(40.0f, 40.0f, 40.0f);
	pointlight3.pos = Vec3f(-30.f, 30.f, -40.f);

	PointLight pointlight4;
	pointlight4.intensity = Vec3f(40.0f, 40.0f, 40.0f);
	pointlight4.pos = Vec3f(-30.f, -30.f, -40.f);

	AmbientLight ambientlight;
	ambientlight.intensity = Vec3f(0.03f, 0.03f, 0.03f);

	Entity::RegisterPointLight(&pointlight);
	Entity::RegisterPointLight(&pointlight2);
	Entity::RegisterPointLight(&pointlight3);
	Entity::RegisterPointLight(&pointlight4);
	Entity::RegisterAmbientLight(&ambientlight);

	/////////////////////////////////////////////////////////


	//TexturedQuad quad;
	//quad.pos = Vec3f(0, -10, -100);
	//quad.rot = Vec3f(-90, 0, 0);
	//quad.scale = Vec3f(10.0, 100.0, 10.0);
	//Entity::Register(&quad);

	//TexturedQuad quad2;
	//quad2.pos = Vec3f(10, 0, -100);
	//quad2.rot = Vec3f(-90, 0, 90);
	//quad2.scale = Vec3f(10.0, 100.0, 10.0);
	//Entity::Register(&quad2);

	//TexturedQuad quad3;
	//quad3.pos = Vec3f(-10, 0, -100);
	//quad3.rot = Vec3f(-90, 0, -90);
	//quad3.scale = Vec3f(10.0, 100.0, 10.0);
	//Entity::Register(&quad3);

	//TexturedQuad quad4;
	//Entity::Register(&quad4);
	//quad4.pos = Vec3f(0, 10, -100);
	//quad4.rot = Vec3f(90, 0, 0);
	//quad4.scale = Vec3f(10.0, 100.0, 10.0);

	//TexturedQuad quad5;
	//Entity::Register(&quad5);
	//quad5.pos = Vec3f(0, 0, -80);
	//quad5.rot = Vec3f(0, 0, 0);
	//quad5.scale = Vec3f(10.0, 10.0, 10.0);

	////Setting up lights
	//AmbientLight ambientlight;
	//ambientlight.intensity = Vec3f(0.1f, 0.1f, 0.1f);
	//PointLight pointlight;
	//pointlight.intensity = Vec3f(0.2f, 0.f, 0.f);
	//pointlight.pos = Vec3f(9.f, 9.f, -20.f);
	//PointLight pointlight2;
	//pointlight2.intensity = Vec3f(0.0f, 5.0f, 5.0f);
	//pointlight2.pos = Vec3f(-5.0f, -5.0f, -5.f);
	//PointLight pointlight3;
	//pointlight3.intensity = Vec3f(40.0f, 40.0f, 40.0f);
	//pointlight3.pos = Vec3f(0.0f, 0.0f, -70.f);

	//Entity::RegisterAmbientLight(&ambientlight);
	//Entity::RegisterPointLight(&pointlight);
	////Entity::RegisterPointLight(&pointlight2);
	//Entity::RegisterPointLight(&pointlight3);

	System::Boot();
	
	System::Start();
	return 0;
};