#include "MethodTimer.h"
#include "TimeReport.h"
#include "MethodCaller.h"
#include "AutoMethodTimer.h"

#include <windows.h>

namespace{
	typedef long long time_interval;

	struct GetFrequency{
		LARGE_INTEGER freq;
		GetFrequency(){
			QueryPerformanceFrequency(&freq);
		}
	}gf;

	// Returns implementation dependent time index
	time_interval getTime(){
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);
		return time.QuadPart;
	}
	// Returns difference between intervals in seconds
	double timeDifference(time_interval first, time_interval second){
		second-=first;
		return double(second)/gf.freq.QuadPart;
	}

	class AutoTimer{
		gppUnit::TimeReport& report;
		time_interval time;
		AutoTimer& operator=(const AutoTimer&);
	public:
		explicit AutoTimer(gppUnit::TimeReport& report):report(report),
			time(getTime())
		{}
		~AutoTimer(){
			report.reportTime(timeDifference(time,getTime()));
		}
	};

	gppUnit::AutoMethodTimer<AutoTimer> timer;
}

namespace gppUnit{
	MethodTimer* MethodTimer::getTimer(){
		return &timer;
	}
}
