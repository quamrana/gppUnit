#include "Confirmation.h"
#include "AssertException.h"
#include "ReportResult.h"

namespace gppUnit {
	void ConfirmationBase::Result(const TestResult& result) {
		if(report) {
			report->Report(result);
		}
	}

	void Confirm::fail(const char* message) {
		TestResult result(message);
		Result(result);
	}
	void Confirm::pass(const char* message) {
		TestResult result(true, message);
		Result(result);
	}
	void Confirm::isTrue(bool result, const char* message) {
		if(result) {
			pass(message);
		} else {
			fail(message);
		}
	}
	void Confirm::isFalse(bool result, const char* message) {
		isTrue(!result, message);
	}

	void Expect::Result(const TestResult& result) {
		ConfirmationBase::Result(result);
		if(!result.result) {
			throw gppUnit::assertException;
		}
	}
}

