/*
Copyright (c) 2011 Andrew Wall

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
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
