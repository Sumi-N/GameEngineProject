#include "NewHeapManager.h"

#include <Windows.h>

void * NewHeapManager::initialize(void * i_ptr, size_t i_size)
{
	_head = i_ptr;
	_current = i_ptr;
	_size = i_size;
	if (reinterpret_cast<uintptr_t>(_current) >= reinterpret_cast<uintptr_t>(_head) + i_size) {
		return nullptr;
	}

	static_cast<Using *>(_head)->exit = false;
	static_cast<Using *>(_head)->size = i_size;

	return _current;
}

void * NewHeapManager::_alloc(size_t)
{
	_current = _head;
	Using * iterator = static_cast<Using *>(_head);
	while (iterator->exit != false) {

	}
	return nullptr;
}

bool NewHeapManager::_free(void *)
{
	return false;
}

void NewHeapManager::collect()
{
}
