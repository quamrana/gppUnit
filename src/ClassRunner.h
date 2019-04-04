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
#ifndef CLASSRUNNER_H_8EB7AFBD_8A5D_4F51_B35B_FBE17B321070
#define CLASSRUNNER_H_8EB7AFBD_8A5D_4F51_B35B_FBE17B321070

#include "ClassDescription.h"
#include "TestCaseMethodCaller.h"
#include "DataStructures.h"
#include "ProjectContext.h"

namespace gppUnit {
	class Notification;
	class MethodTimer;

	class ClassRunner: public ClassDescription, public Runner {
		ProjectContext& context;
		Notification& notify;
		PrototypeTestCase& testcase;

		SetupCaller setup;
		TestCaller test;
		TeardownCaller teardown;

		std::vector<MethodData> methodData;
		ClassData classData;

		std::string name() const override { return classData.title; }
		size_t methods() const override { return methodData.size(); }
		size_t results() const override { return classData.results; }
		double run_time() const override { return classData.reportedTime; }

		MethodData callMethod(gppUnit::TestCaseMethodCaller& method);
		bool add(const MethodData& data);
		bool run(gppUnit::TestCaseMethodCaller* method);

		void runMethods();
		void calculateClassData();
	public:
		ClassRunner(ProjectContext&, PrototypeTestCase&);
		~ClassRunner();
		void run() {
			runMethods();
			calculateClassData();
		}
		const ClassData& classSummary() const { return classData; }
	};
}
#endif // CLASSRUNNER_H_8EB7AFBD_8A5D_4F51_B35B_FBE17B321070
