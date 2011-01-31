#include "ProjectRunner.h"
#include "ClassRunner.h"
#include "Notification.h"

#include "Helpers.h"

#include <algorithm>
#include <numeric>

namespace gppUnit {

	void ProjectRunner::call(gppUnit::PrototypeTestCase* testcase) {
		ClassRunner runner(notify, *testcase, timer);

		runner.run();

		classData.push_back(runner.classSummary());
	}

	void ProjectRunner::calculateProjectData() {
		projectData.goodReport = std::accumulate(classData.begin(), classData.end(), true, Report<ClassData>());
		projectData.results = std::accumulate(classData.begin(), classData.end(), size_t(), Results<ClassData>());
		projectData.reportedTime = std::accumulate(classData.begin(), classData.end(), double(), RunTime<ClassData>());
	}
	ProjectRunner::ProjectRunner(const std::string& title,
	                             Notification& notify,
	                             MethodTimer& timer,
	                             const TestCaseList& cases): notify(notify),
		timer(timer),
		cases(cases),
		projectData(title) {
		notify.StartProject(*this);
	}
	ProjectRunner::~ProjectRunner() { notify.EndProject(); }

	// TODO: Turn run() inside out.
	// Make a ClassRunner a member, then hand it a testcase in each iteration.
	bool ProjectRunner::run() {
		std::for_each(cases.begin(), cases.end(),
		              std::bind1st(
		                  std::mem_fun(&ProjectRunner::call),
		                  this
		              )
		             );
		calculateProjectData();
		return projectData.goodReport;
	}
}

