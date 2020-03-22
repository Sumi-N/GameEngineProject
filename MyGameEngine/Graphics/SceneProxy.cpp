#pragma once

#include "SceneProxy.h"

void SceneProxy::Init()
{
	InitBuffer();
	InitMeshData();
	InitTexture();
}

void SceneProxy::CleanUp()
{

}