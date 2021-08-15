#pragma once

#include "Define.h"
#include "Application.h"

int main()
{
	MEMORY_LEAK_DETECTION

#ifdef ENABLE_CUSTOM_ALLOCATOR
	INITIALIZE_HEAP_MANAGER
#endif	

	auto app = Tempest::Create();
	delete app;	

#ifdef ENABLE_CUSTOM_ALLOCATOR
	//FINALIZE_HEAP_MANAGER
#endif	

	return 0;
};