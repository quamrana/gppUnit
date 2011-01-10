#include "..\HiResTimer.h"

#include <windows.h>

namespace Prototype1{
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
}
