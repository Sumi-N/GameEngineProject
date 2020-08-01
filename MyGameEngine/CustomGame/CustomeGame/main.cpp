#pragma once

#include <Core/Thread/EntryPoint.h>
#include <Parts/Light.h>
#include <PremadeParts/Quad.h>
#include <PremadeParts/TexturedQuad.h>
#include <EntitySystem/Entity.h>
#include <EntitySystem/ObjectFactory.h>
#include <Debug/MemoryLeakDetection.h>

#include "Teapot.h"
#include "MyCamera.h"
#include "MyPointLight.h"
#include "MySkyBox.h"

#include "NormalMapDebugPlane.h"

#include "SpherePBR_Test.h"
#include "RastedSphere.h"
#include "ScuffedGoldSphere.h"
#include "WarnPaintedCement.h"
#include "MetalGridSphere.h"
#include "BathRoomTileSphere.h"
#include "DirtyWickerWeaveSphere.h"
#include "GrayBrickSphere.h"
#include "BrushedMetalSphere.h"
#include "OldSoiledClothSphere.h"

float QueryPreciseTimeinAFrame(const Vec3f& start_position, const Vec3f& start_velocity, const Vec3f& up_vector, const Vec3f& hit_position, float accel, float current_time)
{

	Vec3f start_end_vec = hit_position - start_position;
	float vertical_distance = start_end_vec.x * up_vector.x + start_end_vec.y * up_vector.y + start_end_vec.z * up_vector.z;
	float vertical_velocity = start_velocity.x * up_vector.x + start_velocity.y * up_vector.y + start_velocity.z * up_vector.z;
	float vertical_accel = accel;

	if (vertical_accel == 0)
	{
		return vertical_distance / vertical_velocity;
	}

	float t1 = (-1 * vertical_velocity + Math::Sqrt(vertical_velocity * vertical_velocity + 2 * vertical_accel * vertical_distance)) / vertical_accel;
	float t2 = (-1 * vertical_velocity - Math::Sqrt(vertical_velocity * vertical_velocity + 2 * vertical_accel * vertical_distance)) / vertical_accel;

	return t1;
}


int main()
{
	QueryPreciseTimeinAFrame(Vec3f(0, 0, 0), Vec3f(0, 5, 10), Vec3f(0, 1, 0), Vec3f(0, 1.27, 5.0), -9.8, 0.0);

	MEMORY_LEAK_DETECTION

	// Setting up camera
	Entity::RegisterCamera(ObjectFactory<MyCamera>::Create());

	// Setting up skybox
	Entity::RegisterSkyBox(ObjectFactory<MySkyBox>::Create());

	///////////////////////////////////////////////////////////

	// Setting up quad3
	//NormalMapDebugPlane normalplane;
	//Entity::Register(&normalplane);

	//////////////////////////////////////////////////////////

	//// Setting up teapot
	//Teapot teapot1;
	//Entity::Register(&teapot1);
	//teapot1.pos = Vec3f(-25, 0, 0);
	//teapot1.rot = Vec3f(-90, 0, 0);
	//teapot1.scale = Vec3f(0.5, 0.5, 0.5);

	////Setting up teapot
	//Teapot teapot2;
	//Entity::Register(&teapot2);
	//teapot2.pos = Vec3f(0, 0, -25);
	//teapot2.rot = Vec3f(-90, 0, 0);
	//teapot2.scale = Vec3f(0.5, 0.5, 0.5);

	//// Setting up teapot
	//Teapot teapot3;
	//Entity::Register(&teapot3);
	//teapot3.pos = Vec3f(25, 0, 0);
	//teapot3.rot = Vec3f(-90, 0, 0);
	//teapot3.scale = Vec3f(0.5, 0.5, 0.5);

	//// Setting up teapot
	//Teapot teapot4;
	//Entity::Register(&teapot4);
	//teapot4.pos = Vec3f(0, 25, 0);
	//teapot4.rot = Vec3f(-90, 0, 0);
	//teapot4.scale = Vec3f(0.5, 0.5, 0.5);

	//// Setting up teapot
	//Teapot teapot5;
	//Entity::Register(&teapot5);
	//teapot5.pos = Vec3f(0, -25, 0);
	//teapot5.rot = Vec3f(-90, 0, 0);
	//teapot5.scale = Vec3f(0.5, 0.5, 0.5);

	//// Setting up teapot
	//Teapot teapot6;
	//Entity::Register(&teapot6);
	//teapot6.pos = Vec3f(0, 0, 25);
	//teapot6.rot = Vec3f(-90, 0, 0);
	//teapot6.scale = Vec3f(0.5, 0.5, 0.5);

	//TexturedQuad frontwall;
	//Entity::Register(&frontwall);
	//frontwall.pos = Vec3f(0, 0, -40);
	//frontwall.rot = Vec3f(0, 0, 0);
	//frontwall.scale = Vec3f(50.0f, 50.0f, 50.0f);

	//TexturedQuad backwall;
	//Entity::Register(&backwall);
	//backwall.pos = Vec3f(0, 0, 40);
	//backwall.rot = Vec3f(0, 180, 0);
	//backwall.scale = Vec3f(50.0f, 50.0f, 50.0f);

	//TexturedQuad leftwall;
	//Entity::Register(&leftwall);
	//leftwall.pos = Vec3f(-40, 0, 0);
	//leftwall.rot = Vec3f(0, 90, 0);
	//leftwall.scale = Vec3f(50.0f, 50.0f, 50.0f);

	//TexturedQuad rightwall;
	//Entity::Register(&rightwall);
	//rightwall.pos = Vec3f(40, 0, 0);
	//rightwall.rot = Vec3f(0, -90, 0);
	//rightwall.scale = Vec3f(50.0f, 50.0f, 50.0f);

	//TexturedQuad topwall;
	//Entity::Register(&topwall);
	//topwall.pos = Vec3f(0, 40, 0);
	//topwall.rot = Vec3f(90, 0, 0);
	//topwall.scale = Vec3f(50.0f, 50.0f, 50.0f);

	//Quad bottomwall;
	//Entity::Register(&bottomwall);
	//bottomwall.pos = Vec3f(0, -40, 0);
	//bottomwall.rot = Vec3f(-90, 0, 0);
	//bottomwall.scale = Vec3f(50.0f, 50.0f, 50.0f);

	////Setting up lights
	//AmbientLight ambientlight;
	//ambientlight.intensity = Vec3f(0.5f, 0.5f, 0.5f);

	//MyPointLight pointlight;
	//pointlight.intensity = Vec3f(10.0f, 10.0f, 10.0f);
	//pointlight.pos = Vec3f(0.f, 0.f, 0.f);

	//MyPointLight pointlight2;
	//pointlight2.intensity = Vec3f(30.0f, 30.0f, 30.0f);
	//pointlight2.pos = Vec3f(20.f, 20.f, 20.f);

	//Entity::RegisterAmbientLight(&ambientlight);
	//Entity::RegisterPointLight(&pointlight);
	//Entity::RegisterPointLight(&pointlight2);

	///////////////////////////////////////////////////////////

	//SpherePBR_Test * sphere[64];

	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		sphere[8 * i + j] = ObjectFactory<SpherePBR_Test>::Create();
	//		sphere[8 * i + j]->ChangePos(Vec3f(6.25f * i - 20.0f, 6.25f * j - 20.0f, -60.0f));
	//		sphere[8 * i + j]->ChangeMaterialParameter(0.125f * i, 0.125f * j);
	//		sphere[8 * i + j]->scale = Vec3f(0.1f, 0.1f, 0.1f);
	//		Entity::Register(sphere[8 * i + j]);
	//	}
	//}

	OwningPointer<RastedSphere> rastered = ObjectFactory<RastedSphere>::Create();
	rastered->Translate(Vec3f(0, 0, -60));
	rastered->scale = Vec3f(0.3f, 0.3f, 0.3f);

	//OwningPointer<ScuffedGoldSphere> gold = ObjectFactory<ScuffedGoldSphere>::Create();
	//gold->Translate(Vec3f(15, 0, -60));
	//gold->scale = Vec3f(0.3f, 0.3f, 0.3f);

	//WornPaintedCement cement;
	//cement.Translate(Vec3f(-15, 0, -60));
	//cement.scale = Vec3f(0.3f, 0.3f, 0.3f);

	//MetalGridSphere metalgrid;
	//metalgrid.Translate(Vec3f(-15, 15, -60));
	//metalgrid.scale = Vec3f(0.3f, 0.3f, 0.3f);

	//BathRoomTileSphere bathroomtile;
	//bathroomtile.Translate(Vec3f(-15, -15, -60));
	//bathroomtile.scale = Vec3f(0.3f, 0.3f, 0.3f);

	//DirtyWickerWeaveSphere dirtyweave;
	//dirtyweave.Translate(Vec3f(15, -15, -60));
	//dirtyweave.scale = Vec3f(0.3f, 0.3f, 0.3f);

	//GrayBrickSphere graybrick;
	//graybrick.Translate(Vec3f(15, 15, -60));
	//graybrick.scale = Vec3f(0.3f, 0.3f, 0.3f);

	//BrushedMetalSphere brushedmetal;
	//brushedmetal.Translate(Vec3f(0, 15, -60));
	//brushedmetal.scale = Vec3f(0.3f, 0.3f, 0.3f);

	//OldSoiledClothSphere oldsoiledcloth;
	//oldsoiledcloth.Translate(Vec3f(0, -15, -60));
	//oldsoiledcloth.scale = Vec3f(0.3f, 0.3f, 0.3f);

	Entity::Register(rastered);
	//Entity::Register(gold);
	//Entity::Register(&cement);
	//Entity::Register(&metalgrid);
	//Entity::Register(&bathroomtile);
	//Entity::Register(&dirtyweave);
	//Entity::Register(&graybrick);
	//Entity::Register(&brushedmetal);
	//Entity::Register(&oldsoiledcloth);

	OwningPointer<MyPointLight> pointlight = ObjectFactory<MyPointLight>::Create();
	pointlight->intensity = Vec3f(25.0f, 25.0f, 25.0f);
	pointlight->pos = Vec3f(0.f, 0.f, -40.f);

	//PointLight pointlight2;
	//pointlight2.intensity = Vec3f(10.0f, 10.0f, 10.0f);
	//pointlight2.pos = Vec3f(30.f, -30.f, -40.f);

	//PointLight pointlight3;
	//pointlight3.intensity = Vec3f(10.0f, 10.0f, 10.0f);
	//pointlight3.pos = Vec3f(-30.f, 30.f, -40.f);

	//PointLight pointlight4;
	//pointlight4.intensity = Vec3f(10.0f, 10.0f, 10.0f);
	//pointlight4.pos = Vec3f(-30.f, -30.f, -40.f);

	Entity::RegisterPointLight(pointlight);
	//Entity::RegisterPointLight(&pointlight2);
	//Entity::RegisterPointLight(&pointlight3);
	//Entity::RegisterPointLight(&pointlight4);

	/////////////////////////////////////////////////////////


	//TexturedQuad quad;
	//quad.pos = Vec3f(0, -10, -100);
	//quad.rot = Vec3f(-90, 0, 0);
	//quad.scale = Vec3f(10.0, 100.0, 10.0);
	//Entity::Register(&quad);

	//TexturedQuad quad2;
	//quad2.pos = Vec3f(10, 0, -100);
	//quad2.rot = Vec3f(-90, 0, 90);
	//quad2.scale = Vec3f(10.0, 100.0, 10.0);
	//Entity::Register(&quad2);

	//TexturedQuad quad3;
	//quad3.pos = Vec3f(-10, 0, -100);
	//quad3.rot = Vec3f(-90, 0, -90);
	//quad3.scale = Vec3f(10.0, 100.0, 10.0);
	//Entity::Register(&quad3);

	//TexturedQuad quad4;
	//Entity::Register(&quad4);
	//quad4.pos = Vec3f(0, 10, -100);
	//quad4.rot = Vec3f(90, 0, 0);
	//quad4.scale = Vec3f(10.0, 100.0, 10.0);

	//TexturedQuad quad5;
	//Entity::Register(&quad5);
	//quad5.pos = Vec3f(0, 0, -80);
	//quad5.rot = Vec3f(0, 0, 0);
	//quad5.scale = Vec3f(10.0, 10.0, 10.0);

	////Setting up lights
	//AmbientLight ambientlight;
	//ambientlight.intensity = Vec3f(0.1f, 0.1f, 0.1f);
	//PointLight pointlight;
	//pointlight.intensity = Vec3f(0.2f, 0.f, 0.f);
	//pointlight.pos = Vec3f(9.f, 9.f, -20.f);
	//PointLight pointlight2;
	//pointlight2.intensity = Vec3f(0.0f, 5.0f, 5.0f);
	//pointlight2.pos = Vec3f(-5.0f, -5.0f, -5.f);
	//PointLight pointlight3;
	//pointlight3.intensity = Vec3f(40.0f, 40.0f, 40.0f);
	//pointlight3.pos = Vec3f(0.0f, 0.0f, -70.f);

	//Entity::RegisterAmbientLight(&ambientlight);
	//Entity::RegisterPointLight(&pointlight);
	////Entity::RegisterPointLight(&pointlight2);
	//Entity::RegisterPointLight(&pointlight3);

	System::Boot();

	System::Start();

	return 0;
};