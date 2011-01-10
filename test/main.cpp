#include <iostream>

void DoAutoRun(const char* title);

int main(int , char* [])
{
	//std::cout << "Hello, World!" << std::endl;
	DoAutoRun("Test gppUnit1.5");
#ifdef WIN32
	std::cout << "Press return...";
	std::cin.get();
#endif
	return 0;
}

