#pragma once

static void * _head;
static void * _current;
static void * _over;
static size_t _size;

typedef struct Using {
	bool exit;
	size_t size;
} Using;

class NewHeapManager
{
public:
	static void * initialize(void *, size_t);
	void * _alloc(size_t);
	bool _free(void *);
	void collect();
};

