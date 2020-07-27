#pragma once
#include "Define.h"

template<class T>
class ObjectFactory
{
public:
	static T* Create()
	{
		T* object = new T();
		return object;
	}

	static OwningPointer<T> CreateOwningPointer()
	{
		T* object = new T();
		OwningPointer<T> pointer;
		pointer = object;
		return pointer;
	}
};