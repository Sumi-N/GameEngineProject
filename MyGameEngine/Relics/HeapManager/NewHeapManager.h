#pragma once

static void * _head;
static void * _current;
static void * _over;
static size_t _size;

#ifdef _DEBUG
	typedef struct Using {
		//Guardbanding
		unsigned char tailguardbanding;
		bool exit;
		size_t size;
		//Guard banding
		unsigned char headguardbanding;
	} Using;
#else
	typedef struct Using {
		bool exit;
		size_t size;
	} Using;
#endif 

class NewHeapManager
{
public:
	static void * initialize(void *, size_t);
	void * _alloc(size_t);
	bool _free(void *);
	void collect();
};

