#include "AutoMain.h"

#include <iostream>

int main(int , char* []) {
	bool result = gppUnit::AutoMain();
#ifdef WIN32
	std::cout << "Press return...";
	std::cin.get();
#endif
	return !result;
}

