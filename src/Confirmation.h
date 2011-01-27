#ifndef CONFIRMATION_H_77E45C37_62F1_45A6_A19B_0733ED0735EF
#define CONFIRMATION_H_77E45C37_62F1_45A6_A19B_0733ED0735EF

#include "TestCase.h"
#include "TestResult.h"
#include "Matchers.h"

namespace gppUnit {
	class ConfirmationBase: public ResultSetter {
		ReportResult* report;
		void setReport(ReportResult* reporter) { report = reporter; }
	protected:
		virtual void Result(const TestResult&);
	public:
		ConfirmationBase(): report(0) {}
	};

	class Confirm: public ConfirmationBase {
	public:
		virtual void fail(const char* message = "fail");
		void pass(const char* message = "pass");
		void isTrue(bool result, const char* message = "Should be True");
		template<typename ACTUAL, typename MATCHER>
		void that(const ACTUAL& actual, MATCHER m, const char* message = "Should match") {
			MatcherResult match = m.match(actual);
			TestResult result(match.result);
			result.message = message;

			const char* aux=(result.result)? "and got" : "but got";
			TableFormatter f;
			f << "Expected" << tab << match.strm;
			f << aux << tab << "'" << ProxyValue(actual) << "'" << endl;
			result.description = f.toVector();

			Result(result);
		}
	};

	class Expect: public Confirm {
	public:
		void fail(const char* message = "fail");
	};
}

#endif // CONFIRMATION_H_77E45C37_62F1_45A6_A19B_0733ED0735EF