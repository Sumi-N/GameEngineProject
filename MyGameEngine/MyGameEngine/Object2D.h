#pragma once
#include "Vector2D.h"
#include "HeapManager.h"

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
	void * operator new(size_t i_size, HeapManager * pHeap) {
		void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHeap->_alloc(i_size, 4)) + sizeof(Using));
		return rtnp;
	}
	void operator delete(void * iptr) {
		void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(iptr) - sizeof(Using));
		//static_cast<Object2D *>(rtnp)->~Object2D;
		return;
	}

	virtual void showPosition();
	virtual void showName();
	virtual Vector2D<int, int> getPosition();
	virtual void setPosition(Vector2D<int, int> pos);
	void randomName(int);
};

