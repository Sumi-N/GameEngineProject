#pragma once
#include <stdint.h>
#define DESCRIPTOR_SIZE 25
#define UNIT_SIZE sizeof(uint8_t)
#define UNIT_SIZE_BITS (sizeof(uint8_t)*8) // 1 byte = 8 bits
#define INVALID 255 // the invalid number which return back to calling function telling them the fixed size allocator is already full 

class FixedSizeAllocator
{
	class BitArray {
	public:
		void ClearAll(void);
		void SetAll(void);

		void SetBit(size_t);
		void ClearBit(size_t);

		size_t GetFirstClearBit(void) const;
		size_t GetFirstSetBit(void) const;
	private:
		uint8_t _bytes[DESCRIPTOR_SIZE];
	};

public:
	void * head;

	void * initialize(void * i_ptr, size_t i_size);
	void * alloc(void);
	bool free(void * i_ptr);

private:
	BitArray _descriptor;
	size_t _fixed_unit;
};

inline void * FixedSizeAllocator::initialize(void * i_ptr, size_t i_size)
{
	head = i_ptr;
	_fixed_unit = i_size;
	_descriptor.ClearAll();
	return reinterpret_cast<void*>(reinterpret_cast<size_t>(i_ptr) + _fixed_unit * DESCRIPTOR_SIZE * UNIT_SIZE);
}

inline void * FixedSizeAllocator::alloc()
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

inline bool FixedSizeAllocator::free(void * i_ptr)
{
	if (i_ptr == nullptr) {
		return false;
	}
	size_t index = (reinterpret_cast<size_t>(i_ptr) - reinterpret_cast<size_t>(head)) / _fixed_unit;
	_descriptor.ClearBit(index);
	return true;
}

