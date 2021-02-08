#pragma once

#include "TestScenes.h"

#include "MyCamera.h"
#include "MyPointLight.h"
#include "MySkyBox.h"

#include "SpherePBR_Test.h"

namespace Tempest
{
	void TestScene::PBR_Red_Balls()
	{
		// Setting up camera
		OwningPointer<MyCamera> mycamera = OwningPointer<MyCamera>::Create(mycamera);
		Entity::RegisterCamera(mycamera);

		// Setting up skybox
		OwningPointer<MySkyBox> myskybox = OwningPointer<MySkyBox>::Create(myskybox);
		Entity::RegisterSkyBox(myskybox);


		OwningPointer<SpherePBR_Test> sphere[64];

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				OwningPointer<SpherePBR_Test>::Create(sphere[8 * i + j]);
				sphere[8 * i + j]->ChangePos(Vec3f(6.25f * i - 20.0f, 6.25f * j - 20.0f, -60.0f));
				sphere[8 * i + j]->ChangeMaterialParameter(0.125f * i, 0.125f * j);
				sphere[8 * i + j]->scale = Vec3f(0.1f, 0.1f, 0.1f);
				Entity::Register(sphere[8 * i + j]);
			}
		}

		OwningPointer<MyPointLight> pointlight = OwningPointer<MyPointLight>::Create(pointlight);
		pointlight->intensity = Vec3f(25.0f, 25.0f, 25.0f);
		pointlight->pos = Vec3f(0.f, 0.f, -40.f);

		OwningPointer<MyPointLight> pointlight2 = OwningPointer<MyPointLight>::Create(pointlight2);
		pointlight2->intensity = Vec3f(10.0f, 10.0f, 10.0f);
		pointlight2->pos = Vec3f(30.f, -30.f, -40.f);

		OwningPointer<MyPointLight> pointlight3 = OwningPointer<MyPointLight>::Create(pointlight3);
		pointlight3->intensity = Vec3f(10.0f, 10.0f, 10.0f);
		pointlight3->pos = Vec3f(-30.f, 30.f, -40.f);

		OwningPointer<MyPointLight> pointlight4 = OwningPointer<MyPointLight>::Create(pointlight4);
		pointlight4->intensity = Vec3f(10.0f, 10.0f, 10.0f);
		pointlight4->pos = Vec3f(-30.f, -30.f, -40.f);

		Entity::RegisterPointLight(pointlight);
		Entity::RegisterPointLight(pointlight2);
		Entity::RegisterPointLight(pointlight3);
		Entity::RegisterPointLight(pointlight4);
	}
}