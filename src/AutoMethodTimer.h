#ifndef AUTOMETHODTIMER_H_19665F04_D3A9_47EC_B3D7_AE5853DE44D9
#define AUTOMETHODTIMER_H_19665F04_D3A9_47EC_B3D7_AE5853DE44D9

#include "MethodCaller.h"

namespace gppUnit{
	class TimeReport;

	template<typename AUTO>
	class AutoMethodTimer: public gppUnit::MethodTimer{
		void timeMethod(gppUnit::MethodCaller& caller, gppUnit::TimeReport& report){
			AUTO timer(report);
			caller.forward();
		}
	};
}

#endif // AUTOMETHODTIMER_H_19665F04_D3A9_47EC_B3D7_AE5853DE44D9
