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
};