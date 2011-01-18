#include "src\MethodDescription.h"

#include "TestUtilities.h"

#include <stdexcept>
#include <sstream>

namespace TestExceptionCatching{
	class RTEThrowingTestCase: public Utilities::MockTestCase{
		void test(){ 
			throw std::runtime_error("rte");
		}
	};
	class StringThrowingTestCase: public Utilities::MockTestCase{
		void test(){ 
			throw std::string("string");
		}
	};
	class CharStarThrowingTestCase: public Utilities::MockTestCase{
		void test(){ 
			throw "charstar";
		}
	};
	class IntStarThrowingTestCase: public Utilities::MockTestCase{
		void test(){ 
			throw 1;
		}
	};
	class SelfThrowingTestCase: public Utilities::MockTestCase{
		void test(){ 
			throw this;
		}
	};

	class Test: public Utilities::TestCaseCaller, gppUnit::Notification{
		RTEThrowingTestCase testcase1;
		StringThrowingTestCase testcase2;
		CharStarThrowingTestCase testcase3;
		IntStarThrowingTestCase testcase4;
		SelfThrowingTestCase testcase5;

		std::stringstream collect;

		const gppUnit::MethodDescription* description;

		double run_time;
		bool runtimeCaptured;

		void StartMethod(const gppUnit::MethodDescription& desc){
			description=&desc;
		}
		bool exceptionReported;
		virtual void Exception(const std::string& what){
			exceptionReported=true;
			collect << what << '.';
		}
		void EndMethod(){
			if (!runtimeCaptured){
				if (description->name()=="test"){
					run_time=description->run_time();
					runtimeCaptured=true;
				}
			}
			description=0;
		}

		void givenTestCase(){
			add(testcase1);
			add(testcase2);
			add(testcase3);
			add(testcase4);
			add(testcase5);
			givenNotification(this);
			exceptionReported=false;
			run_time=-1;
			runtimeCaptured=false;
		}
		void thenExceptionReported(){
			confirm.isTrue(exceptionReported,"thenExceptionReported");
			confirm.equals("rte.string.charstar.1.Unknown Exception.",collect.str(),"Various exceptions");
		}
		void thenTimeReported(){
			confirm.isTrue(0.1==run_time,"TestUtilities should supply a standard run_time");
		}
		void test(){
			givenTestCase();
			whenCalled();
			thenExceptionReported();
			thenTimeReported();
		}
	}GPPUNIT_INSTANCE;
}
