#pragma once
#include "Define.h"

namespace Tempest
{
	class MemoryChunk
	{
	private:
		typedef struct Block
		{
#ifdef _DEBUG
			unsigned char headguardbanding;
#endif
			bool exist;
			size_t size;
#ifdef _DEBUG
			unsigned char tailguardbanding;
#endif
		} Block;

	public:
		MemoryChunk() = default;
		~MemoryChunk() = default;

		void  Initialize(size_t i_size);
		void  Initialize(void* i_ptr, size_t i_size);
		void  Finalize();
		void* Allocate(size_t i_size);
		void* Reallocate(void* i_ptr, size_t i_size);
		bool  Free(void* i_ptr);
		void  Collect();

		bool  IsHeapAlive() const { return is_alive; }

	private:
		void  FindSpaceAndInsertblock_(size_t i_size);
		void* SplitToTwoBlocks_(size_t i_size);

	private:
		void* _head = nullptr;
		void* _current = nullptr;
		void* _end = nullptr;
		size_t _size = 0;

		bool is_alive = false;
		bool is_self_allcoate = false;
	};
}