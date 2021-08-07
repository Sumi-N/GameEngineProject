#include "HeapManager.h"

void* HeapManager::initialize(void* i_ptr, size_t i_size)
{
	_head = i_ptr;
	_current = i_ptr;
	_size = i_size;
	_end = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(_head) + i_size);
	if (_current >= _end)
	{
		return nullptr;
	}

	static_cast<Unit*>(_head)->exist = false;
	static_cast<Unit*>(_head)->size = i_size;

	return _current;
}

void* HeapManager::_alloc(size_t i_size)
{
	_current = _head;
	Unit* iterator = static_cast<Unit*>(_current);

	//Check if there is a space to insert block
	while (iterator->exist == true || iterator->size < i_size + sizeof(Unit))
	{
		_current = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + iterator->size + sizeof(Unit));
		iterator = static_cast<Unit*>(_current);
		if (_current >= _end)
		{
			return nullptr;
		}
	}

	//Split one descriptor to two descriptors
	size_t emptyspace = iterator->size;
	iterator->exist = true;
	iterator->size = i_size;
	void* rtnpoint = reinterpret_cast<void*>(reinterpret_cast<size_t>(_current) + sizeof(Unit));
	_current = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + iterator->size + sizeof(Unit));
	Unit* padding = static_cast<Unit*>(_current);
	padding->exist = false;
	padding->size = emptyspace - (i_size + sizeof(Unit));
	return rtnpoint;
}

bool HeapManager::_free(void* i_ptr)
{
	_current = reinterpret_cast<void*>(reinterpret_cast<size_t>(i_ptr) - sizeof(Unit));
	Unit* freepoint = static_cast<Unit*>(_current);
	freepoint->exist = false;
	return true;
}

//check one descriptor and the next descriptor and see if both of them are not used, then coalease them
void HeapManager::collect()
{
	_current = _head;
	Unit* currentdescriptor = static_cast<Unit*>(_current);
	void* _next = reinterpret_cast<void*>(reinterpret_cast<size_t>(_current) + currentdescriptor->size + sizeof(Unit));
	Unit* nextdescriptor = static_cast<Unit*>(_next);
	while (_next <= _end)
	{
		if (currentdescriptor->exist == false && nextdescriptor->exist == false)
		{
			currentdescriptor->size += (nextdescriptor->size + sizeof(Unit));
			_next = reinterpret_cast<void*>(reinterpret_cast<size_t>(_next) + nextdescriptor->size + sizeof(Unit));
			nextdescriptor = static_cast<Unit*>(_next);
		}
		else
		{
			_current = _next;
			_next = reinterpret_cast<void*>(reinterpret_cast<size_t>(_next) + nextdescriptor->size + sizeof(Unit));
			currentdescriptor = static_cast<Unit*>(_current);
			nextdescriptor = static_cast<Unit*>(_next);
		}
	}

	return;
}
