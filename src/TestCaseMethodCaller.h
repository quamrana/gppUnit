#ifndef TESTCASEMETHODCALLER_H_247F51F5_D46D_4DD6_B084_72BCEFCCFE7C
#define TESTCASEMETHODCALLER_H_247F51F5_D46D_4DD6_B084_72BCEFCCFE7C

#include "MethodCaller.h"
#include "MethodNames.h"
#include "TestCase.h"

namespace gppUnit{
	class TestCaseMethodCaller: public MethodCaller{
		const char* name;
	protected:
		PrototypeTestCase& testcase;
	public:
		TestCaseMethodCaller(PrototypeTestCase& testcase, const char* name):name(name),testcase(testcase){}
		const char* methodName(void) const { return name; }
		void setReport(ReportResult* report){ testcase.setReport(report); }
	};
	class SetupCaller: public TestCaseMethodCaller{
		void forward(){ testcase.setup(); }
	public:
		SetupCaller(PrototypeTestCase& fwd):TestCaseMethodCaller(fwd,setupMethodName()){}
	};
	class TestCaller: public TestCaseMethodCaller{
		void forward(){ testcase.test(); }
	public:
		TestCaller(PrototypeTestCase& fwd):TestCaseMethodCaller(fwd,testMethodName()){}
	};
	class TeardownCaller: public TestCaseMethodCaller{
		void forward(){ testcase.teardown(); }
	public:
		TeardownCaller(PrototypeTestCase& fwd):TestCaseMethodCaller(fwd,teardownMethodName()){}
	};
}

#endif // TESTCASEMETHODCALLER_H_247F51F5_D46D_4DD6_B084_72BCEFCCFE7C
