#pragma once
class HeapManager
{
public:

	static HeapManager * create(void *, size_t, unsigned int);
	void destroy();
	void * _alloc(size_t);
	void * _alloc(size_t, unsigned int);
	bool _free(void *);
	void collect();
	bool Contains(void *) const;
	bool IsAllocated(void *) const;
	size_t getLargestFreeBlock() const;
	size_t getTotalFreeMemory() const;
	void ShowFreeBlocks() const;
	void ShowOutstandingAllocatios();
};

