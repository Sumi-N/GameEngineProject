#pragma once
#include "Define.h"

static void* _head;
static void* _current;
static void* _end;
static size_t _size;

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
	static void* initialize(void*, size_t);
	void* alloc(size_t);
	void* realloc(void*, size_t);
	bool free(void*);
	void collect();	
};

