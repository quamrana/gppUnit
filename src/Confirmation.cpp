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
		TestResult result;
		result.message = message;
		Result(result);
	}
	void Confirm::pass(const char* message) {
		TestResult result;
		result.result = true;
		result.message = message;
		Result(result);
	}
	void Confirm::isTrue(bool result, const char* message) {
		if(result) {
			pass(message);
		} else {
			fail(message);
		}
	}
	//TODO: I was expecting to override ConfirmationBase::Result
	// but this will do for now.
	void Expect::fail(const char* message) {
		Confirm::fail(message);
		throw gppUnit::assertException;
	}
}

