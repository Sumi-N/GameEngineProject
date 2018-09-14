#include "StaticLibTest.h"
#include<iostream>
#include "List.h"

int main() {

	List<int> hoge;
	hoge.add(10);
	hoge.add(2);
	hoge.add(29);
	hoge.add(23);
	List<int> foo;
	foo.add(3);
	foo.add(4);
	foo.add(5);

	std::cout << &hoge << std::endl;
	std::cout << &foo << std::endl;

	List<int>::Iterator it;
	it = hoge.begin();
	while (it != hoge.end()) {
		std::cout << *it << std::endl;
		it++;
	}

	hoge.~List();

	it = foo.begin();
	while (it != foo.end()) {
		std::cout << *it << std::endl;
		it++;
	}
	
	while (1) {

	}
}