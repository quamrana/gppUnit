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
#ifndef CONFIRMATION_H_77E45C37_62F1_45A6_A19B_0733ED0735EF
#define CONFIRMATION_H_77E45C37_62F1_45A6_A19B_0733ED0735EF

#include "TestCase.h"

#include <sstream>

namespace gppUnit {
	struct TestResult;
	struct MatcherResult;

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
		void fail(const char* message = "fail");
		void pass(const char* message = "pass");
		void isTrue(bool result, const char* message = "Should be True");
		void isFalse(bool result, const char* message = "Should be True");

		template<typename ACTUAL, typename MATCHER>
		void that(const ACTUAL& actual, MATCHER m, const char* message = "Should match") {
			const MatcherResult& match = m.match(actual);
			privThat(match, message);
		}
	private:
		void privThat(const MatcherResult& match, const char* message);
	};

	extern const char* and_got;
	extern const char* but_got;

	class Expect: public Confirm {
		virtual void Result(const TestResult&);
	};
}

#endif // CONFIRMATION_H_77E45C37_62F1_45A6_A19B_0733ED0735EF
