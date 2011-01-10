#ifndef ASSERTEXCEPTION_H_01669C70_2784_4AAB_816A_BE5924C251F4
#define ASSERTEXCEPTION_H_01669C70_2784_4AAB_816A_BE5924C251F4

#include <stdexcept>

namespace Prototype1{
	class AssertException: public std::runtime_error{
	public:
		AssertException():runtime_error("Stack unwind due to Assert Exception"){}
	};

	extern AssertException assertException;
}

#endif // ASSERTEXCEPTION_H_01669C70_2784_4AAB_816A_BE5924C251F4
