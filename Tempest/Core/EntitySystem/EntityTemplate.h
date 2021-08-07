#pragma once
#include "Define.h"

template<class T>
class Entity
{
public:
	Array<OwningPointer<T>> list;

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
};