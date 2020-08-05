#pragma once
#include "Define.h"

template<class T>
class Entity
{
public:
	std::vector<OwningPointer<T>> list;

	OwningPointer<T> Register()
	{

	}

	void Boot()
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			(*it)->Boot();
		}
	}

	static OwningPointer<T> Create()
	{
		T* object = new T();
		OwningPointer<T> pointer;
		pointer = object;
		return pointer;
	}
};