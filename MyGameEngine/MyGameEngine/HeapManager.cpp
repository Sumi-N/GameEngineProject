#include "HeapManager.h"
#include "DebugLog.h"

HeapManager * HeapManager::create(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	_p = i_pMemory;
	_current = _p;
	_size = i_sizeMemory;
	_desnum = i_numDescriptors;
	return (HeapManager *)_p;
}

void HeapManager::destroy()
{
}

void * HeapManager::_alloc(size_t)
{
	return nullptr;
}

void * HeapManager::_alloc(size_t i_size, unsigned int i_alignment)
{
	unsigned int chanks = i_size / i_alignment + 1;
	_current = (HeapManager *)_current + i_alignment * (size_t)chanks;
	return _current;
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

