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
		Owner<MyCameraObject> mycamera = Create<MyCameraObject>();
		Entity::Register(mycamera);

		// Setting up skybox
		Owner<MySkyBox> myskybox = Create<MySkyBox>();
		Entity::Register(myskybox);


		Owner<RastedSphere> rastered = Create<RastedSphere>();
		rastered->Translate(Vec3f(0, 0, -60));
		rastered->scale = Vec3f(0.3f, 0.3f, 0.3f);

		Owner<ScuffedGoldSphere> gold = Create<ScuffedGoldSphere>();
		gold->Translate(Vec3f(15, 0, -60));
		gold->scale = Vec3f(0.3f, 0.3f, 0.3f);

		Owner<WornPaintedCement> cement = Create<WornPaintedCement>();
		cement->Translate(Vec3f(-15, 0, -60));
		cement->scale = Vec3f(0.3f, 0.3f, 0.3f);

		Owner<MetalGridSphere> metalgrid = Create<MetalGridSphere>();
		metalgrid->Translate(Vec3f(-15, 15, -60));
		metalgrid->scale = Vec3f(0.3f, 0.3f, 0.3f);

		Owner<BathRoomTileSphere> bathroomtile = Create<BathRoomTileSphere>();
		bathroomtile->Translate(Vec3f(-15, -15, -60));
		bathroomtile->scale = Vec3f(0.3f, 0.3f, 0.3f);

		Owner<DirtyWickerWeaveSphere> dirtyweave = Create<DirtyWickerWeaveSphere>();
		dirtyweave->Translate(Vec3f(15, -15, -60));
		dirtyweave->scale = Vec3f(0.3f, 0.3f, 0.3f);

		Owner<GrayBrickSphere> graybrick = Create<GrayBrickSphere>();
		graybrick->Translate(Vec3f(15, 15, -60));
		graybrick->scale = Vec3f(0.3f, 0.3f, 0.3f);

		Owner<BrushedMetalSphere> brushedmetal = Create<BrushedMetalSphere>();
		brushedmetal->Translate(Vec3f(0, 15, -60));
		brushedmetal->scale = Vec3f(0.3f, 0.3f, 0.3f);

		Owner<OldSoiledClothSphere> oldsoiledcloth = Create<OldSoiledClothSphere>();
		oldsoiledcloth->Translate(Vec3f(0, -15, -60));
		oldsoiledcloth->scale = Vec3f(0.3f, 0.3f, 0.3f);

		Entity::Register(rastered);
		Entity::Register(gold);
		Entity::Register(cement);
		Entity::Register(metalgrid);
		Entity::Register(bathroomtile);
		Entity::Register(dirtyweave);
		Entity::Register(graybrick);
		Entity::Register(brushedmetal);
		Entity::Register(oldsoiledcloth);

		Owner<MyPointLight> pointlight = Create<MyPointLight>();		
		pointlight->pos = Vec3f(0.f, 0.f, -40.f);

		Owner<MyPointLight> pointlight2 = Create<MyPointLight>();		
		pointlight2->pos = Vec3f(30.f, -30.f, -40.f);

		Owner<MyPointLight> pointlight3 = Create<MyPointLight>();		
		pointlight3->pos = Vec3f(-30.f, 30.f, -40.f);

		Owner<MyPointLight> pointlight4 = Create<MyPointLight>();		
		pointlight4->pos = Vec3f(-30.f, -30.f, -40.f);

		Entity::Register(pointlight);
		//Entity::Register(pointlight2);
		//Entity::Register(pointlight3);
		//Entity::Register(pointlight4);
	}

}