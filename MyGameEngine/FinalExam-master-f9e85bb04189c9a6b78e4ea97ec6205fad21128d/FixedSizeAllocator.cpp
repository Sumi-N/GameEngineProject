#include "FixedSizeAllocator.h"

#include <Windows.h>

void * FixedSizeAllocator::initialize(void * i_ptr, size_t i_size)
{	
	head = i_ptr;
	_fixed_unit = i_size;
	_descriptor.ClearAll();
	return reinterpret_cast<void*>(reinterpret_cast<size_t>(i_ptr) + _fixed_unit * DESCRIPTOR_SIZE * UNIT_SIZE);
}

void * FixedSizeAllocator::alloc()
{
	size_t index = _descriptor.GetFirstClearBit();
	if (index != INVALID) {
		_descriptor.SetBit(index);
		return reinterpret_cast<void *>(reinterpret_cast<size_t>(head) + _fixed_unit * index);
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
	size_t index = (reinterpret_cast<size_t>(i_ptr) - reinterpret_cast<size_t>(head)) / _fixed_unit;
	_descriptor.ClearBit(index);
	return true;
}
