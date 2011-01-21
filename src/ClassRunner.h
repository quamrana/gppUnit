#ifndef CLASSRUNNER_H_8EB7AFBD_8A5D_4F51_B35B_FBE17B321070
#define CLASSRUNNER_H_8EB7AFBD_8A5D_4F51_B35B_FBE17B321070

#include "ClassDescription.h"
#include "TestCaseMethodCaller.h"
#include "MethodResult.h"

namespace gppUnit{
	class Notification;
	class MethodTimer;
	struct MethodData;

	struct ClassData{
		std::string title;
		size_t results;
		double reportedTime;
		explicit ClassData(const std::string title):title(title),results(0),reportedTime(-1){}
	};
	class ClassRunner: public ClassDescription, public Runner{
		Notification& notify;
		PrototypeTestCase& testcase;
		MethodTimer& timer;

		SetupCaller setup;
		TestCaller test;
		TeardownCaller teardown;

		std::vector<gppUnit::MethodData> methodData;
		ClassData classData;

		std::string name() const { return classData.title; }
		size_t methods() const { return methodData.size(); }
		size_t results() const { return classData.results; }
		double run_time() const { return classData.reportedTime; }

		MethodData callMethod(gppUnit::TestCaseMethodCaller& method);
		bool add(const MethodData& data);
		bool run(gppUnit::TestCaseMethodCaller* method);

		void runMethods();
		void calculateClassData();
	public:
		ClassRunner(gppUnit::Notification& notify, 
			gppUnit::PrototypeTestCase& testcase,
			gppUnit::MethodTimer& timer);
		~ClassRunner();
		void run(){
			runMethods();
			calculateClassData();
		}
		const ClassData& classSummary() const { return classData; }
	};
}
#endif // CLASSRUNNER_H_8EB7AFBD_8A5D_4F51_B35B_FBE17B321070
