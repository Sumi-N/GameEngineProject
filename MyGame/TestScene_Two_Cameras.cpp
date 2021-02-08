#pragma  once
#include "TestScenes.h"

#include "Teapot.h"
#include "MyCamera.h"
#include "MyPointLight.h"
#include "MySkyBox.h"

namespace Tempest
{
	void TestScene::Two_Cameras()
	{
		OwningPointer<MyCamera> camera1;
		OwningPointer<MyCamera>::Create(camera1);
		OwningPointer<MyCamera> camera2;
		OwningPointer<MyCamera>::Create(camera2);

		Entity::RegisterCamera(camera1);
		Entity::RegisterCamera(camera2);

		OwningPointer<MySkyBox> myskybox = OwningPointer<MySkyBox>::Create(myskybox);
		Entity::RegisterSkyBox(myskybox);

		//Setting up teapot
		OwningPointer<Teapot> teapot2 = OwningPointer<Teapot>::Create(teapot2);
		Entity::Register(teapot2);
		teapot2->pos = Vec3f(0, 0, -25);
		teapot2->rot = Vec3f(-90, 0, 0);
		teapot2->scale = Vec3f(0.5, 0.5, 0.5);

		//Setting up lights
		OwningPointer<AmbientLight> ambientlight = OwningPointer<AmbientLight>::Create(ambientlight);
		ambientlight->intensity = Vec3f(0.5f, 0.5f, 0.5f);

		OwningPointer<MyPointLight> pointlight = OwningPointer<MyPointLight>::Create(pointlight);
		pointlight->intensity = Vec3f(10.0f, 10.0f, 10.0f);
		pointlight->pos = Vec3f(0.f, 0.f, 0.f);

		Entity::RegisterAmbientLight(ambientlight);
		Entity::RegisterPointLight(pointlight);
	}
}