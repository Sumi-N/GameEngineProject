#pragma once

#include "TestScenes.h"

#include "MyCamera.h"
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


void TestScene::PBR_9Balls()
{
	// Setting up camera
	Entity::RegisterCamera(ObjectFactory<MyCamera>::Create());

	// Setting up skybox
	Entity::RegisterSkyBox(ObjectFactory<MySkyBox>::Create());


	OwningPointer<RastedSphere> rastered = ObjectFactory<RastedSphere>::Create();
	rastered->Translate(Vec3f(0, 0, -60));
	rastered->scale = Vec3f(0.3f, 0.3f, 0.3f);

	OwningPointer<ScuffedGoldSphere> gold = ObjectFactory<ScuffedGoldSphere>::Create();
	gold->Translate(Vec3f(15, 0, -60));
	gold->scale = Vec3f(0.3f, 0.3f, 0.3f);

	OwningPointer<WornPaintedCement> cement = ObjectFactory<WornPaintedCement>::Create();
	cement->Translate(Vec3f(-15, 0, -60));
	cement->scale = Vec3f(0.3f, 0.3f, 0.3f);

	OwningPointer<MetalGridSphere> metalgrid = ObjectFactory<MetalGridSphere>::Create();
	metalgrid->Translate(Vec3f(-15, 15, -60));
	metalgrid->scale = Vec3f(0.3f, 0.3f, 0.3f);

	OwningPointer<BathRoomTileSphere> bathroomtile = ObjectFactory<BathRoomTileSphere>::Create();
	bathroomtile->Translate(Vec3f(-15, -15, -60));
	bathroomtile->scale = Vec3f(0.3f, 0.3f, 0.3f);

	OwningPointer<DirtyWickerWeaveSphere> dirtyweave = ObjectFactory<DirtyWickerWeaveSphere>::Create();
	dirtyweave->Translate(Vec3f(15, -15, -60));
	dirtyweave->scale = Vec3f(0.3f, 0.3f, 0.3f);

	OwningPointer<GrayBrickSphere> graybrick = ObjectFactory<GrayBrickSphere>::Create();
	graybrick->Translate(Vec3f(15, 15, -60));
	graybrick->scale = Vec3f(0.3f, 0.3f, 0.3f);

	OwningPointer<BrushedMetalSphere> brushedmetal = ObjectFactory<BrushedMetalSphere>::Create();
	brushedmetal->Translate(Vec3f(0, 15, -60));
	brushedmetal->scale = Vec3f(0.3f, 0.3f, 0.3f);

	OwningPointer<OldSoiledClothSphere> oldsoiledcloth = ObjectFactory<OldSoiledClothSphere>::Create();
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

	OwningPointer<MyPointLight> pointlight = ObjectFactory<MyPointLight>::Create();
	pointlight->intensity = Vec3f(25.0f, 25.0f, 25.0f);
	pointlight->pos = Vec3f(0.f, 0.f, -40.f);

	OwningPointer<MyPointLight> pointlight2 = ObjectFactory<MyPointLight>::Create();
	pointlight2->intensity = Vec3f(10.0f, 10.0f, 10.0f);
	pointlight2->pos = Vec3f(30.f, -30.f, -40.f);

	OwningPointer<MyPointLight> pointlight3 = ObjectFactory<MyPointLight>::Create();
	pointlight3->intensity = Vec3f(10.0f, 10.0f, 10.0f);
	pointlight3->pos = Vec3f(-30.f, 30.f, -40.f);

	OwningPointer<MyPointLight> pointlight4 = ObjectFactory<MyPointLight>::Create();
	pointlight4->intensity = Vec3f(10.0f, 10.0f, 10.0f);
	pointlight4->pos = Vec3f(-30.f, -30.f, -40.f);

	Entity::RegisterPointLight(pointlight);
	//Entity::RegisterPointLight(pointlight2);
	//Entity::RegisterPointLight(pointlight3);
	//Entity::RegisterPointLight(pointlight4);
}