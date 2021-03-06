#include "NewHeapManager.h"
#include <stdio.h>
#include <Windows.h>

void * NewHeapManager::initialize(void * i_ptr, size_t i_size)
{
	_head = i_ptr;
	_current = i_ptr;
	_size = i_size;
	_over = reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(_head) + i_size);
	if (_current >= _over) {
		return nullptr;
	}

	static_cast<Using *>(_head)->exit = false;
	static_cast<Using *>(_head)->size = i_size;

	return _current;
}

void * NewHeapManager::_alloc(size_t i_size)
{
	_current = _head;
	Using * iterator = static_cast<Using *>(_current);

	//Check if there is a space to insert block
	while (iterator->exit == true || iterator->size < i_size + sizeof(Using)) {
		_current = reinterpret_cast<void *> (reinterpret_cast<size_t>(_current) + iterator->size + sizeof(Using));
		iterator = static_cast<Using *>(_current);
		if (_current >= _over) {
			return nullptr;
		}
	}

	//Split one descriptor to two descriptors
	size_t emptyspace = iterator->size;
	iterator->exit = true;
	iterator->size = i_size;
	void * rtnpoint = reinterpret_cast<void *>(reinterpret_cast<size_t>(_current) + sizeof(Using));
	_current = reinterpret_cast<void *> (reinterpret_cast<size_t>(_current) + iterator->size + sizeof(Using));
	Using * padding = static_cast<Using *>(_current);
	padding->exit = false;
	padding->size = emptyspace - (i_size + sizeof(Using));
	return rtnpoint;
}

bool NewHeapManager::_free(void * i_ptr)
{
	_current = reinterpret_cast<void*>(reinterpret_cast<size_t>(i_ptr) - sizeof(Using));
	Using * freepoint = static_cast<Using*>(_current);
	freepoint->exit = false;
	return true;
}

//check one descriptor and the next descriptor and see if both of them are not used, then coalease them
void NewHeapManager::collect()
{
	_current = _head;
	Using * currentdescriptor = static_cast<Using *>(_current);
	void * _next = reinterpret_cast<void *>(reinterpret_cast<size_t>(_current) + currentdescriptor->size + sizeof(Using));
	Using * nextdescriptor = static_cast<Using *>(_next);
	while(_next <= _over) {
		if (currentdescriptor->exit == false && nextdescriptor->exit == false) {
			currentdescriptor->size += (nextdescriptor->size + sizeof(Using));
			_next = reinterpret_cast<void *>(reinterpret_cast<size_t>(_next) + nextdescriptor->size + sizeof(Using));
			nextdescriptor = static_cast<Using *>(_next);
		}
		else {
			_current = _next;
			_next = reinterpret_cast<void *>(reinterpret_cast<size_t>(_next) + nextdescriptor->size + sizeof(Using));
			currentdescriptor = static_cast<Using *>(_current);
			nextdescriptor = static_cast<Using *>(_next);
		}
	}

	return;
}
