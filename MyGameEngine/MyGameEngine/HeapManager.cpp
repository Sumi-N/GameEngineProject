#include "HeapManager.h"
#include "DebugLog.h"

HeapManager * HeapManager::create(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	_head = (HeapManager *)i_pMemory;
	_current = (HeapManager *)i_pMemory;
	_size = i_sizeMemory;
	_desnum = i_numDescriptors;

	Using* tmp = (Using *)i_pMemory;
	tmp->exit = false;
	tmp->size = i_sizeMemory;
	return _head;
}

void HeapManager::destroy()
{
}

void * HeapManager::_alloc(size_t i_size)
{
	_current = (HeapManager *)_current + i_size;
	if (_current >= (HeapManager *)_head + _size) {
		_current = nullptr;
	}
	return _current;
}

void * HeapManager::_alloc(size_t i_size, unsigned int i_alignment)
{
	//check if it won't overflow from the heap
	if ( _current + i_size >= _head + _size) {
		return nullptr;
	}

	Using * current = (Using *)_current;
	if (current->exit) {
		//_current += current->size;
	}
	else {

	}
	//calculate number of the chanks it needs
	unsigned int chanks = (i_size + sizeof(Using))/ i_alignment + 1;
	//assigne discriptor to the head of the memory
	Using tmp = {true, chanks * i_alignment};
	_current = &tmp;
	
	_current = (HeapManager *)_current + i_alignment * (size_t)chanks;
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

