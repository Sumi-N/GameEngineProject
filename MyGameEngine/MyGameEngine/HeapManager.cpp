#include "HeapManager.h"
#include "DebugLog.h"
#include <stdio.h>

HeapManager * HeapManager::create(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	_head = (unsigned char *)i_pMemory;
	_current = (unsigned char *)i_pMemory;
	_size = i_sizeMemory;
	_desnum = i_numDescriptors;

	Using * tmp = (Using *)i_pMemory;
	tmp->exit = false;
	tmp->size = i_sizeMemory;
	return (HeapManager *)_current;
}

void HeapManager::destroy()
{
}

void * HeapManager::_alloc(size_t i_size)
{
	_current = _current + i_size;
	if (_current >= (unsigned char *)_head + _size) {
		_current = nullptr;
	}
	return _current;
}

void * HeapManager::_alloc(size_t i_size, unsigned int i_alignment)
{	
	//check if the pointer for current memory is exit
	Using * __current = (Using *)_current;
	if (__current->exit) {
		_current += __current->size;
	}
	//make a padding
	size_t distance = _current - _head ;
	Using * padding = (Using *)_current;
	padding->exit = false;
	padding->size = ((distance + sizeof(Using)) / i_alignment + 1) * i_alignment - distance;
	_current += padding->size;

	//check if it won't overflow from the heap
	if ( _current + i_size >= _head + _size) {
		return nullptr;
	}

	//calculate number of the chanks it needs
	unsigned int chanks = (i_size + sizeof(Using))/ i_alignment + 1;
	//assigne discriptor to the head of the memory

	Using * tmp = (Using *)_current;
	tmp->exit = true;
	tmp->size = chanks * i_alignment;

	return (void *)_current;
}


bool HeapManager::_free(void * i_ptr)
{
	Using * tmp = (Using * )i_ptr;
	tmp->exit = false;
	return true;
}

void HeapManager::collect()
{
}

bool HeapManager::Contains(void * i_ptr) const
{
	if (i_ptr >= this && i_ptr < this + _size){
		return true;
	}
	return false;
}

bool HeapManager::IsAllocated(void * i_ptr) const
{
	Using * tmp = (Using *)i_ptr;
	if (tmp->exit) {
		return true;
	}
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

