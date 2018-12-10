#include "MemorySystem.h"
#include "NewHeapManager.h"

bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	_current = i_pHeapMemory;
	_current = allocator[0].initialize(_current, 16);
	_current = allocator[1].initialize(_current, 32);
	_current = allocator[2].initialize(_current, 96);
	_current = allocator[3].initialize(_current, 96);
	NewHeapManager::initialize(_current,i_sizeHeapMemory - (16 * 200 + 32 * 200 + 96 * 400));
	return true;
}

void Collect()
{
	generalmanager.collect();
	
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
}

void DestroyMemorySystem()
{
	// Destroy your HeapManager and FixedSizeAllocators
}

void * AllocMemory(size_t size)
{	
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
		return generalmanager._alloc(size);
	}
}

void FreeMemory(void * i_ptr)
{
	if (i_ptr >= allocator[0].head && allocator[1].head > i_ptr) {
		allocator[0].free(i_ptr);
	}
	else if (i_ptr >= allocator[1].head && allocator[2].head > i_ptr) {
		allocator[1].free(i_ptr);
	}
	else if (i_ptr >= allocator[2].head && _head > i_ptr) {
		allocator[2].free(i_ptr);
	}
	else
	{
		generalmanager._free(i_ptr);
	}
}

