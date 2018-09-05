#include "NameGenerator.h"



NameGenerator::NameGenerator()
{
}


NameGenerator::~NameGenerator()
{
}

void NameGenerator::returnName(char* p, const int length) {
	static const char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < length ; i++)
	{
		p[i] = characters[rand() % (sizeof(characters) - 1)];
		p[length] = 0;
	}
}