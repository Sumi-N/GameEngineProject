#pragma once
#include "Define.h"

extern void* _head;
extern void* _current;
extern void* _end;
extern size_t _size;

class HeapManager
{
public:
#ifdef _DEBUG
	typedef struct Block
	{
		//Guard banding
		unsigned char headguardbanding;		
		bool exist;
		size_t size;
		//Guard banding
		unsigned char tailguardbanding;
	} Block;
#else
	typedef struct Block
	{
		bool exist;
		size_t size;
	} Block;
#endif 

public:
	HeapManager();
	~HeapManager();

	void* Initialize(void*, size_t);
	void  Finalize();
	void* Alloc(size_t);
	void* Realloc(void*, size_t);
	bool  Free(void*);
	void  Collect();

	bool IsHeapAlive();

private:
	bool is_heap_alive = false;

#ifdef _DEBUG
	void AccessViolationCheck(const Block*);
#endif
};

