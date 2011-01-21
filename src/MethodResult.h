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
	public:
		MethodResult(TestCaseMethodCaller& method, Notification& notify, MethodTimer& timer);
		~MethodResult();
		bool protectMethod();
		const MethodData& methodSummary() const { return methodData; }
	};
}

#endif // METHODRESULT_H_BB279506_1005_4F01_B313_46B5B55ECBD8
