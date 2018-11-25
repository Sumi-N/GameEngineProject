#pragma once
#include "Object2D.h"

class ObjectController
{
public:
	ObjectController(Object2D obj);
	~ObjectController();

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
	
	Object2D object;
	virtual bool moveTowardObject(Object2D & target);
	virtual bool moveByOrder(const char order);
private:

};

