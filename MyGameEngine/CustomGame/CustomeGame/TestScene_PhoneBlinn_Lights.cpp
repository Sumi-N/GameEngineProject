#include "TestScenes.h"

#include "MyCamera.h"
#include "MyPointLight.h"
#include "MySkyBox.h"

#include <Parts/Light.h>
#include <PremadeParts/Quad.h>
#include <PremadeParts/TexturedQuad.h>

void TestScene::PhoneBlinn_Lights()
{
	// Setting up camera
	OwningPointer<MyCamera> mycamera = OwningPointer<MyCamera>::Create(mycamera);
	Entity::RegisterCamera(mycamera);

	// Setting up skybox
	OwningPointer<MySkyBox> myskybox = OwningPointer<MySkyBox>::Create(myskybox);
	Entity::RegisterSkyBox(myskybox);

	OwningPointer<TexturedQuad> quad = OwningPointer<TexturedQuad>::Create(quad);
	quad->pos = Vec3f(0, -10, -100);
	quad->rot = Vec3f(-90, 0, 0);
	quad->scale = Vec3f(10.0, 100.0, 10.0);
	Entity::Register(quad);

	OwningPointer<TexturedQuad> quad2 = OwningPointer<TexturedQuad>::Create(quad2);
	quad2->pos = Vec3f(10, 0, -100);
	quad2->rot = Vec3f(-90, 0, 90);
	quad2->scale = Vec3f(10.0, 100.0, 10.0);
	Entity::Register(quad2);

	OwningPointer<TexturedQuad> quad3 = OwningPointer<TexturedQuad>::Create(quad3);
	quad3->pos = Vec3f(-10, 0, -100);
	quad3->rot = Vec3f(-90, 0, -90);
	quad3->scale = Vec3f(10.0, 100.0, 10.0);
	Entity::Register(quad3);

	OwningPointer<TexturedQuad> quad4 = OwningPointer<TexturedQuad>::Create(quad4);
	Entity::Register(quad4);
	quad4->pos = Vec3f(0, 10, -100);
	quad4->rot = Vec3f(90, 0, 0);
	quad4->scale = Vec3f(10.0, 100.0, 10.0);

	OwningPointer<TexturedQuad> quad5 = OwningPointer<TexturedQuad>::Create(quad5);
	Entity::Register(quad5);
	quad5->pos = Vec3f(0, 0, -80);
	quad5->rot = Vec3f(0, 0, 0);
	quad5->scale = Vec3f(10.0, 10.0, 10.0);

	//Setting up lights
	OwningPointer<AmbientLight> ambientlight = OwningPointer<AmbientLight>::Create(ambientlight);
	ambientlight->intensity = Vec3f(0.1f, 0.1f, 0.1f);

	OwningPointer<MyPointLight> pointlight = OwningPointer<MyPointLight>::Create(pointlight);
	pointlight->intensity = Vec3f(0.2f, 0.f, 0.f);
	pointlight->pos = Vec3f(9.f, 9.f, -20.f);

	OwningPointer<MyPointLight> pointlight2 = OwningPointer<MyPointLight>::Create(pointlight2);
	pointlight2->intensity = Vec3f(0.0f, 5.0f, 5.0f);
	pointlight2->pos = Vec3f(-5.0f, -5.0f, -5.f);

	OwningPointer<MyPointLight> pointlight3 = OwningPointer<MyPointLight>::Create(pointlight3);
	pointlight3->intensity = Vec3f(40.0f, 40.0f, 40.0f);
	pointlight3->pos = Vec3f(0.0f, 0.0f, -70.f);

	Entity::RegisterAmbientLight(ambientlight);
	Entity::RegisterPointLight(pointlight);
	Entity::RegisterPointLight(pointlight2);
	Entity::RegisterPointLight(pointlight3);
}
