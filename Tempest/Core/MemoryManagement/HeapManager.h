#pragma once

static void* _head;
static void* _current;
static void* _over;
static size_t _size;

class HeapManager
{
public:
#ifdef _DEBUG

	typedef struct Unit
	{
		//Guard banding
		unsigned char tailguardbanding;
		bool exit;
		size_t size;
		//Guard banding
		unsigned char headguardbanding;
	} Unit;
#else
	typedef struct Unit
	{
		bool exit;
		size_t size;
	} Unit;
#endif 

public:
	static void* initialize(void*, size_t);
	void* _alloc(size_t);
	bool _free(void*);
	void collect();
};

