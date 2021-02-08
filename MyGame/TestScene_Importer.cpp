#pragma once
#include "TestScenes.h"

#include "MyCamera.h"
#include "MyPointLight.h"
#include "MySkyBox.h"
#include <PremadeParts/Cube.h>

namespace Tempest
{
	void TestScene::Importer()
	{
		// Setting up camera
		OwningPointer<MyCamera> mycamera = OwningPointer<MyCamera>::Create(mycamera);
		Entity::RegisterCamera(mycamera);

		// Setting up skybox
		OwningPointer<MySkyBox> myskybox = OwningPointer<MySkyBox>::Create(myskybox);
		Entity::RegisterSkyBox(myskybox);

		OwningPointer<MyPointLight> pointlight = OwningPointer<MyPointLight>::Create(pointlight);
		pointlight->intensity = Vec3f(25.0f, 25.0f, 25.0f);
		pointlight->pos = Vec3f(0.f, 0.f, -40.f);
		Entity::RegisterPointLight(pointlight);

		OwningPointer<Cube> cube = OwningPointer<Cube>::Create(cube);
		Entity::Register(cube);
	}
}