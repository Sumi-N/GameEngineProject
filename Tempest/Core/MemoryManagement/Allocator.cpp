#include "Define.h"
#include "MemorySystem.h"

#include <inttypes.h>
#include <malloc.h>

#ifdef CUSTOM_ALLOCATOR

const size_t 		sizeHeap = 1024 * 1024 * 1024;
const unsigned int 	numDescriptors = 2048;

void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
//bool test = InitializeMemorySystem(pHeapMemory, sizeHeap, numDescriptors);

//void* __cdecl malloc(size_t i_size)
//{	
//	DEBUG_PRINT("malloc %zu", i_size);
//	return AllocMemory(i_size);
//}
//
//void __cdecl free(void* i_ptr)
//{	
//	DEBUG_PRINT("free 0x%" PRIXPTR, reinterpret_cast<uintptr_t>(i_ptr));
//	return FreeMemory(i_ptr);
//}

void* operator new(size_t i_size)
{	
	if (!IsHeapInitialized)
	{
		IsHeapInitialized = true;
		void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
		InitializeMemorySystem(pHeapMemory, sizeHeap, numDescriptors);
	}

	DEBUG_PRINT("new %zu", i_size);
	return AllocMemory(i_size);
}

void operator delete(void* i_ptr)
{	
	DEBUG_PRINT("delete 0x%" PRIXPTR, reinterpret_cast<uintptr_t>(i_ptr));
	return FreeMemory(i_ptr);
}

void* operator new[](size_t i_size)
{	
	DEBUG_PRINT("new [] %zu", i_size);
	return AllocMemory(i_size);
}

void operator delete [](void* i_ptr)
{	
	DEBUG_PRINT("delete [] 0x%" PRIXPTR, reinterpret_cast<uintptr_t>(i_ptr));
	return FreeMemory(i_ptr);
}

#endif // CUSTOM_ALLOCATOR