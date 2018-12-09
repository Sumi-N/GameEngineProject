#pragma once
#include <stdint.h>
#define DESCRIPTOR_SIZE 25
#define UNIT_SIZE 8
#define INVALID 200

class FixedSizeAllocator
{
	class BitArray {
		public:
			uint8_t bytes[DESCRIPTOR_SIZE];
			void ClearAll(void);
			void SetAll(void);

			bool AreAllClear(void) const;
			bool AreAllSet(void) const;

			bool IsBitSet(size_t) const;
			bool IsBitClear(size_t) const;

			void SetBit(size_t);
			void ClearBit(size_t);

			size_t GetFirstClearBit(void) const;
			size_t GetFirstSetBit(void) const;

			bool operator[](size_t i_index) const;
	};

public:

	void * begin;
	size_t size;
	BitArray descriptor;

	void * initialize(void * i_ptr, size_t i_size, unsigned int blocks);

	void * alloc();
	bool free(void * i_ptr);
};

