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
#ifndef METHODRESULT_H_BB279506_1005_4F01_B313_46B5B55ECBD8
#define METHODRESULT_H_BB279506_1005_4F01_B313_46B5B55ECBD8

#include "TimeReport.h"
#include "MethodDescription.h"
#include "ReportResult.h"
#include "DataStructures.h"

#include <sstream>

namespace gppUnit {
	class TestCaseMethodCaller;
	class Notification;
	class MethodTimer;


	class MethodResult: public MethodDescription,
		public ReportResult,
		public TimeReport {

		TestCaseMethodCaller& method;
		Notification& notify;
		MethodTimer& timer;
		MethodData methodData;

		void Report(const TestResult& result);
		void reportTime(double run_time) { methodData.reportedTime = run_time; }

		std::string name() const { return methodData.title; }
		size_t results() const { return methodData.results; }
		virtual double run_time() const { return methodData.reportedTime; }

		void Exception(const std::string& /* what */);

		template<typename T>
		void reportException(T what) {
			std::stringstream strm;
			strm << what;
			Exception(strm.str());
		}
		bool protectMethodFromAssertException();
		bool protectMethodFromCommonExceptions();
	public:
		MethodResult(TestCaseMethodCaller& method, Notification& notify, MethodTimer& timer);
		~MethodResult();
		bool protectMethod();
		const MethodData& methodSummary() const { return methodData; }
	};
}

#endif // METHODRESULT_H_BB279506_1005_4F01_B313_46B5B55ECBD8
