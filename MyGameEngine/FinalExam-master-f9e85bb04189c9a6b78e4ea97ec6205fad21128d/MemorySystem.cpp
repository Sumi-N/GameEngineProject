#include "MemorySystem.h"
#include "NewHeapManager.h"

bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	_current = i_pHeapMemory;
	p_fixedallocator[0] = _current;
	_current = allocator[0].initialize(_current, 16, 100);
	p_fixedallocator[1] = _current;
	_current = allocator[1].initialize(_current, 32, 200);
	p_fixedallocator[2] = _current;
	_current = allocator[2].initialize(_current, 96, 400);
	NewHeapManager::initialize(_current,i_sizeHeapMemory - (16 * 100 + 32 * 200 + 96 * 400));
	return true;
}

void Collect()
{
	normalmanager.collect();
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
}

void DestroyMemorySystem()
{
	// Destroy your HeapManager and FixedSizeAllocators
}

void * AllocMemory(size_t size)
{	
	return normalmanager._alloc(size);
	/*
	if (size <= 16) {
		return	allocator[0].alloc();
	}
	else if(size <= 32){
		return	allocator[1].alloc();
	}
	else if (size <= 96) {
		return	allocator[2].alloc();
	}
	else 
	{
		return normalmanager._alloc(size);
	}
	*/
}

void FreeMemory(void * i_ptr)
{
	normalmanager._free(i_ptr);
	/*
	if (i_ptr < p_fixedallocator[0]) {
		allocator[0].free(i_ptr);
	}
	else if (i_ptr < p_fixedallocator[1]) {
		allocator[1].free(i_ptr);
	}
	else if (i_ptr < p_fixedallocator[2]) {
		allocator[2].free(i_ptr);
	}
	else
	{
		normalmanager._free(i_ptr);
	}
	*/
}

