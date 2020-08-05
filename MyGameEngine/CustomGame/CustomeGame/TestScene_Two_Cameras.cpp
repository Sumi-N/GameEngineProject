#include "TestScenes.h"

#include "Teapot.h"
#include "MyCamera.h"
#include "MyPointLight.h"
#include "MySkyBox.h"

void TestScene::Two_Cameras()
{
	OwningPointer<MyCamera> camera1  =  ObjectFactory<MyCamera>::Create();
	OwningPointer<MyCamera> camera2  =  ObjectFactory<MyCamera>::Create();

	// Setting up camera
	Entity::RegisterCamera(camera1);
	Entity::RegisterCamera(camera2);

	// Setting up skybox
	Entity::RegisterSkyBox(ObjectFactory<MySkyBox>::Create());

	//Setting up teapot
	OwningPointer<Teapot> teapot2 = ObjectFactory<Teapot>::Create();
	Entity::Register(teapot2);
	teapot2->pos = Vec3f(0, 0, -25);
	teapot2->rot = Vec3f(-90, 0, 0);
	teapot2->scale = Vec3f(0.5, 0.5, 0.5);

	//Setting up lights
	OwningPointer<AmbientLight> ambientlight = ObjectFactory<AmbientLight>::Create();
	ambientlight->intensity = Vec3f(0.5f, 0.5f, 0.5f);

	OwningPointer<MyPointLight> pointlight = ObjectFactory<MyPointLight>::Create();
	pointlight->intensity = Vec3f(10.0f, 10.0f, 10.0f);
	pointlight->pos = Vec3f(0.f, 0.f, 0.f);

	Entity::RegisterAmbientLight(ambientlight);
	Entity::RegisterPointLight(pointlight);
}