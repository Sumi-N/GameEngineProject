#pragma  once
#include "TestScenes.h"

#include <PremadeParts/TexturedQuad.h>
#include "Teapot.h"
#include "MyCamera.h"
#include "MyPointLight.h"
#include "MySkyBox.h"

namespace Tempest
{
	void TestScene::PhoneBlinn_Teapots()
	{
		// Setting up camera
		OwningPointer<MyCamera> mycamera = OwningPointer<MyCamera>::Create(mycamera);
		Entity::RegisterCamera(mycamera);

		// Setting up skybox
		OwningPointer<MySkyBox> myskybox = OwningPointer<MySkyBox>::Create(myskybox);
		Entity::RegisterSkyBox(myskybox);

		// Setting up teapot
		OwningPointer<Teapot> teapot1 = OwningPointer<Teapot>::Create(teapot1);
		Entity::Register(teapot1);
		teapot1->pos = Vec3f(-25, 0, 0);
		teapot1->rot = Vec3f(-90, 0, 0);
		teapot1->scale = Vec3f(0.5, 0.5, 0.5);

		//Setting up teapot
		OwningPointer<Teapot> teapot2 = OwningPointer<Teapot>::Create(teapot2);
		Entity::Register(teapot2);
		teapot2->pos = Vec3f(0, 0, -25);
		teapot2->rot = Vec3f(-90, 0, 0);
		teapot2->scale = Vec3f(0.5, 0.5, 0.5);

		// Setting up teapot
		OwningPointer<Teapot> teapot3 = OwningPointer<Teapot>::Create(teapot3);
		Entity::Register(teapot3);
		teapot3->pos = Vec3f(25, 0, 0);
		teapot3->rot = Vec3f(-90, 0, 0);
		teapot3->scale = Vec3f(0.5, 0.5, 0.5);

		// Setting up teapot
		OwningPointer<Teapot> teapot4 = OwningPointer<Teapot>::Create(teapot4);
		Entity::Register(teapot4);
		teapot4->pos = Vec3f(0, 25, 0);
		teapot4->rot = Vec3f(-90, 0, 0);
		teapot4->scale = Vec3f(0.5, 0.5, 0.5);

		// Setting up teapot
		OwningPointer<Teapot> teapot5 = OwningPointer<Teapot>::Create(teapot5);
		Entity::Register(teapot5);
		teapot5->pos = Vec3f(0, -25, 0);
		teapot5->rot = Vec3f(-90, 0, 0);
		teapot5->scale = Vec3f(0.5, 0.5, 0.5);

		// Setting up teapot
		OwningPointer<Teapot> teapot6 = OwningPointer<Teapot>::Create(teapot6);
		Entity::Register(teapot6);
		teapot6->pos = Vec3f(0, 0, 25);
		teapot6->rot = Vec3f(-90, 0, 0);
		teapot6->scale = Vec3f(0.5, 0.5, 0.5);

		OwningPointer<TexturedQuad> frontwall = OwningPointer<TexturedQuad>::Create(frontwall);
		Entity::Register(frontwall);
		frontwall->pos = Vec3f(0, 0, -40);
		frontwall->rot = Vec3f(0, 0, 0);
		frontwall->scale = Vec3f(50.0f, 50.0f, 50.0f);

		OwningPointer<TexturedQuad> backwall = OwningPointer<TexturedQuad>::Create(backwall);
		Entity::Register(backwall);
		backwall->pos = Vec3f(0, 0, 40);
		backwall->rot = Vec3f(0, 180, 0);
		backwall->scale = Vec3f(50.0f, 50.0f, 50.0f);

		OwningPointer<TexturedQuad> leftwall = OwningPointer<TexturedQuad>::Create(leftwall);
		Entity::Register(leftwall);
		leftwall->pos = Vec3f(-40, 0, 0);
		leftwall->rot = Vec3f(0, 90, 0);
		leftwall->scale = Vec3f(50.0f, 50.0f, 50.0f);

		OwningPointer<TexturedQuad> rightwall = OwningPointer<TexturedQuad>::Create(rightwall);
		Entity::Register(rightwall);
		rightwall->pos = Vec3f(40, 0, 0);
		rightwall->rot = Vec3f(0, -90, 0);
		rightwall->scale = Vec3f(50.0f, 50.0f, 50.0f);

		OwningPointer<TexturedQuad> topwall = OwningPointer<TexturedQuad>::Create(topwall);
		Entity::Register(topwall);
		topwall->pos = Vec3f(0, 40, 0);
		topwall->rot = Vec3f(90, 0, 0);
		topwall->scale = Vec3f(50.0f, 50.0f, 50.0f);

		OwningPointer<TexturedQuad> bottomwall = OwningPointer<TexturedQuad>::Create(bottomwall);
		Entity::Register(bottomwall);
		bottomwall->pos = Vec3f(0, -40, 0);
		bottomwall->rot = Vec3f(-90, 0, 0);
		bottomwall->scale = Vec3f(50.0f, 50.0f, 50.0f);

		//Setting up lights
		OwningPointer<AmbientLight> ambientlight = OwningPointer<AmbientLight>::Create(ambientlight);
		ambientlight->intensity = Vec3f(0.5f, 0.5f, 0.5f);

		OwningPointer<MyPointLight> pointlight = OwningPointer<MyPointLight>::Create(pointlight);
		pointlight->intensity = Vec3f(10.0f, 10.0f, 10.0f);
		pointlight->pos = Vec3f(0.f, 0.f, 0.f);

		OwningPointer<MyPointLight> pointlight2 = OwningPointer<MyPointLight>::Create(pointlight2);
		pointlight2->intensity = Vec3f(30.0f, 30.0f, 30.0f);
		pointlight2->pos = Vec3f(20.f, 20.f, 20.f);

		Entity::RegisterAmbientLight(ambientlight);
		Entity::RegisterPointLight(pointlight);
		//Entity::RegisterPointLight(pointlight2);
	}
}