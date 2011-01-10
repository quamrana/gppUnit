#ifndef AUTOTIMER_H_356972A0_FAF1_4FEA_9B51_2C8810681B48
#define AUTOTIMER_H_356972A0_FAF1_4FEA_9B51_2C8810681B48

#include "HiResTimer.h"

namespace Prototype1{
	class TimeReport;

	class AutoTimer{
		TimeReport& report;
		time_interval time;
	public:
		explicit AutoTimer(TimeReport& report):report(report),
			time(getTime())
		{}
		~AutoTimer();
	};
}

#endif // AUTOTIMER_H_356972A0_FAF1_4FEA_9B51_2C8810681B48
