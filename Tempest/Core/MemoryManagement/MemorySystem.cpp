#include "MemorySystem.h"
#include "HeapManager.h"

void InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{	
	IsHeapInitialized = true;

	_current = i_pHeapMemory;
	/*_current = allocator[0].initialize(_current, 16);
	_current = allocator[1].initialize(_current, 32);
	_current = allocator[2].initialize(_current, 96);
	_current = allocator[3].initialize(_current, 96);*/
	//HeapManager::initialize(reinterpret_cast<void*>(reinterpret_cast<size_t>(_current) + 96 * 200), i_sizeHeapMemory - (16 * 200 + 32 * 200 + 96 * 400));
	HeapManager::initialize(reinterpret_cast<void*>(reinterpret_cast<size_t>(_current)), i_sizeHeapMemory);	
}

bool IsHeapAlive()
{
	return IsHeapInitialized;
}

void DestroyMemorySystem()
{
	IsHeapInitialized = false;
	// Destroy your HeapManager and FixedSizeAllocators
}

void* AllocMemory(size_t i_size)
{
	return generalmanager.alloc(i_size);

	//if (size <= 16)
	//{
	//	return	allocator[0].alloc();
	//}
	//else if (size <= 32)
	//{
	//	return	allocator[1].alloc();
	//}
	//else if (size <= 96)
	//{
	//	if (allocator[2].alloc() == nullptr)
	//	{
	//		return allocator[3].alloc();
	//	}
	//	return	allocator[2].alloc();
	//}
	//else
	//{
	//	return generalmanager._alloc(size);
	//}
}

void* ReallocMemory(void* i_ptr, size_t i_size)
{
	return generalmanager.realloc(i_ptr, i_size);
}

void Collect()
{
	generalmanager.collect();
}

void FreeMemory(void* i_ptr)
{
	generalmanager.free(i_ptr);

	//if (i_ptr >= allocator[0].head && allocator[1].head > i_ptr)
	//{
	//	allocator[0].free(i_ptr);
	//}
	//else if (i_ptr >= allocator[1].head && allocator[2].head > i_ptr)
	//{
	//	allocator[1].free(i_ptr);
	//}
	//else if (i_ptr >= allocator[2].head && allocator[3].head > i_ptr)
	//{
	//	allocator[2].free(i_ptr);
	//}
	//else if (i_ptr >= allocator[3].head && reinterpret_cast<size_t>(allocator[3].head) + 96 * 200 > reinterpret_cast<size_t>(i_ptr))
	//{
	//	allocator[3].free(i_ptr);
	//}
	//else
	//{
	//	generalmanager._free(i_ptr);
	//}
}

