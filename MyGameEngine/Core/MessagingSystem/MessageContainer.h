#pragma once
#include "Define.h"

class MessageContainer
{
public:
	MessageContainer() : container_size(0){ }

	void Create();
	void Load();
	void Unload();
	void Swap();
	void CleanUp();

private:
	size_t container_size;

	void* pcontainer[2];
};

