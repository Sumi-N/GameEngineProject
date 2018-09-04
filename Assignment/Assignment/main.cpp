#include <iostream>
#include "NameGenerator.h"

int main() {

	int mn;
	char *p;
	char str[256];
	p = str;

	std::cout << "choose the number of monster" << std::endl;
	std::cin >> mn;
	std::cout << "the number of monster pops up : " << mn << std::endl;
	std::cout << "type your player name" << std::endl;
	std::cin >> str;
	std::cout << "your name is " << str << std::endl;

	while (true) {
	}
	return 0;
}
