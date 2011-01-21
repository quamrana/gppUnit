#include "src\ProjectDescription.h"
#include "src\ClassRunner.h"

#include "src\Helpers.h"

/*
#include "src\MethodNames.h"
#include "src\TestCaseMethodCaller.h"
#include "src\MethodDescription.h"
#include "src\ReportResult.h"
#include "src\TestResult.h"
#include "src\TypeInformation.h"
#include "src\ClassDescription.h"
#include "src\MethodResult.h"
*/

#include "TestUtilities.h"

#include <algorithm>
#include <functional>
#include <numeric>

namespace Utilities{




	class ProjectRunner: public gppUnit::ProjectDescription{
		gppUnit::Notification& notify;
		gppUnit::MethodTimer& timer;
		gppUnit::TestCaseList cases;

		std::vector<gppUnit::ClassData> classData;
		gppUnit::ClassData projectData;

		std::string name() const { return projectData.title; }
		size_t classes() const { return cases.size(); }
		size_t results() const { return projectData.results; }
		double run_time() const { return projectData.reportedTime; }

		void call(gppUnit::PrototypeTestCase* testcase){
			gppUnit::ClassRunner runner(notify,*testcase,timer);

			runner.run();

			classData.push_back(runner.classSummary());
		}
		void calculateProjectData(){
			projectData.results=std::accumulate(classData.begin(),classData.end(),long(),gppUnit::Results<gppUnit::ClassData>());
			projectData.reportedTime=std::accumulate(classData.begin(),classData.end(),double(),gppUnit::RunTime<gppUnit::ClassData>());
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
