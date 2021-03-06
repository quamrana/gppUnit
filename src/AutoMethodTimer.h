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
#ifndef AUTOMETHODTIMER_H_19665F04_D3A9_47EC_B3D7_AE5853DE44D9
#define AUTOMETHODTIMER_H_19665F04_D3A9_47EC_B3D7_AE5853DE44D9

#include "MethodTimer.h"
#include "MethodCaller.h"

namespace gppUnit {
	class TimeReport;

	template<typename AUTO>
	class AutoMethodTimer: public gppUnit::MethodTimer {
		void timeMethod(gppUnit::MethodCaller& caller, gppUnit::TimeReport& report) {
			AUTO timer(report);
			caller.forward();
		}
	};
}

#endif // AUTOMETHODTIMER_H_19665F04_D3A9_47EC_B3D7_AE5853DE44D9
