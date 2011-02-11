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
		classData(),
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

