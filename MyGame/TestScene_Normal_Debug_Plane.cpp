#pragma  once

#include "TestScenes.h"

#include "Teapot.h"
#include "MyCameraObject.h"
#include "MyPointLight.h"
#include "MySkyBox.h"

#include "NormalMapDebugPlane.h"

namespace Tempest
{
	void TestScene::Normal_Debug_Plane()
	{
		// Setting up camera
		OwningPointer<MyCameraObject> mycamera = OwningPointer<MyCameraObject>::Create(mycamera);
		Entity::RegisterCamera(mycamera);

		// Setting up skybox
		OwningPointer<MySkyBox> myskybox = OwningPointer<MySkyBox>::Create(myskybox);
		Entity::RegisterSkyBox(myskybox);

		// Setting up quad3
		OwningPointer<NormalMapDebugPlane> normalplane = OwningPointer<NormalMapDebugPlane>::Create(normalplane);
		Entity::Register(normalplane);

		OwningPointer<MyPointLight> pointlight = OwningPointer<MyPointLight>::Create(pointlight);
		pointlight->intensity = Vec3f(25.0f, 25.0f, 25.0f);
		pointlight->pos = Vec3f(0.f, 0.f, -40.f);

		Entity::RegisterPointLight(pointlight);
	}
}