#include "..\HiResTimer.h"

#include <time.h>
#include <iostream>

namespace Prototype1{
	namespace Internal{
		static long scale_long=1000000;
		static double scale_double=1000000.0;
	}
	time_interval getTime(){
		time_interval result;
		struct timeval ts;
   		gettimeofday(&ts,0);
   		result=ts.tv_usec+(ts.tv_sec*Internal::scale_long);
   		// std::cout << ts.tv_usec << std::endl;
   		return result;
	}
	double timeDifference(time_interval first, time_interval second){
		return double(second-first)/Internal::scale_double;
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
}
