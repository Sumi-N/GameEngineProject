#include "MessageContainer.h"

void MessageContainer::Create()
{
	pcontainer[0] = new char[container_size];
	pcontainer[1] = new char[container_size];
}

void MessageContainer::Swap()
{
	std::swap(pcontainer[0], pcontainer[1]);
}
