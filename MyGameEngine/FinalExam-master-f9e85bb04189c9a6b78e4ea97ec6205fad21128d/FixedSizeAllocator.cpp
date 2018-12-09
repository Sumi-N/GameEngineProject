#include "FixedSizeAllocator.h"

#include <Windows.h>

void * FixedSizeAllocator::initialize(void * i_ptr, size_t i_size, unsigned int blocks)
{	
	begin = i_ptr;
	size = i_size;
	descriptor.ClearAll();
	return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(i_ptr) + i_size * blocks + sizeof(BitArray));
}

void * FixedSizeAllocator::alloc()
{
	size_t index = descriptor.GetFirstClearBit();
	if (index != INVALID) {
		descriptor.SetBit(index);
		return reinterpret_cast<void *>(reinterpret_cast<size_t>(begin) + size * index);
	}
	else {
		return nullptr;
	}
}

bool FixedSizeAllocator::free(void * i_ptr)
{
	if (i_ptr == nullptr) {
		return false;
	}
	size_t index = (reinterpret_cast<uintptr_t>(i_ptr) - reinterpret_cast<uintptr_t>(begin)) / size;
	descriptor.ClearBit(index);
	return true;
}
