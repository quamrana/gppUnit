/*
Copyright (c) 2011 Andrew Wall

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef TESTCASEMETHODCALLER_H_247F51F5_D46D_4DD6_B084_72BCEFCCFE7C
#define TESTCASEMETHODCALLER_H_247F51F5_D46D_4DD6_B084_72BCEFCCFE7C

#include "MethodCaller.h"
#include "MethodNames.h"
#include "TestCase.h"

namespace gppUnit {
	class TestCaseMethodCaller;
	class Runner {
	protected:
		virtual ~Runner() {}
	public:
		virtual bool run(TestCaseMethodCaller*) = 0;
	};

	class TestCaseMethodCaller: public MethodCaller {
		const char* name;
	protected:
		PrototypeTestCase& testcase;
		Runner& runner;
	public:
		TestCaseMethodCaller(PrototypeTestCase& testcase, Runner& runner, const char* name): name(name), testcase(testcase), runner(runner) {}
		const char* methodName(void) const { return name; }
		void setReport(ReportResult* report) { testcase.setReport(report); }
		bool operator()() { return runner.run(this); }
	};
	class SetupCaller: public TestCaseMethodCaller {
		void forward() { testcase.setup(); }
	public:
		SetupCaller(PrototypeTestCase& fwd, Runner& runner): TestCaseMethodCaller(fwd, runner, setupMethodName()) {}
	};
	class TestCaller: public TestCaseMethodCaller {
		void forward() { testcase.test(); }
	public:
		TestCaller(PrototypeTestCase& fwd, Runner& runner): TestCaseMethodCaller(fwd, runner, testMethodName()) {}
	};
	class TeardownCaller: public TestCaseMethodCaller {
		void forward() { testcase.teardown(); }
	public:
		TeardownCaller(PrototypeTestCase& fwd, Runner& runner): TestCaseMethodCaller(fwd, runner, teardownMethodName()) {}
	};
}

#endif // TESTCASEMETHODCALLER_H_247F51F5_D46D_4DD6_B084_72BCEFCCFE7C
