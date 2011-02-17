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

	const char* and_got = "and got";
	const char* but_got = "but got";

	void Confirm::privThat(const MatcherResult& match, const char* message) {
		TestResult result(match.result, message);

		TableFormatter f;
		f << "Expected" << tab << match.strm;
		if(match.hasActual) {
			const char* aux = (result.result) ? and_got : but_got;
			f << aux << tab << match.actualStrm;
		}
		result.description = f.toVector();

		Result(result);
	}

	void Expect::Result(const TestResult& result) {
		ConfirmationBase::Result(result);
		if(!result.result) {
			throw gppUnit::assertException;
		}
	}
}

