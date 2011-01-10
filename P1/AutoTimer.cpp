#include "AutoTimer.h"
#include "TimeReport.h"

namespace Prototype1{
	AutoTimer::~AutoTimer(){
		report.reportTime(timeDifference(time,getTime()));
	}
}