#ifndef TESTCASEMETHODCALLER_H_247F51F5_D46D_4DD6_B084_72BCEFCCFE7C
#define TESTCASEMETHODCALLER_H_247F51F5_D46D_4DD6_B084_72BCEFCCFE7C

#include "MethodCaller.h"
#include "MethodNames.h"
#include "TestCase.h"

namespace gppUnit{
	class TestCaseMethodCaller;
	class Runner{
	protected:
		virtual ~Runner(){}
	public:
		virtual bool run(TestCaseMethodCaller*)=0;
	};

	class TestCaseMethodCaller: public MethodCaller{
		const char* name;
	protected:
		PrototypeTestCase& testcase;
		Runner& runner;
	public:
		TestCaseMethodCaller(PrototypeTestCase& testcase, Runner& runner, const char* name):name(name),testcase(testcase),runner(runner){}
		const char* methodName(void) const { return name; }
		void setReport(ReportResult* report){ testcase.setReport(report); }
		bool operator()(){ return runner.run(this); }
	};
	class SetupCaller: public TestCaseMethodCaller{
		void forward(){ testcase.setup(); }
	public:
		SetupCaller(PrototypeTestCase& fwd, Runner& runner):TestCaseMethodCaller(fwd,runner,setupMethodName()){}
	};
	class TestCaller: public TestCaseMethodCaller{
		void forward(){ testcase.test(); }
	public:
		TestCaller(PrototypeTestCase& fwd, Runner& runner):TestCaseMethodCaller(fwd,runner,testMethodName()){}
	};
	class TeardownCaller: public TestCaseMethodCaller{
		void forward(){ testcase.teardown(); }
	public:
		TeardownCaller(PrototypeTestCase& fwd, Runner& runner):TestCaseMethodCaller(fwd,runner,teardownMethodName()){}
	};
}

#endif // TESTCASEMETHODCALLER_H_247F51F5_D46D_4DD6_B084_72BCEFCCFE7C
