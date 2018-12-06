#pragma once
class FixedSizeAllocator
{
	class BitArray {
		public:
			void ClearAll(void);
			void SetAll(void);

			bool AreAllClear(void) const;
			bool AreAllSet(void) const;

			bool IsBitSet(size_t) const;
			bool IsBitClear(size_t) const;

			void SetBit(size_t);
			void ClearBit(size_t);

			bool GetFirstClearBit(size_t & o_bitNumber) const;
			bool GetFirstSetBit(size_t & o_bitNumber) const;

			bool operator[](size_t i_index) const;
	};

public:
	FixedSizeAllocator();
	~FixedSizeAllocator();

	void* begin;

	void * initialize(void * i_ptr, size_t i_size, unsigned int blocks);

	void * alloc();
	void free(void * i_ptr);
	
	BitArray descriptor;
};

