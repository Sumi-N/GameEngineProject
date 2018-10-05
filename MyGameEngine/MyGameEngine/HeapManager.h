#pragma once
#include "List.h";

static HeapManager * _head;		//head pointer
static HeapManager * _current; //current pointer
static size_t _size;	//heap size
static unsigned int _desnum; //descriptors' number

typedef struct Using {
	bool exit;
	size_t size;
} Using;

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

private:
};

