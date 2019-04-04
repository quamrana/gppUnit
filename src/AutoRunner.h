/*
Copyright (c) 2011-2019 Andrew Wall

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
#ifndef AUTORUNNER_H_ED89D4F6_3B20_4FC1_9808_929558CF9D98
#define AUTORUNNER_H_ED89D4F6_3B20_4FC1_9808_929558CF9D98

#include "ProjectContext.h"
#include "TestCase.h"

namespace gppUnit {

	class AutoRunner {
		ProjectContext context;
		std::string title;

	public:
		explicit AutoRunner(const CommandLineOptions&);
		bool run(const TestCaseList& cases);

		// Set the title of project being run
		AutoRunner& operator<<(const std::string& title_);

		// Add a notification
		AutoRunner& operator<<(Notification& notify_);

		// Set the timer to be used
		AutoRunner& operator<<(MethodTimer& timer_);
	};
}
#endif // AUTORUNNER_H_ED89D4F6_3B20_4FC1_9808_929558CF9D98
