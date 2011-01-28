#include "src\MethodTimer.h"
#include "src\AutoMethodTimer.h"
#include "src\TimeReport.h"

#include "TestUtilities.h"

#include <sstream>

namespace TestAutoMethodTimer{
	using gppUnit::equals;

	class Test: public Auto::TestCase, gppUnit::MethodCaller, gppUnit::TimeReport{
		gppUnit::AutoMethodTimer<Utilities::MockAuto<0> > mockauto;
		gppUnit::MethodTimer* caller;
		std::stringstream strm;

		virtual void forward(){ 
			strm << "fwd.";
		}
		virtual void reportTime(double /* run_time */){
			strm << "time.";
		}

		void givenAutoMethodTimer(){
			caller=&mockauto;
		}
		void whenCalled(){
			caller->timeMethod(*this,*this);
		}
		void thenMethodCalledBeforeTimeReported(){
			confirm.that("fwd.time.",equals(strm),"forward before time");
		}
		void test(){
			givenAutoMethodTimer();
			whenCalled();
			thenMethodCalledBeforeTimeReported();
		}
	}GPPUNIT_INSTANCE;
}
