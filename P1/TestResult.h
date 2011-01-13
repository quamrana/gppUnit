#ifndef TESTRESULT_H_C4186DFF_F229_40D0_B450_5566CA43DB88
#define TESTRESULT_H_C4186DFF_F229_40D0_B450_5566CA43DB88

#include <string>
#include <vector>

namespace Prototype1{
	struct TestResult{
		bool result;
		std::string message;
		std::vector<std::string> description;
		TestResult(){}
	};
}

#endif // TESTRESULT_H_C4186DFF_F229_40D0_B450_5566CA43DB88
