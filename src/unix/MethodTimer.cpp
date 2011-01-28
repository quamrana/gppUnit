#include "MethodTimer.h"
#include "TimeReport.h"
#include "AutoMethodTimer.h"

#include <time.h>

namespace {
	typedef long long time_interval;

	namespace Internal {
		static long scale_long = 1000000;
		static double scale_double = 1000000.0;
	}
	time_interval getTime() {
		time_interval result;
		struct timeval ts;
		gettimeofday(&ts, 0);
		result = ts.tv_usec + (ts.tv_sec * Internal::scale_long);
		// std::cout << ts.tv_usec << std::endl;
		return result;
	}
	double timeDifference(time_interval first, time_interval second) {
		return double(second - first) / Internal::scale_double;
	}
	/*
	namespace Temp{
		namespace Internal{
			static long scale_long=1000000000;
			static double scale_double=1000000000.0;
		}
		time_interval getTime(){
			time_interval result;
			struct timespec ts;
			clock_gettime(&ts,0);
			result=ts.tv_nsec+(ts.tv_sec*Internal::scale_long);
			// std::cout << ts.tv_usec << std::endl;
			return result;
		}
	}
	*/
	class AutoTimer {
		gppUnit::TimeReport& report;
		time_interval time;
		AutoTimer& operator=(const AutoTimer&);
	public:
		explicit AutoTimer(gppUnit::TimeReport& report): report(report),
			time(getTime())
		{}
		~AutoTimer() {
			report.reportTime(timeDifference(time, getTime()));
		}
	};

	gppUnit::AutoMethodTimer<AutoTimer> timer;
}

namespace gppUnit {
	MethodTimer& MethodTimer::getTimer() {
		return timer;
	}
}
