#include "StaticLibTest.h"
#include "Object2D.h"
#include<iostream>
#include "List.h"
#include "CollisionDetection.h"

int main() {

	/*
	List<char> hoge;
	hoge.add('a');
	hoge.add('2');
	hoge.add('b');
	hoge.add('s');
	List<int> foo;
	foo.add(3);
	foo.add(4);
	foo.add(5);

	std::cout << &hoge << std::endl;
	std::cout << &foo << std::endl;

	List<char>::Iterator it;
	it = hoge.begin();
	while (it != hoge.end()) {
		std::cout << *it << std::endl;
		it++;
	}

	hoge.~List();

	List<int>::Iterator at;
	at = foo.begin();
	while (at != foo.end()) {
		std::cout << *at << std::endl;
		at++;
	}
	*/

	Object2D a;
	Object2D b;
	Object2D c;
	
	std::cout << "hello we start throwing to list" << std::endl;
	List<Object2D> baa;
	baa.add(a);
	baa.add(b);
	baa.add(c);
	
	while (1) {

	}
}