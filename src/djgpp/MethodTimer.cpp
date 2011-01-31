#include "MethodTimer.h"
#include "TimeReport.h"
#include "AutoMethodTimer.h"

// #include <iostream>
#include <time.h>

namespace {
	typedef long long time_interval;

	namespace Internal {
		static long scale_long = UCLOCKS_PER_SEC;
		static double scale_double = scale_long;
	}
	time_interval getTime() {
		return uclock();
	}
	double timeDifference(time_interval first, time_interval second) {
		time_interval diff = second - first;
		if(diff < 0) {
			diff += 65536L;
			// std::cout << "----------------" << std::endl;
		}
		double result = double(diff) / Internal::scale_double;
		// std::cout << result << "s" << std::endl;
		return result;
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
