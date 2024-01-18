#include "MemorySystem.h"

namespace Tempest
{
	namespace MemorySystem
	{
		static MemoryChunk memory_chunk;

		void Initialize()
		{
			memory_chunk.Initialize(2ll * 1024ll * 1024ll * 1024ll);
		}
		void Finalize()
		{
			memory_chunk.Finalize();
		}

		void* Allocate(size_t i_size)
		{
			return memory_chunk.Allocate(i_size);
		}

		void* Reallocate(void* i_ptr, size_t i_size)
		{
			return memory_chunk.Reallocate(i_ptr, i_size);
		}

		void Free(void* i_ptr)
		{
			memory_chunk.Free(i_ptr);
		}
	}
}