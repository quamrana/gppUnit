#include "src\MethodDescription.h"

#include "TestUtilities.h"

#include <stdexcept>

namespace TestExceptionCatching{
	class ThrowingTestCase: public Utilities::MockTestCase{
		void test(){ 
			throw std::runtime_error("throw");
		}
	};

	class Test: public Utilities::TestCaseCaller, gppUnit::Notification{
		ThrowingTestCase testcase;

		const gppUnit::MethodDescription* description;

		double run_time;

		void StartMethod(const gppUnit::MethodDescription& desc){
			description=&desc;
		}
		bool exceptionReported;
		virtual void Exception(const std::string& /* what */){
			exceptionReported=true;
		}
		void EndMethod(){
			if (description->name()=="test"){
				run_time=description->run_time();
			}
			description=0;
		}

		void givenTestCase(){
			add(testcase);
			givenNotification(this);
			exceptionReported=false;
			run_time=-1;
		}
		void thenExceptionReported(){
			confirm.isTrue(exceptionReported,"thenExceptionReported");
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
