#include <iostream>

int main(int , char* [])
{
	std::cout << "Hello, World!" << std::endl;
#ifdef WIN32
	std::cout << "Press return...";
	std::cin.get();
#endif
	return 0;
}

