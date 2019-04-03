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
#include "ClassRunner.h"

#include "MethodResult.h"
#include "Notification.h"
#include "TypeInformation.h"

#include "Helpers.h"

#include <numeric>
#include <typeinfo>

namespace gppUnit {
	MethodData ClassRunner::callMethod(TestCaseMethodCaller& method) {
		MethodResult desc(context, classData, method);

		desc.run();

		return desc.methodSummary();
	}
	bool ClassRunner::add(const MethodData& data) { methodData.push_back(data); return data.goodReport; }
	bool ClassRunner::run(TestCaseMethodCaller* method) {
		return add(callMethod(*method));
	}

	void ClassRunner::runMethods() {
		if(setup()) {
			test();
		}
		teardown();
	}
	void ClassRunner::calculateClassData() {
		classData.goodReport = std::accumulate(methodData.begin(), methodData.end(), true, Report<MethodData>());
		classData.results = std::accumulate(methodData.begin(), methodData.end(), size_t(), Results<MethodData>());
		classData.reportedTime = std::accumulate(methodData.begin(), methodData.end(), double(), RunTime<MethodData>());
	}

	ClassRunner::ClassRunner(ProjectContext& context_, PrototypeTestCase& testcase_):
		context(context_),
	    notify(context.notify),
		testcase(testcase_),
		setup(testcase, *this),
		test(testcase, *this),
		teardown(testcase, *this),
		methodData(),
		classData(demangleTypeName(typeid(testcase).name())) {
		notify.StartClass(*this);
	}
	ClassRunner::~ClassRunner() { notify.EndClass(); }
}
