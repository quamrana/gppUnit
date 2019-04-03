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
#ifndef PROJECTRUNNER_H_E1CE6833_9AF2_4103_91F0_A9A5AB7F8885
#define PROJECTRUNNER_H_E1CE6833_9AF2_4103_91F0_A9A5AB7F8885

#include "ProjectDescription.h"
#include "TestCase.h"
#include "DataStructures.h"
#include "ProjectContext.h"

namespace gppUnit {
	class Notification;
	class MethodTimer;

	class ProjectRunner: public ProjectDescription {
		ProjectContext& context;
		Notification& notify;
		TestCaseList cases;

		std::vector<ClassData> classData;
		ClassData projectData;

		std::string name() const override { return projectData.title; }
		size_t classes() const override { return cases.size(); }
		bool hasPassed() const override { return projectData.goodReport; }
		size_t results() const override { return projectData.results; }
		double run_time() const override { return projectData.reportedTime; }

		void call(PrototypeTestCase* testcase);
		void calculateProjectData();
	public:
		ProjectRunner(const std::string& title, ProjectContext&, const TestCaseList& cases);
		~ProjectRunner();

		bool run();
	};
}
#endif // PROJECTRUNNER_H_E1CE6833_9AF2_4103_91F0_A9A5AB7F8885
