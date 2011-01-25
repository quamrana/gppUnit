#include "Confirmation.h"
#include "AssertException.h"
#include "ReportResult.h"

namespace gppUnit {
	void Confirm::fail(const char* message) {
		TestResult result;
		result.message = message;
		report->Report(result);
	}
	void Confirm::pass(const char* message) {
		TestResult result;
		result.result = true;
		result.message = message;
		report->Report(result);
	}
	void Confirm::isTrue(bool result, const char* message) {
		if(result) {
			pass(message);
		} else {
			fail(message);
		}
	}
	void Expect::fail(const char* message) {
		Confirm::fail(message);
		throw gppUnit::assertException;
	}
}

