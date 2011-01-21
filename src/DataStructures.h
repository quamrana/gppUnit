#ifndef DATASTRUCTURES_H_4D95AE2F_F05B_430C_A724_4242350F4A87
#define DATASTRUCTURES_H_4D95AE2F_F05B_430C_A724_4242350F4A87

#include <string>

namespace gppUnit{
	struct TestResult;

	struct MethodData{
		std::string title;
		size_t results;
		bool goodReport;
		double reportedTime;

		void accrueResult(const TestResult& result);
		void checkForExceptions(bool noExceptions){
			goodReport&=noExceptions;
		}
		explicit MethodData(const std::string& name):title(name),
			results(0),
			goodReport(true),
			reportedTime(0)
		{}
	};

	struct ClassData{
		std::string title;
		size_t results;
		double reportedTime;
		explicit ClassData(const std::string title):title(title),
			results(0),
			reportedTime(-1)
		{}
	};
}
#endif // DATASTRUCTURES_H_4D95AE2F_F05B_430C_A724_4242350F4A87
