#include "MethodTimer.h"
#include "TimeReport.h"
#include "AutoMethodTimer.h"

// #include <iostream>
#include <time.h>


namespace {
	typedef long long time_interval;

	namespace Internal {
		static long scale_long = 1000000;
		static double scale_double = scale_long; //1000000.0;
	}
	time_interval getTime() {
		time_interval result;
		struct timeval ts;
		gettimeofday(&ts, 0);
		result = ts.tv_sec;
		result *= Internal::scale_long;
		result += ts.tv_usec;
		// std::cout << result << "u " << ts.tv_sec << "s " << ts.tv_usec << 'u' << std::endl;
		return result;
	}
	double timeDifference(time_interval first, time_interval second) {
		// double result=double(second - first) / Internal::scale_double;
		// std::cout << result << "s" << std::endl;
		// return result;
		return double(second - first) / Internal::scale_double;
	}

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
