#pragma once
#include "MemoryChunk.h"

namespace Tempest
{
	namespace MemorySystem
	{
		void Initialize();
		void Finalize();
		void* Allocate(size_t i_size);
		void* Reallocate(void* i_ptr, size_t i_size);
		void  Free(void* i_ptr);
	}
}