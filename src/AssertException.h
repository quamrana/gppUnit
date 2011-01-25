#ifndef ASSERTEXCEPTION_H_0590596A_D2AC_43B8_8977_043E857A58EB
#define ASSERTEXCEPTION_H_0590596A_D2AC_43B8_8977_043E857A58EB

#include <stdexcept>

namespace gppUnit{
	class AssertException: public std::runtime_error{
	public:
		AssertException():runtime_error("Stack unwind due to Assert Exception"){}
	};

	extern AssertException assertException;
}

#endif // ASSERTEXCEPTION_H_0590596A_D2AC_43B8_8977_043E857A58EB
