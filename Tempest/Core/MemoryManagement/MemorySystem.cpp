#include "MemorySystem.h"
#include "HeapManager.h"

bool InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{	
	IsHeapInitialized = true;

	_current = i_pHeapMemory;
	_current = allocator[0].initialize(_current, 16);
	_current = allocator[1].initialize(_current, 32);
	_current = allocator[2].initialize(_current, 96);
	_current = allocator[3].initialize(_current, 96);
	HeapManager::initialize(reinterpret_cast<void*>(reinterpret_cast<size_t>(_current) + 96 * 200), i_sizeHeapMemory - (16 * 200 + 32 * 200 + 96 * 400));
	return true;
}

bool IsHeapAlive()
{
	return IsHeapInitialized;
}

void Collect()
{
	generalmanager.collect();

	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
}

void DestroyMemorySystem()
{
	IsHeapInitialized = false;
	// Destroy your HeapManager and FixedSizeAllocators
}

//Allocate memory to certain heap manager depend on how much size the allocation is 
void* AllocMemory(size_t size)
{
	return generalmanager._alloc(size);

	if (size <= 16)
	{
		return	allocator[0].alloc();
	}
	else if (size <= 32)
	{
		return	allocator[1].alloc();
	}
	else if (size <= 96)
	{
		if (allocator[2].alloc() == nullptr)
		{
			return allocator[3].alloc();
		}
		return	allocator[2].alloc();
	}
	else
	{
		return generalmanager._alloc(size);
	}
}

//Free memory on certain heapmanager
void FreeMemory(void* i_ptr)
{
	if (i_ptr >= allocator[0].head && allocator[1].head > i_ptr)
	{
		allocator[0].free(i_ptr);
	}
	else if (i_ptr >= allocator[1].head && allocator[2].head > i_ptr)
	{
		allocator[1].free(i_ptr);
	}
	else if (i_ptr >= allocator[2].head && allocator[3].head > i_ptr)
	{
		allocator[2].free(i_ptr);
	}
	else if (i_ptr >= allocator[3].head && reinterpret_cast<size_t>(allocator[3].head) + 96 * 200 > reinterpret_cast<size_t>(i_ptr))
	{
		allocator[3].free(i_ptr);
	}
	else
	{
		generalmanager._free(i_ptr);
	}
}

