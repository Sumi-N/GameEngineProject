#include "HeapManager.h"
#include "DebugLog.h"

HeapManager * HeapManager::create(void *, size_t, unsigned int)
{
	return nullptr;
}

void HeapManager::destroy()
{
}

void * HeapManager::_alloc(size_t)
{
	return nullptr;
}

void * HeapManager::_alloc(size_t, unsigned int)
{
	return nullptr;
}


bool HeapManager::_free(void *)
{
	return false;
}

void HeapManager::collect()
{
}

bool HeapManager::Contains(void *) const
{
	return false;
}

bool HeapManager::IsAllocated(void *) const
{
	return false;
}

size_t HeapManager::getLargestFreeBlock() const
{
	return size_t();
}


size_t HeapManager::getTotalFreeMemory() const
{
	return size_t();
}

void HeapManager::ShowFreeBlocks() const
{
}

void HeapManager::ShowOutstandingAllocatios()
{
}

