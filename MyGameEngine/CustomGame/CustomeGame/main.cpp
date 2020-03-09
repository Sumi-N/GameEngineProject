#pragma once

#include <Core/Thread/EntryPoint.h>
#include <Parts/MeshComponent.h>
#include <Parts/Object.h>

#include "Teapot.h"

#include <stdio.h>

int main()
{
	Teapot teapot;
	MeshComponent teapotmesh;
	teapotmesh.Load("../../Assets/models/teapot.obj");
	System::Boot();
	return 0;
};