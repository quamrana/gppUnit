#include "src\AutoOptions.h"
#include "src\AutoRunner.h"
#include "src\StreamNotification.h"
#include "src\ProjectDescription.h"
#include "src\ClassDescription.h"
#include "src\MethodDescription.h"
#include "src\TestResult.h"

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
}

namespace gppUnit {
	void AutoOptions(AutoRunner& runner) {
		runner << "gppUnit 1.5" << Notifier;

	}
}
