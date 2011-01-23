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

