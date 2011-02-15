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
#include "src\AutoOptions.h"
#include "src\AutoRunner.h"
#include "src\StreamNotification.h"
#include "src\ProjectDescription.h"
#include "src\ClassDescription.h"
#include "src\MethodDescription.h"
#include "src\TestResult.h"
#include "src\SuccessLogger.h"

#include <iostream>
#include <sstream>

namespace {
	gppUnit::StreamNotification Notifier(std::cout);

	class TimeLogging: public gppUnit::Notification{
		std::stringstream out;
		//const gppUnit::ProjectDescription* proj;
		const gppUnit::ClassDescription* desc;
		const gppUnit::MethodDescription* method;


		//void StartProject(const gppUnit::ProjectDescription&desc){
		//			proj = &desc;
		//}
		void StartClass(const gppUnit::ClassDescription&desc){
					this->desc = &desc;
					out << desc.name() << std::endl;
		}
		void StartMethod(const gppUnit::MethodDescription&desc){
					method = &desc;
					out << " " << desc.name();
		}
		//void Result(const gppUnit::TestResult&);
		//void Exception(const std::string& /* what */);

		void EndMethod(){
			out << " " << method->run_time() << std::endl;
		}

		void EndProject(){
			std::cout << out.str();
		}
	}tlog;

	gppUnit::SuccessLogger success;
	gppUnit::FileLoggerNotification fln1("gppUnit.log",success);

	gppUnit::AllRunsLogger allRuns;
	gppUnit::FileLoggerNotification fln2("gppUnit-allruns.log",allRuns);
}

namespace gppUnit {
	void AutoOptions(AutoRunner& runner) {
		runner << "gppUnit 1.5" << Notifier << fln1 << fln2;

	}
}
