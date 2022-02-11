#pragma once

#include "TestScenes.h"

#include "MyCameraObject.h"
#include "MyPointLight.h"
#include "MySkyBox.h"

#include "RastedSphere.h"
#include "ScuffedGoldSphere.h"
#include "WarnPaintedCement.h"
#include "MetalGridSphere.h"
#include "BathRoomTileSphere.h"
#include "DirtyWickerWeaveSphere.h"
#include "GrayBrickSphere.h"
#include "BrushedMetalSphere.h"
#include "OldSoiledClothSphere.h"

namespace Tempest
{
	void TestScene::PBR_9Balls()
	{
		// Setting up camera
		OwningPointer<MyCameraObject> mycamera = OwningPointer<MyCameraObject>::Create(mycamera);
		Entity::RegisterCamera(mycamera);

		// Setting up skybox
		OwningPointer<MySkyBox> myskybox = OwningPointer<MySkyBox>::Create(myskybox);
		Entity::RegisterSkyBox(myskybox);


		OwningPointer<RastedSphere> rastered = OwningPointer<RastedSphere>::Create(rastered);
		rastered->Translate(Vec3f(0, 0, -60));
		rastered->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<ScuffedGoldSphere> gold = OwningPointer<ScuffedGoldSphere>::Create(gold);
		gold->Translate(Vec3f(15, 0, -60));
		gold->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<WornPaintedCement> cement = OwningPointer<WornPaintedCement>::Create(cement);
		cement->Translate(Vec3f(-15, 0, -60));
		cement->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<MetalGridSphere> metalgrid = OwningPointer<MetalGridSphere>::Create(metalgrid);
		metalgrid->Translate(Vec3f(-15, 15, -60));
		metalgrid->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<BathRoomTileSphere> bathroomtile = OwningPointer<BathRoomTileSphere>::Create(bathroomtile);
		bathroomtile->Translate(Vec3f(-15, -15, -60));
		bathroomtile->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<DirtyWickerWeaveSphere> dirtyweave = OwningPointer<DirtyWickerWeaveSphere>::Create(dirtyweave);
		dirtyweave->Translate(Vec3f(15, -15, -60));
		dirtyweave->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<GrayBrickSphere> graybrick = OwningPointer<GrayBrickSphere>::Create(graybrick);
		graybrick->Translate(Vec3f(15, 15, -60));
		graybrick->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<BrushedMetalSphere> brushedmetal = OwningPointer<BrushedMetalSphere>::Create(brushedmetal);
		brushedmetal->Translate(Vec3f(0, 15, -60));
		brushedmetal->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<OldSoiledClothSphere> oldsoiledcloth = OwningPointer<OldSoiledClothSphere>::Create(oldsoiledcloth);
		oldsoiledcloth->Translate(Vec3f(0, -15, -60));
		oldsoiledcloth->scale = Vec3f(0.3f, 0.3f, 0.3f);

		Entity::Register(rastered, "Rasterd Ball");
		Entity::Register(gold, "Gold Ball");
		Entity::Register(cement, "Cement Ball");
		Entity::Register(metalgrid, "Metal Grid Ball");
		Entity::Register(bathroomtile, "Bathroom Tile Ball");
		Entity::Register(dirtyweave, "Dirty Weave Ball");
		Entity::Register(graybrick, "Gray Brick Ball");
		Entity::Register(brushedmetal, "Brush Metal Ball");
		Entity::Register(oldsoiledcloth, "Old Soiled Cloth Ball");

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
		//Entity::RegisterPointLight(pointlight2);
		//Entity::RegisterPointLight(pointlight3);
		//Entity::RegisterPointLight(pointlight4);
	}

}