#include "src\MethodNames.h"
#include "src\TestCaseMethodCaller.h"
#include "src\MethodDescription.h"
#include "src\ReportResult.h"
#include "src\TestResult.h"
#include "src\TypeInformation.h"
#include "src\ClassDescription.h"
#include "src\MethodResult.h"
#include "src\ProjectDescription.h"

#include "TestUtilities.h"

#include <algorithm>
#include <functional>
#include <numeric>
#include <typeinfo>

namespace Utilities{

	template<typename T>
	struct Results{
		size_t operator()(size_t init, const T& description){
			return init+description.results;
		}
	};
	template<typename T>
	struct RunTime{
		double operator()(double init, const T& description){
			return init+description.reportedTime;
		}
	};

	struct ClassData{
		std::string title;
		size_t results;
		double reportedTime;
		explicit ClassData(const std::string title):title(title),results(0),reportedTime(-1){}
	};
	class ClassRunner: public gppUnit::ClassDescription, public gppUnit::Runner{
		gppUnit::Notification& notify;
		gppUnit::PrototypeTestCase& testcase;
		gppUnit::MethodTimer& timer;

		gppUnit::SetupCaller setup;
		gppUnit::TestCaller test;
		gppUnit::TeardownCaller teardown;

		std::vector<gppUnit::MethodData> methodData;
		ClassData classData;

		std::string name() const { return classData.title; }
		size_t methods() const { return methodData.size(); }
		size_t results() const { return classData.results; }
		double run_time() const { return classData.reportedTime; }

		gppUnit::MethodData callMethod(gppUnit::TestCaseMethodCaller& method){
			gppUnit::MethodResult desc(method,notify,timer);

			desc.protectMethod();

			return desc.methodSummary();
		}
		bool add(const gppUnit::MethodData& data){ methodData.push_back(data); return data.goodReport; }
		bool run(gppUnit::TestCaseMethodCaller* method){
			return add(callMethod(*method));
		}
		void runMethods(){
			if (setup())
			{
				test();
			}
			teardown();
		}
		void calculateClassData(){
			classData.results=std::accumulate(methodData.begin(),methodData.end(),long(),Results<gppUnit::MethodData>());
			classData.reportedTime=std::accumulate(methodData.begin(),methodData.end(),double(),RunTime<gppUnit::MethodData>());
		}
	public:
		ClassRunner(gppUnit::Notification& notify, 
			gppUnit::PrototypeTestCase& testcase,
			gppUnit::MethodTimer& timer):notify(notify),
			testcase(testcase),
			timer(timer),
			setup(testcase,*this),
			test(testcase,*this),
			teardown(testcase,*this),
			classData(gppUnit::demangleTypeName(typeid(testcase).name()))
		{
			notify.StartClass(*this);
		}
		~ClassRunner(){ notify.EndClass(); }
		void run(){
			runMethods();
			calculateClassData();
		}
		const ClassData& classSummary() const { return classData; }
	};

	class ProjectRunner: public gppUnit::ProjectDescription{
		gppUnit::Notification& notify;
		gppUnit::MethodTimer& timer;
		gppUnit::TestCaseList cases;

		std::vector<ClassData> classData;
		ClassData projectData;

		std::string name() const { return projectData.title; }
		size_t classes() const { return cases.size(); }
		size_t results() const { return projectData.results; }
		double run_time() const { return projectData.reportedTime; }

		void call(gppUnit::PrototypeTestCase* testcase){
			ClassRunner runner(notify,*testcase,timer);

			runner.run();

			classData.push_back(runner.classSummary());
		}
		void calculateProjectData(){
			projectData.results=std::accumulate(classData.begin(),classData.end(),long(),Results<ClassData>());
			projectData.reportedTime=std::accumulate(classData.begin(),classData.end(),double(),RunTime<ClassData>());
		}
	public:
		ProjectRunner(const std::string& title,
			gppUnit::Notification& notify, 
			gppUnit::MethodTimer& timer,
			const gppUnit::TestCaseList& cases):notify(notify),
			timer(timer),
			cases(cases),
			projectData(title)
		{
			notify.StartProject(*this);
		}
		~ProjectRunner(){ notify.EndProject(); }

	// TODO: Turn run() inside out.
	// Make a ClassRunner a member, then hand it a testcase in each iteration.
		void run(){
			std::for_each(cases.begin(),cases.end(),
				std::bind1st(
					std::mem_fun(&ProjectRunner::call),
					this
				)
			);
			calculateProjectData();
		}
	};

	void TestCaseCaller::whenCalled(){
		ProjectRunner runner("TestCaseCaller",*notify,*timer,cases);
		runner.run();
	}
}
