#include "HeapManager.h"
//#include "DebugLog.h"
#include <stdio.h>

HeapManager * HeapManager::create(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	_head = static_cast<unsigned char *>(i_pMemory);
	_current = static_cast<unsigned char *>(i_pMemory);
	_size = i_sizeMemory;
	_desnum = i_numDescriptors;

	
	while (reinterpret_cast<uintptr_t>(_head) % 64 != 0) {
		_head++;
		_current++;
		_size--;
	}

	//Using * tmp = static_cast<Using *>(i_pMemory);
	Using * tmp = reinterpret_cast<Using *>(_head);
	tmp->exit = false;
	//tmp->size = i_sizeMemory;
	tmp->size = _size;
	return reinterpret_cast<HeapManager *>(_current);
}

void HeapManager::destroy()
{
}

void * HeapManager::_alloc(size_t i_size)
{
	_current = _current + i_size;
	if (_current >= reinterpret_cast<unsigned char *>(_head) + _size) {
		_current = nullptr;
	}
	Using * tmp = reinterpret_cast<Using *>(_current);
	tmp->exit = true;
	tmp->size = i_size;
	return _current;
}

void * HeapManager::_alloc(size_t i_size, unsigned int i_alignment)
{	
	//check if the pointer for current memory is exit
	Using * __current = reinterpret_cast<Using *>(_current);
	if (__current->exit) {
		_current += __current->size;
	}

	//make a padding
	size_t distance = _current - _head ;
	Using * padding = reinterpret_cast<Using *>(_current);
	padding->exit = false;
	padding->size = ((distance + sizeof(Using)) / i_alignment + 1) * i_alignment - distance;
	_current += padding->size;
	//printf("padding is %d\n", padding->size);

	//check if it won't overflow from the heap
	if ( _current + i_size >= _head + _size) {
		return nullptr;
	}

	//calculate number of the chanks it needs
	size_t chanks = (i_size + sizeof(Using))/ i_alignment + 1;

	//assigne discriptor to the head of the memory
	Using * tmp = reinterpret_cast<Using *>(_current);
	tmp->exit = true;
	tmp->size = chanks * i_alignment;
	//printf("the size of alloc %d\n", tmp->size);
	return static_cast<void *>(_current);
}


bool HeapManager::_free(void * i_ptr)
{
	Using * tmp = reinterpret_cast<Using *>(i_ptr);
	tmp->exit = false;
	return true;
}

void HeapManager::collect()
{ 
	unsigned char * convertor;
	Using * curr = reinterpret_cast<Using *>(_head);
	convertor = reinterpret_cast<unsigned char *>(curr);
	convertor += curr->size;
	curr = reinterpret_cast<Using *>(convertor);
	Using * prev = reinterpret_cast<Using *>(_head);

	while (reinterpret_cast<unsigned char *>(curr) <= _head + _size) {
		if (curr->exit) {
			prev = curr;
			convertor = (unsigned char *)curr;
			convertor += curr->size;
			curr = reinterpret_cast<Using *>(convertor);
		}
		else {
			if (prev->exit) {
				prev = curr;
				convertor = reinterpret_cast<unsigned char *>(curr);
				convertor += curr->size;
				curr = reinterpret_cast<Using *>(convertor);
			}
			else {
				prev->size += curr->size;
				convertor = reinterpret_cast<unsigned char *>(curr);
				convertor += curr->size;
				curr = reinterpret_cast<Using *>(convertor);
			}
		}

		if (curr->size == 0) {
			break;
		}
	}
	_current = reinterpret_cast<unsigned char *>(prev);
	/*
	unsigned char * convertor;
	Using * curr = (Using *)_head;
	convertor = (unsigned char *)curr;
	convertor += curr->size;
	curr = (Using *)convertor;
	Using * prev = (Using *)_head;

	Using currdata;
	Using prevdata;

	while ((unsigned char *)curr <= _head + _size) {
		
		if (curr->exit) {
			if (prev->exit) {
				prev = curr;
				convertor = (unsigned char *)curr;
				convertor += curr->size;
				curr = (Using *)convertor;
			}
			else {
				prevdata.exit = curr->exit;
				prevdata.size = curr->size;
				currdata.exit = prev->exit;
				currdata.size = prev->size;

				convertor = (unsigned char *)prev;
				convertor += curr->size;
				curr = (Using *)convertor;

				curr->exit = currdata.exit;
				curr->size = currdata.size;
				prev->exit = prevdata.exit;
				prev->size = prevdata.size;

				prev = curr;
				convertor = (unsigned char *)curr;
				convertor += curr->size;
				curr = (Using *)convertor;
			}
		}
		else {
			if(prev->exit){
				prev = curr;
				convertor = (unsigned char *)curr;
				convertor += curr->size;
				curr = (Using *)convertor;
			}
			else {
				prev->size += curr->size;
				convertor = (unsigned char *)curr;
				convertor += curr->size;
				curr = (Using *)convertor;
			}
		}

		if (curr->size == 0) {
			break;
		}
	}
	_current = (unsigned char *)prev;
	*/
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
	Using * tmp = static_cast<Using *>(i_ptr);
	if (tmp->exit) {
		return true;
	}
	return false;
}

size_t HeapManager::getLargestFreeBlock() const
{
	size_t max = 0;
	unsigned char * iterator = _head;
	Using * tmp;
	while (iterator <= _head + _size) {
		tmp = reinterpret_cast<Using *>(iterator);
		if (tmp->size == 0) {
			break;
		}
		if (!(tmp->exit)) {
			if (tmp->size > max) {
				max = tmp->size;
			}
		}
		iterator += tmp->size;
	}
	return max;
}


size_t HeapManager::getTotalFreeMemory() const
{
	size_t total = 0;
	unsigned char * iterator = _head;
	Using * tmp;
	while (iterator <= _head + _size) {
		tmp = reinterpret_cast<Using *>(iterator);
		if (tmp->size == 0) {
			break;
		}
		if (!(tmp->exit)) {
			total += tmp->size;
		}
		iterator += tmp->size;
	}
	return total;
}

void HeapManager::ShowFreeBlocks() const
{
	unsigned char * iterator = _head;
	//descriptor number
	int dn = 0;
	Using * tmp;
	while (iterator <= _head + _size) {
		tmp = reinterpret_cast<Using *>(iterator);
		if (tmp->size == 0) {
			break;
		}
		if (!(tmp->exit)) {
			printf("No%d: address %p, size %zu (freed)\n", dn, tmp, tmp->size);
			dn++;
		}
		iterator += tmp->size;
	}
}

void HeapManager::ShowOutstandingAllocations() const
{
	unsigned char * iterator = _head;
	//descriptor number
	int dn = 0;
	Using * tmp;
	while (iterator <= _head + _size) {
		tmp = reinterpret_cast<Using *>(iterator);
		if (tmp->size == 0) {
			break;
		}
		if (tmp->exit) {
			printf("No%d: address %p, size %zu (outstanding) \n", dn, tmp, tmp->size);
			dn++;
		}
		iterator += tmp->size;
	}
}

size_t HeapManager::s_MinumumToLeave()
{
	return size_t();
}

