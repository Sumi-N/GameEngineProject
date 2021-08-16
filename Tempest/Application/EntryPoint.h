#pragma once

#include "Define.h"
#include "Application.h"

int main()
{
	MEMORY_LEAK_DETECTION

	auto app = Tempest::Create();
	delete app;	

	return 0;
};