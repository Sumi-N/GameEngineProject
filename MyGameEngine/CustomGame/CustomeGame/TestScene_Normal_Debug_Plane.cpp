#include "TestScenes.h"

#include "Teapot.h"
#include "MyCamera.h"
#include "MyPointLight.h"
#include "MySkyBox.h"

#include "NormalMapDebugPlane.h"

void TestScene::Normal_Debug_Plane()
{
	// Setting up camera
	Entity::RegisterCamera(ObjectFactory<MyCamera>::Create());

	// Setting up skybox
	Entity::RegisterSkyBox(ObjectFactory<MySkyBox>::Create());

	// Setting up quad3
	OwningPointer<NormalMapDebugPlane> normalplane = ObjectFactory<NormalMapDebugPlane>::Create();
	Entity::Register(normalplane);

	OwningPointer<MyPointLight> pointlight = ObjectFactory<MyPointLight>::Create();
	pointlight->intensity = Vec3f(25.0f, 25.0f, 25.0f);
	pointlight->pos = Vec3f(0.f, 0.f, -40.f);

	Entity::RegisterPointLight(pointlight);
}