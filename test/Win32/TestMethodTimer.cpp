#include "AutoRun.h"

#include "src\MethodTimer.h"
#include "src\MethodCaller.h"
#include "src\TimeReport.h"

#include <sstream>

namespace TestWin32MethodTimer{
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
			win32Timer=gppUnit::MethodTimer::getTimer();
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
			bool notTooLarge=(runtimeReport<(50.0/1e6));
			bool notTooSmall=(runtimeReport>(0.5/1e6));
			confirm.isTrue(notTooLarge,"Time should be not too large");
			confirm.isTrue(notTooSmall,"Time should be not too small");
		}
		void thenMethodCalledBeforeTimeReported(){
			confirm.equals("fwd.time.",strm.str(),"forward before time");
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
