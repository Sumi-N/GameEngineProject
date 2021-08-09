#pragma once

#include "Define.h"
#include "Application.h"

int main()
{
	MEMORY_LEAK_DETECTION

#ifdef ENABLE_CUSTOM_ALLOCATOR
	INITIALIZE_HEAP_MANAGER
#endif
	pHeapMemory = HeapAlloc(GetProcessHeap(), 0, HEAP_SIZE); 
	if (!pHeapMemory)
	{
		DEBUG_ASSERT(true); 
	}		

	auto app = Tempest::Create();
	delete app;	

	return 0;
};