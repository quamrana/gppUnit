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
#include "AutoRunner.h"
#include "MethodTimer.h"
#include "MethodCaller.h"
#include "ProjectRunner.h"

namespace gppUnit {

	class NullTimer: public MethodTimer {
		virtual void timeMethod(MethodCaller& caller, TimeReport&) {
			caller.forward();
		}
	} nullTimer;

	AutoRunner::AutoRunner(): timer(&nullTimer) {}

	bool AutoRunner::run(const gppUnit::TestCaseList& cases) {
		ProjectRunner runner(title, notify, *timer, cases);
		return runner.run();
	}

	AutoRunner& AutoRunner::operator<<(std::string& name) {
		title = name;
		return *this;
	}
	AutoRunner& AutoRunner::operator<<(const char* name) {
		title = name;
		return *this;
	}

	// Add a notification
	AutoRunner& AutoRunner::operator<<(Notification& notifier) {
		notify.add(notifier);
		return *this;
	}

	// Set the timer to be used
	AutoRunner& AutoRunner::operator<<(MethodTimer& methodTimer) {
		timer = &methodTimer;
		return *this;

	}

}

