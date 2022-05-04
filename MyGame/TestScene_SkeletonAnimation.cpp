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
		Entity::Register(mycamera);

		// Setting up skybox
		OwningPointer<MySkyBox> myskybox = OwningPointer<MySkyBox>::Create(myskybox);
		Entity::Register(myskybox);

		// Setting up animated player
		OwningPointer<AnimatedPlayer> player = OwningPointer<AnimatedPlayer>::Create(player);
		Entity::Register(player);
		player->pos = Vec3f(0, -10, -25);		
		player->scale = Vec3f(0.1f, 0.1f, 0.1f);

		OwningPointer<MyPointLight> pointlight = OwningPointer<MyPointLight>::Create(pointlight);		
		Entity::Register(pointlight);
	}
}