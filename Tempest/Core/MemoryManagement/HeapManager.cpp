#include "HeapManager.h"

void*  _head;
void*  _current;
void*  _end;
size_t _size;

HeapManager::HeapManager()
{
	DEBUG_PRINT("Heap Manager is created");

#ifdef ENABLE_CUSTOM_ALLOCATOR
	#ifdef ENGINE_PLATFORM_WINDOWS
		_head = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, HEAP_SIZE);	
		Initialize(_head, HEAP_SIZE);
	#endif // ENGINE_PLATFORM_WINDOWS
#endif // ENABLE_CUSTOM_ALLOCATOR

	is_heap_alive = true;
}

HeapManager::~HeapManager()
{
	is_heap_alive = false;

#ifdef ENABLE_CUSTOM_ALLOCATOR
	#ifdef ENGINE_PLATFORM_WINDOWS
		Finalize();	
		HeapFree(GetProcessHeap(), 0, _head);
	#endif // ENGINE_PLATFORM_WINDOWS

	DEBUG_PRINT("Heap Manager was destroyed");
#endif // ENABLE_CUSTOM_ALLOCATOR
}

void* HeapManager::Initialize(void* i_ptr, size_t i_size)
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

	static_cast<Block*>(_head)->exist = false;
	static_cast<Block*>(_head)->size = i_size - sizeof(Block);

	return _current;
}

void HeapManager::Finalize(){

}

void* HeapManager::Alloc(size_t i_size)
{
	bool need_to_collect = false;
	
	Block* current_block = static_cast<Block*>(_current);

	//Check if there is a space to insert block
	while (!(current_block->exist == false && current_block->size >= i_size + sizeof(Block)))
	{		
		_current = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + current_block->size + sizeof(Block));
		current_block = static_cast<Block*>(_current);
		if (reinterpret_cast<size_t>(_current) + sizeof(Block) >= reinterpret_cast<size_t>(_end))
		{
			DEBUG_PRINT("Start collecting the heap since there is not enought memory to allocate");
			need_to_collect = true;
			break;
		}
	}

	if (need_to_collect)
	{
		Collect();

		_current = _head;
		current_block = static_cast<Block*>(_current);

		while (current_block->exist == true || current_block->size < i_size + sizeof(Block))
		{
			_current = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + current_block->size + sizeof(Block));
			current_block = static_cast<Block*>(_current);
			if(reinterpret_cast<size_t>(_current) + sizeof(Block) >= reinterpret_cast<size_t>(_end))
			{				
				DEBUG_PRINT("There is not enough memory to allocate");
				DEBUG_ASSERT(false);
				return nullptr;
			}
		}
	}

	//Now split the descriptor to two descriptors

	size_t available_space = current_block->size;

	current_block->exist = true;
	current_block->size = i_size;
	void* return_address = reinterpret_cast<void*>(reinterpret_cast<size_t>(_current) + sizeof(Block));

	void * next = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + sizeof(Block) + current_block->size);

	Block* next_block = static_cast<Block*>(next);
	next_block->exist = false;
	next_block->size = available_space - (i_size + sizeof(Block));
	_current = next;	

	//DEBUG_PRINT("The _current address is now at %zx", reinterpret_cast<size_t>(_current));
	//DEBUG_PRINT("The _current empty space now at %zu", reinterpret_cast<size_t>(_end) - reinterpret_cast<size_t>(_current));

	return return_address;
}

void* HeapManager::Realloc(void* i_ptr, size_t i_size)
{
	if (!i_ptr)
	{
		DEBUG_ASSERT(false);
	}

	bool need_to_collect = false;
	
	Block* current_block = static_cast<Block*>(_current);

	//Check if there is a space to insert block
	while (!(current_block->exist == false && current_block->size >= i_size + sizeof(Block)))
	{
		_current = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + current_block->size + sizeof(Block));
		current_block = static_cast<Block*>(_current);
		if (reinterpret_cast<size_t>(_current) + sizeof(Block) >= reinterpret_cast<size_t>(_end))
		{
			DEBUG_PRINT("Start collecting the heap since there is not enought memory to allocate");
			need_to_collect = true;
			break;
		}
	}

	if (need_to_collect)
	{
		Collect();

		_current = _head;
		current_block = static_cast<Block*>(_current);

		while (current_block->exist == true || current_block->size < i_size + sizeof(Block))
		{
			_current = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + current_block->size + sizeof(Block));
			current_block = static_cast<Block*>(_current);
			if(reinterpret_cast<size_t>(_current) + sizeof(Block) >= reinterpret_cast<size_t>(_end))
			{
				DEBUG_PRINT("There is not enough memory to allocate");
				DEBUG_ASSERT(false);
				return nullptr;
			}
		}
	}

	//Now split the descriptor to two descriptors

	size_t available_space = current_block->size;

	current_block->exist = true;
	current_block->size = i_size;
	void* return_address = reinterpret_cast<void*>(reinterpret_cast<size_t>(_current) + sizeof(Block));

	void* next = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + sizeof(Block) + current_block->size);
	Block* next_block = static_cast<Block*>(next);
	next_block->exist = false;
	next_block->size = available_space - (i_size + sizeof(Block));
	_current = next;

	memcpy(return_address, i_ptr, i_size);

	Free(i_ptr);

	//DEBUG_PRINT("The _current address is now at %zx", reinterpret_cast<size_t>(_current));
	//DEBUG_PRINT("The _current empty space now at %zu", reinterpret_cast<size_t>(_end) - reinterpret_cast<size_t>(_current));

	return return_address;
}

bool HeapManager::Free(void* i_ptr)
{
	if (!i_ptr)
	{
		DEBUG_ASSERT(false);
	}

	void* freeing = reinterpret_cast<void*>(reinterpret_cast<size_t>(i_ptr) - sizeof(Block));
	Block* freeing_block = static_cast<Block*>(freeing);
	if (!freeing_block->exist)
	{
		DEBUG_ASSERT(false);
	}
	freeing_block->exist = false;
	return true;
}

void HeapManager::Collect()
{
	void*  current_collecting       = _head;
	Block* current_collecting_block = static_cast<Block*>(current_collecting);
	void*  next_collecting          = reinterpret_cast<void*>(reinterpret_cast<size_t>(current_collecting) + current_collecting_block->size + sizeof(Block));
	Block* next_collecting_block    = static_cast<Block*>(next_collecting);
	
	do{
		if (current_collecting_block->exist == false && next_collecting_block->exist == false)
		{
			current_collecting_block->size += (next_collecting_block->size + sizeof(Block));
			next_collecting = reinterpret_cast<void*>(reinterpret_cast<size_t>(next_collecting) + next_collecting_block->size + sizeof(Block));
			next_collecting_block = static_cast<Block*>(next_collecting);
		}
		else if(next_collecting_block->exist == false)
		{
			current_collecting = next_collecting;
			current_collecting_block = static_cast<Block*>(current_collecting);
			next_collecting = reinterpret_cast<void*>(reinterpret_cast<size_t>(next_collecting) + next_collecting_block->size + sizeof(Block));			
			next_collecting_block = static_cast<Block*>(next_collecting);
		}
		else
		{
			current_collecting = reinterpret_cast<void*>(reinterpret_cast<size_t>(next_collecting) + next_collecting_block->size + sizeof(Block));
			current_collecting_block = static_cast<Block*>(current_collecting);
			next_collecting = reinterpret_cast<void*>(reinterpret_cast<size_t>(current_collecting) + current_collecting_block->size + sizeof(Block));
			next_collecting_block = static_cast<Block*>(next_collecting);
		}
	} 
	while 
	(reinterpret_cast<size_t>(next_collecting) + next_collecting_block->size + sizeof(Block) <= reinterpret_cast<size_t>(_end));

	return;
}

bool HeapManager::IsHeapAlive()
{
	return is_heap_alive;
}