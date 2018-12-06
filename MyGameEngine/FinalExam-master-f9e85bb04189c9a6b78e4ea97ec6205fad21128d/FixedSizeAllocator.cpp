#include "FixedSizeAllocator.h"

#include <Windows.h>



FixedSizeAllocator::FixedSizeAllocator()
{

}

FixedSizeAllocator::~FixedSizeAllocator()
{
}

void * FixedSizeAllocator::initialize(void * i_ptr, size_t i_size, unsigned int blocks)
{	
	return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(i_ptr) + i_size * blocks);
}

void * FixedSizeAllocator::alloc()
{
	return nullptr;
}

void FixedSizeAllocator::free(void * i_ptr)
{
}
