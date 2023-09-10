#include "MemoryChunk.h"

#ifdef _DEBUG
#define HEAP_ACCESS_VIOLATION_CHECK(i_block) \
	DEBUG_ASSERT(i_block->headguardbanding != '\0'); \
	DEBUG_ASSERT(i_block->tailguardbanding != '\0');
#endif

namespace Tempest
{
	void MemoryChunk::Initialize(const size_t i_size)
	{
		DEBUG_ASSERT(i_size > 0);

#ifdef ENGINE_PLATFORM_WINDOWS
		void* ptr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, i_size);
		is_self_allcoate = true;
#else
		ENGINE_ASSERT(false);
#endif // ENGINE_PLATFORM_WINDOWS

		Initialize(ptr, i_size);
	}

	void MemoryChunk::Initialize(void* i_ptr, const size_t i_size)
	{
		DEBUG_ASSERT(i_ptr);
		DEBUG_ASSERT(i_size > 0);

		_head = i_ptr;
		_current = i_ptr;
		_size = i_size;
		_end = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(_head) + i_size);
		is_alive = true;

		static_cast<Block*>(_head)->exist = NULL;
		static_cast<Block*>(_head)->size = i_size - sizeof(Block);

		return;
	}

	void MemoryChunk::Finalize()
	{
#ifdef ENGINE_PLATFORM_WINDOWS
		if (is_self_allcoate)
		{
			HeapFree(GetProcessHeap(), 0, _head);
		}
#else
		ENGINE_ASSERT(false);
#endif // ENGINE_PLATFORM_WINDOWS

		_head = nullptr;
		_current = nullptr;
		_end = nullptr;
		_size = 0;
		is_alive = false;
		is_self_allcoate = false;
	}

	void* MemoryChunk::Allocate(const size_t i_size)
	{
		DEBUG_ASSERT(i_size > 0);

		FindSpaceAndInsertblock_(i_size);

		return SplitToTwoBlocks_(i_size);
	}

	void* MemoryChunk::Reallocate(void* i_ptr, const size_t i_size)
	{
		DEBUG_ASSERT(i_ptr);
		DEBUG_ASSERT(i_size > 0);

		FindSpaceAndInsertblock_(i_size);

		void* return_address = SplitToTwoBlocks_(i_size);

		memcpy(return_address, i_ptr, i_size);

		Free(i_ptr);

		return return_address;
	}

	bool MemoryChunk::Free(void* i_ptr)
	{
		DEBUG_ASSERT(i_ptr);

		void* freeing = reinterpret_cast<void*>(reinterpret_cast<size_t>(i_ptr) - sizeof(Block));
		Block* freeing_block = static_cast<Block*>(freeing);

		DEBUG_ASSERT(freeing_block->exist);

		freeing_block->exist = false;
		return true;
	}

	void MemoryChunk::Collect()
	{

		void* current_collecting = _head;
		Block* current_collecting_block = static_cast<Block*>(current_collecting);
		void* next_collecting = reinterpret_cast<void*>(reinterpret_cast<size_t>(current_collecting) + current_collecting_block->size + sizeof(Block));
		Block* next_collecting_block = static_cast<Block*>(next_collecting);

		do
		{
			HEAP_ACCESS_VIOLATION_CHECK(current_collecting_block);
			HEAP_ACCESS_VIOLATION_CHECK(next_collecting_block);

			if (current_collecting_block->exist == false && next_collecting_block->exist == false)
			{
				current_collecting_block->size += (next_collecting_block->size + sizeof(Block));
				next_collecting = reinterpret_cast<void*>(reinterpret_cast<size_t>(next_collecting) + next_collecting_block->size + sizeof(Block));
				next_collecting_block = static_cast<Block*>(next_collecting);
			}
			else if (current_collecting_block->exist == true && next_collecting_block->exist == false)
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
		} while
			(reinterpret_cast<size_t>(next_collecting) + next_collecting_block->size + sizeof(Block) <= reinterpret_cast<size_t>(_end));

		return;
	}

	void MemoryChunk::FindSpaceAndInsertblock_(const size_t i_size)
	{
		bool need_to_collect = false;

		Block* current_block = static_cast<Block*>(_current);

		auto FindSpaceAndInsertBlock = [&](auto IfCannotFindSpace)
		{
			while (!(current_block->exist == false && current_block->size >= i_size + sizeof(Block)))
			{
				HEAP_ACCESS_VIOLATION_CHECK(current_block);

				_current = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + current_block->size + sizeof(Block));
				current_block = static_cast<Block*>(_current);
				if (reinterpret_cast<size_t>(_current) + sizeof(Block) >= reinterpret_cast<size_t>(_end))
				{
					IfCannotFindSpace();
					break;
				}
			}
		};

		FindSpaceAndInsertBlock([&]()
								{
									DEBUG_PRINT("Start collecting the heap since there is not enought memory to allocate");
									need_to_collect = true;
									return;
								});


		if (need_to_collect)
		{
			Collect();

			_current = _head;
			current_block = static_cast<Block*>(_current);

			FindSpaceAndInsertBlock([&]()
									{
										ENGINE_ASSERT_WITHMESSAGE(false, "There is not enough memory to allocate");
									});
		}
	}

	void* MemoryChunk::SplitToTwoBlocks_(const size_t i_size)
	{
		Block* current_block = static_cast<Block*>(_current);

		HEAP_ACCESS_VIOLATION_CHECK(current_block);

		size_t available_space = current_block->size;

		current_block->exist = true;
		current_block->size = i_size;
		void* return_address = reinterpret_cast<void*>(reinterpret_cast<size_t>(_current) + sizeof(Block));

		void* next = reinterpret_cast<void*> (reinterpret_cast<size_t>(_current) + sizeof(Block) + current_block->size);

		Block* next_block = static_cast<Block*>(next);
		next_block->exist = false;
		next_block->size = available_space - (i_size + sizeof(Block));

		HEAP_ACCESS_VIOLATION_CHECK(next_block);

		_current = next;

		//DEBUG_PRINT("The _current address is now at %zx", reinterpret_cast<size_t>(_current));
		//DEBUG_PRINT("The _current empty space now at %zu", reinterpret_cast<size_t>(_end) - reinterpret_cast<size_t>(_current));

		return return_address;
	}
}