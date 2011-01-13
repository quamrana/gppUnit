#ifndef TESTCASEMETHODCALLERS_H_660CCF58_2191_4729_BA0E_3E5E0385655E
#define TESTCASEMETHODCALLERS_H_660CCF58_2191_4729_BA0E_3E5E0385655E

#include "TestCase.h"

namespace Prototype1{
	namespace Internal{
		class MethodCaller{
		protected:
			virtual ~MethodCaller(){}
		public:
			virtual void forward()=0;
		};

		class TestCaseMethodCaller: public MethodCaller{
			const char* name;
		protected:
			TestCase& testcase;
		public:
			TestCaseMethodCaller(TestCase& testcase,const char* name):name(name),testcase(testcase){}
			const char* methodName(void) const { return name; }
		};
		class SetupCaller: public TestCaseMethodCaller{
			void forward(){ testcase.setup(); }
		public:
			SetupCaller(TestCase& fwd):TestCaseMethodCaller(fwd,"setup"){}
		};
		class TestCaller: public TestCaseMethodCaller{
			void forward(){ testcase.test(); }
		public:
			TestCaller(TestCase& fwd):TestCaseMethodCaller(fwd,"test"){}
		};
		class TeardownCaller: public TestCaseMethodCaller{
			void forward(){ testcase.teardown(); }
		public:
			TeardownCaller(TestCase& fwd):TestCaseMethodCaller(fwd,"teardown"){}
		};
	}
}

#endif // TESTCASEMETHODCALLERS_H_660CCF58_2191_4729_BA0E_3E5E0385655E
