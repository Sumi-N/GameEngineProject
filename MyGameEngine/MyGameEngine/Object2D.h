#pragma once
#include "Vector2D.h"
#include "HeapManager.h"
#include "DebugLog.h"
#include <assert.h>

class Object2D
{
public:
	char *headofname;
	char *name;
	int namelength;
	Vector2D<int, int> pos;

	Object2D();
	~Object2D();
	Object2D(const Object2D & obj);

	Object2D & operator=(const Object2D & obj);

	void * operator new(size_t) = delete;

	void * operator new(size_t i_size, HeapManager * pHeap) {
		void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHeap->_alloc(i_size, 4)) + sizeof(Using));
		assert(pHeap->_alloc(i_size, 4));
		return rtnp;
	}

	void * operator new[](size_t i_size, HeapManager * pHeap) {
		void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHeap->_alloc(i_size, 4)) + sizeof(Using));
		assert(pHeap->_alloc(i_size, 4));
		return rtnp;
	}

	void operator delete(void * iptr) {
		void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(iptr) - sizeof(Using));
		HeapManager * pHeap;
		pHeap = static_cast<HeapManager *>(iptr);
		pHeap->_free(rtnp);
		return;
	}

	void operator delete(void * iptr, HeapManager * pHeap) {
		void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(iptr) - sizeof(Using));
		pHeap->_free(rtnp);
		return;
	}

	void operator delete[](void * iptr, HeapManager * pHeap) {
		void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(iptr) - sizeof(Using));
		pHeap->_free(rtnp);
		return;
	}

	virtual void showPosition();
	virtual void showName();
	virtual Vector2D<int, int> getPosition();
	virtual void setPosition(Vector2D<int, int> pos);
	void randomName(int);
};

