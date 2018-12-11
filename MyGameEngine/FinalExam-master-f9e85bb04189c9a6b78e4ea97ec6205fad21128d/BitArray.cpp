#include "FixedSizeAllocator.h"
#include <intrin.h>
#include <stdio.h>

void FixedSizeAllocator::BitArray::ClearAll() {
	for (int index = 0; index < DESCRIPTOR_SIZE; index++) {
		_bytes[index] &= 0x00;
	}
}

void FixedSizeAllocator::BitArray::SetAll() {
	for (int index = 0; index < DESCRIPTOR_SIZE; index++) {
		_bytes[index] |= 0xff;
	}
}

void FixedSizeAllocator::BitArray::SetBit(size_t i_size) {
	size_t index = i_size / UNIT_SIZE_BITS;
	size_t offset = i_size % UNIT_SIZE_BITS;
	_bytes[index] |= 0x01 << offset;
}

void FixedSizeAllocator::BitArray::ClearBit(size_t i_size) {
	size_t index = i_size / UNIT_SIZE_BITS;
	size_t offset = i_size % UNIT_SIZE_BITS;
	_bytes[index] ^= 0x01 << offset;
}

size_t FixedSizeAllocator::BitArray::GetFirstClearBit() const {
	int index = 0;
	while (_bytes[index] == 0xff) {
		index++;
		if (index >= DESCRIPTOR_SIZE) {
			return INVALID;
		}
	}
	unsigned long clearbit;
	_BitScanForward(&clearbit, ~_bytes[index]);
	return clearbit + index * UNIT_SIZE_BITS;
	
}

size_t FixedSizeAllocator::BitArray::GetFirstSetBit() const {
	int index = 0;
	while (_bytes[index] == 0x00) {
		index++;
		if (index >= DESCRIPTOR_SIZE) {
			return INVALID;
		}
	}
	unsigned long setbit;
	_BitScanForward(&setbit, _bytes[index]);
	return setbit + index * UNIT_SIZE_BITS;
}
