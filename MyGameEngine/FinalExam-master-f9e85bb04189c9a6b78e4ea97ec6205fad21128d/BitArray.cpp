#include "FixedSizeAllocator.h"
#include <intrin.h>
#include <stdio.h>

void FixedSizeAllocator::BitArray::ClearAll() {
	for (int i = 0; i < DESCRIPTOR_SIZE; i++) {
		bytes[i] &= 0x00;
	}
}

void FixedSizeAllocator::BitArray::SetAll() {
	for (int i = 0; i < DESCRIPTOR_SIZE; i++) {
		bytes[i] |= 0xff;
	}
}

bool FixedSizeAllocator::BitArray::AreAllClear() const {
	return true;
}

bool FixedSizeAllocator::BitArray::AreAllSet() const {
	for (int i = 0; i < DESCRIPTOR_SIZE; i++) {
		if (bytes[i] == 0xff)
			return true;
	}
	return false;
}

bool FixedSizeAllocator::BitArray::IsBitSet(size_t i_size) const {
	return true;
}

bool FixedSizeAllocator::BitArray::IsBitClear(size_t i_size) const
{
	return true;
}

void FixedSizeAllocator::BitArray::SetBit(size_t i_size) {
	size_t index1 = i_size / UNIT_SIZE;
	size_t index2 = i_size % UNIT_SIZE;
	bytes[index1] |= 0x01 << index2;
}

void FixedSizeAllocator::BitArray::ClearBit(size_t i_size) {
	size_t index1 = i_size / UNIT_SIZE;
	size_t index2 = i_size % UNIT_SIZE;
	bytes[index1] ^= 0x01 << index2;
}

size_t FixedSizeAllocator::BitArray::GetFirstClearBit() const {
	int index = 0;
	while ((bytes[index] == 0xff) && (index < DESCRIPTOR_SIZE)) {
		index++;
	}
	unsigned long clearbit;
	if (_BitScanForward(&clearbit, ~bytes[index])) {
		return clearbit + index * UNIT_SIZE;
	}
	else {
		return INVALID;
	}
}

size_t FixedSizeAllocator::BitArray::GetFirstSetBit() const {
	int index = 0;
	while ((bytes[index] == 0x00) || (index < DESCRIPTOR_SIZE))
		index++;
	unsigned long setbit;
	if (_BitScanForward(&setbit, bytes[index])) {
		return setbit + index * UNIT_SIZE;
	}
	else {
		return INVALID;
	}
}

bool FixedSizeAllocator::BitArray::operator[](size_t i_index) const {
	return bytes[DESCRIPTOR_SIZE - i_index - 1];
}