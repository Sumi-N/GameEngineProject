#pragma once
#include "TestScenes.h"

#include "MyCameraObject.h"
#include "MyPointLight.h"
#include "MySkyBox.h"
#include "AnimatedPlayer.h"

namespace Tempest
{
	void TestScene::SkeletonAnimation()
	{
		// Setting up camera
		OwningPointer<MyCameraObject> mycamera = OwningPointer<MyCameraObject>::Create(mycamera);
		Entity::RegisterCamera(mycamera);

		// Setting up skybox
		OwningPointer<MySkyBox> myskybox = OwningPointer<MySkyBox>::Create(myskybox);
		Entity::RegisterSkyBox(myskybox);

		// Setting up teapot
		OwningPointer<AnimatedPlayer> teapot1 = OwningPointer<AnimatedPlayer>::Create(teapot1);
		Entity::Register(teapot1);
		teapot1->pos = Vec3f(0, -10, -25);
		teapot1->rot = Vec3f(0, 0, 0);
		teapot1->scale = Vec3f(0.1f, 0.1f, 0.1f);

		OwningPointer<MyPointLight> pointlight = OwningPointer<MyPointLight>::Create(pointlight);
		pointlight->intensity = Vec3f(25.0f, 25.0f, 25.0f);
		pointlight->pos = Vec3f(0.f, 0.f, 0.f);
		Entity::RegisterPointLight(pointlight);
	}
}