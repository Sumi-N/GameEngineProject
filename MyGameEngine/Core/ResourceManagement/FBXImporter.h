#pragma once

#include "Define.h"

class FBXImporter
{
public:
	ofbx::IScene* g_scene = nullptr;

	bool Import(const char*);
	bool saveAsOBJ(ofbx::IScene&, const char*);
};

