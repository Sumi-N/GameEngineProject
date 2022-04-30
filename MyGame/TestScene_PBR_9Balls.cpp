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
		OwningPointer<MyCameraObject> mycamera = Create<MyCameraObject>();
		Entity::RegisterCamera(mycamera);

		// Setting up skybox
		OwningPointer<MySkyBox> myskybox = Create<MySkyBox>();
		Entity::RegisterSkyBox(myskybox);


		OwningPointer<RastedSphere> rastered = Create<RastedSphere>();
		rastered->Translate(Vec3f(0, 0, -60));
		rastered->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<ScuffedGoldSphere> gold = Create<ScuffedGoldSphere>();
		gold->Translate(Vec3f(15, 0, -60));
		gold->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<WornPaintedCement> cement = Create<WornPaintedCement>();
		cement->Translate(Vec3f(-15, 0, -60));
		cement->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<MetalGridSphere> metalgrid = Create<MetalGridSphere>();
		metalgrid->Translate(Vec3f(-15, 15, -60));
		metalgrid->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<BathRoomTileSphere> bathroomtile = Create<BathRoomTileSphere>();
		bathroomtile->Translate(Vec3f(-15, -15, -60));
		bathroomtile->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<DirtyWickerWeaveSphere> dirtyweave = Create<DirtyWickerWeaveSphere>();
		dirtyweave->Translate(Vec3f(15, -15, -60));
		dirtyweave->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<GrayBrickSphere> graybrick = Create<GrayBrickSphere>();
		graybrick->Translate(Vec3f(15, 15, -60));
		graybrick->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<BrushedMetalSphere> brushedmetal = Create<BrushedMetalSphere>();
		brushedmetal->Translate(Vec3f(0, 15, -60));
		brushedmetal->scale = Vec3f(0.3f, 0.3f, 0.3f);

		OwningPointer<OldSoiledClothSphere> oldsoiledcloth = Create<OldSoiledClothSphere>();
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

		OwningPointer<MyPointLight> pointlight = Create<MyPointLight>();
		pointlight->intensity = Vec3f(25.0f, 25.0f, 25.0f);
		pointlight->pos = Vec3f(0.f, 0.f, -40.f);

		OwningPointer<MyPointLight> pointlight2 = Create<MyPointLight>();
		pointlight2->intensity = Vec3f(10.0f, 10.0f, 10.0f);
		pointlight2->pos = Vec3f(30.f, -30.f, -40.f);

		OwningPointer<MyPointLight> pointlight3 = Create<MyPointLight>();
		pointlight3->intensity = Vec3f(10.0f, 10.0f, 10.0f);
		pointlight3->pos = Vec3f(-30.f, 30.f, -40.f);

		OwningPointer<MyPointLight> pointlight4 = Create<MyPointLight>();
		pointlight4->intensity = Vec3f(10.0f, 10.0f, 10.0f);
		pointlight4->pos = Vec3f(-30.f, -30.f, -40.f);

		Entity::RegisterPointLight(pointlight);
		//Entity::RegisterPointLight(pointlight2);
		//Entity::RegisterPointLight(pointlight3);
		//Entity::RegisterPointLight(pointlight4);
	}

}