#include "src\MethodTimer.h"
#include "src\MethodCaller.h"
#include "src\TimeReport.h"

#include "AutoRun.h"

#include <sstream>

namespace TestWin32MethodTimer{
	using gppUnit::greater_than;
	using gppUnit::equal_to;

	class Test: public Auto::TestCase, gppUnit::MethodCaller, gppUnit::TimeReport{

		gppUnit::MethodTimer* win32Timer;
		bool methodCalled;
		bool timeReported;
		double runtimeReport;

		std::stringstream strm;

		virtual void forward(){ 
			methodCalled=true; 
			strm << "fwd.";
		}
		virtual void reportTime(double run_time){
			timeReported=true;
			runtimeReport=run_time;
			strm << "time.";
		}
		void givenTimer(){
			win32Timer=&gppUnit::MethodTimer::getTimer();
			methodCalled=false;
			timeReported=false;
			runtimeReport=-1;
			strm.str("");
		}
		void whenCalled(){
			win32Timer->timeMethod(*this,*this);
		}
		void thenMethodCalled(){
			confirm.isTrue(methodCalled,"Forward should be called");
		}
		void thenTimeReported(){
			confirm.isTrue(timeReported,"Time should be reported");
		}
		void thenRuntimeIsReasonable(){
			confirm.that(runtimeReport,greater_than(0.5e-6),"Time should be not too small");
			confirm.that(runtimeReport,!greater_than(50e-6),"Time should be not too large");
		}
		void thenMethodCalledBeforeTimeReported(){
			confirm.that(strm.str(),equal_to("fwd.time."),"forward before time");
		}
		void test(){
			givenTimer();
			whenCalled();
			thenMethodCalled();
			thenTimeReported();
			thenRuntimeIsReasonable();
			thenMethodCalledBeforeTimeReported();
		}
	}GPPUNIT_INSTANCE;
}
