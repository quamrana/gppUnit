#ifndef HIRESTIMER_H_A8E359BC_36D8_40F5_9BF4_31B97F8AD45B
#define HIRESTIMER_H_A8E359BC_36D8_40F5_9BF4_31B97F8AD45B

namespace Prototype1{
	typedef long long time_interval;

	// Returns implementation dependent time index
	time_interval getTime();
	// Returns difference between intervals in seconds
	// Resolution is implementation dependant
	double timeDifference(time_interval first, time_interval second);
}

#endif // HIRESTIMER_H_A8E359BC_36D8_40F5_9BF4_31B97F8AD45B
