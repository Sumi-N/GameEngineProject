#pragma once
#include "TestScenes.h"

#include "MyCamera.h"
#include "MyPointLight.h"
#include "MySkyBox.h"
#include <PremadeParts/Cube.h>

#include <ResourceManagement/FBXImporter.h>

void TestScene::Importer()
{
	FBXImporter fbx;
	//fbx.Import(PATH_SUFFIX MESH_PATH "cube.fbx");
	std::vector<MeshData> data;
	std::vector<int> index;
	//fbx.LoadMesh(PATH_SUFFIX MESH_PATH "cube.fbx", data, index);

	// Setting up camera
	OwningPointer<MyCamera> mycamera = OwningPointer<MyCamera>::Create(mycamera);
	Entity::RegisterCamera(mycamera);

	OwningPointer<MyPointLight> pointlight = OwningPointer<MyPointLight>::Create(pointlight);
	pointlight->intensity = Vec3f(25.0f, 25.0f, 25.0f);
	pointlight->pos = Vec3f(0.f, 0.f, -40.f);
	Entity::RegisterPointLight(pointlight);

	OwningPointer<Cube> cube = OwningPointer<Cube>::Create(cube);
	cube->Translate(Vec3f(0, 0, -60));
	cube->scale = Vec3f(10.0f, 10.0f, 10.0f);
	Entity::Register(cube);
}