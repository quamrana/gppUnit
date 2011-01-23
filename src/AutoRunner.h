#ifndef AUTORUNNER_H_ED89D4F6_3B20_4FC1_9808_929558CF9D98
#define AUTORUNNER_H_ED89D4F6_3B20_4FC1_9808_929558CF9D98

#include "CompositeNotification.h"
#include "TestCase.h"

namespace gppUnit {
	class MethodTimer;

	class AutoRunner {
		CompositeNotification notify;
		std::string title;
		MethodTimer* timer;

	public:
		AutoRunner();
		bool run(const TestCaseList& cases);

		// Set the title of project being run
		AutoRunner& operator<<(std::string& title);
		AutoRunner& operator<<(const char* title);

		// Add a notification
		AutoRunner& operator<<(Notification& notify);

		// Set the timer to be used
		AutoRunner& operator<<(MethodTimer& timer);
	};
}
#endif // AUTORUNNER_H_ED89D4F6_3B20_4FC1_9808_929558CF9D98
