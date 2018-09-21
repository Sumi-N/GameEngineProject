#pragma once
#include "Vector2D.h"
#include "List.h"

class Object2D
{
public:
	List<char> name;
	Vector2D<int, int> pos;
	Object2D();
	~Object2D();
	Object2D(Object2D &obj);
	bool operator==(const Object2D &);

	void showPosition();
	void showName();

	void randomName(int);
private:
};

