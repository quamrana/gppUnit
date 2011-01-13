#ifndef TESTCASEMETHODCALLER_H_247F51F5_D46D_4DD6_B084_72BCEFCCFE7C
#define TESTCASEMETHODCALLER_H_247F51F5_D46D_4DD6_B084_72BCEFCCFE7C

#include "MethodCaller.h"
#include "MethodNames.h"

namespace gppUnit{
	class TestCaseMethodCaller: public MethodCaller{
		const char* name;
	protected:
		TestCase& testcase;
	public:
		TestCaseMethodCaller(TestCase& testcase, const char* name):name(name),testcase(testcase){}
		const char* methodName(void) const { return name; }
	};
	class SetupCaller: public TestCaseMethodCaller{
		void forward(){ testcase.setup(); }
	public:
		SetupCaller(TestCase& fwd):TestCaseMethodCaller(fwd,setupMethodName()){}
	};
	class TestCaller: public TestCaseMethodCaller{
		void forward(){ testcase.test(); }
	public:
		TestCaller(TestCase& fwd):TestCaseMethodCaller(fwd,testMethodName()){}
	};
	class TeardownCaller: public TestCaseMethodCaller{
		void forward(){ testcase.teardown(); }
	public:
		TeardownCaller(TestCase& fwd):TestCaseMethodCaller(fwd,teardownMethodName()){}
	};
}

#endif // TESTCASEMETHODCALLER_H_247F51F5_D46D_4DD6_B084_72BCEFCCFE7C
