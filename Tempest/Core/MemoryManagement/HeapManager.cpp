#include "HeapManager.h"

void* HeapManager::initialize(void* i_ptr, size_t i_size)
{
	if (!i_ptr)
	{
		DEBUG_ASSERT(false);
	}

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

void* HeapManager::alloc(size_t i_size)
{
	bool require_collect = false;

	_current = _head;
	Unit* iterator = static_cast<Unit*>(_current);

	//Check if there is a space to insert block
	while (iterator->exist == true || iterator->size < i_size + sizeof(Unit))
	{
		_current = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + iterator->size + sizeof(Unit));
		iterator = static_cast<Unit*>(_current);
		if (_current >= _end)
		{
			DEBUG_PRINT("Start collecting the heap since there is not enought memory to allocate");
			require_collect = true;
			break;
		}
	}

	if (require_collect)
	{
		_current = _head;
		iterator = static_cast<Unit*>(_current);

		while (iterator->exist == true || iterator->size < i_size + sizeof(Unit))
		{
			_current = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + iterator->size + sizeof(Unit));
			iterator = static_cast<Unit*>(_current);
			if (_current >= _end)
			{				
				DEBUG_PRINT("There is not enough memory to allocate");
				DEBUG_ASSERT(false);
				return nullptr;
			}
		}
	}

	//Split one descriptor to two descriptors
	size_t empty_space = iterator->size;
	iterator->exist = true;
	iterator->size = i_size;
	void* return_address = reinterpret_cast<void*>(reinterpret_cast<size_t>(_current) + sizeof(Unit));
	_current = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + iterator->size + sizeof(Unit));
	Unit* padding = static_cast<Unit*>(_current);
	padding->exist = false;
	padding->size = empty_space - (i_size + sizeof(Unit));
	return return_address;
}

void* HeapManager::realloc(void* i_ptr, size_t i_size)
{
	if (!i_ptr)
	{
		DEBUG_ASSERT(false);
	}

	bool require_collect = false;

	_current = _head;
	Unit* iterator = static_cast<Unit*>(_current);

	//Check if there is a space to insert block
	while (iterator->exist == true || iterator->size < i_size + sizeof(Unit))
	{
		_current = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + iterator->size + sizeof(Unit));
		iterator = static_cast<Unit*>(_current);
		if (_current >= _end)
		{
			DEBUG_PRINT("Start collecting the heap since there is not enought memory to allocate");
			require_collect = true;
			break;
		}
	}

	if (require_collect)
	{
		_current = _head;
		iterator = static_cast<Unit*>(_current);

		while (iterator->exist == true || iterator->size < i_size + sizeof(Unit))
		{
			_current = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + iterator->size + sizeof(Unit));
			iterator = static_cast<Unit*>(_current);
			if (_current >= _end)
			{
				DEBUG_PRINT("There is not enough memory to allocate");
				DEBUG_ASSERT(false);
				return nullptr;
			}
		}
	}

	//Split one descriptor to two descriptors
	size_t empty_space = iterator->size;
	iterator->exist = true;
	iterator->size = i_size;
	void* return_address = reinterpret_cast<void*>(reinterpret_cast<size_t>(_current) + sizeof(Unit));
	_current = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + iterator->size + sizeof(Unit));
	Unit* padding = static_cast<Unit*>(_current);
	padding->exist = false;
	padding->size = empty_space - (i_size + sizeof(Unit));

	memcpy(return_address, i_ptr, i_size);

	free(i_ptr);

	return return_address;
}

bool HeapManager::free(void* i_ptr)
{
	if (!i_ptr)
	{
		DEBUG_ASSERT(false);
	}

	_current = reinterpret_cast<void*>(reinterpret_cast<size_t>(i_ptr) - sizeof(Unit));
	Unit* freeing_descriptor = static_cast<Unit*>(_current);
	if (!freeing_descriptor->exist)
	{
		DEBUG_ASSERT(false);
	}
	freeing_descriptor->exist = false;
	return true;
}

void HeapManager::collect()
{
	_current = _head;
	Unit* current_descriptor = static_cast<Unit*>(_current);
	void* _next = reinterpret_cast<void*>(reinterpret_cast<size_t>(_current) + current_descriptor->size + sizeof(Unit));
	Unit* nextdescriptor = static_cast<Unit*>(_next);
	while (_next <= _end)
	{
		if (current_descriptor->exist == false && nextdescriptor->exist == false)
		{
			current_descriptor->size += (nextdescriptor->size + sizeof(Unit));
			_next = reinterpret_cast<void*>(reinterpret_cast<size_t>(_next) + nextdescriptor->size + sizeof(Unit));
			nextdescriptor = static_cast<Unit*>(_next);
		}
		else
		{
			_current = _next;
			_next = reinterpret_cast<void*>(reinterpret_cast<size_t>(_next) + nextdescriptor->size + sizeof(Unit));
			current_descriptor = static_cast<Unit*>(_current);
			nextdescriptor = static_cast<Unit*>(_next);
		}
	}

	return;
}
