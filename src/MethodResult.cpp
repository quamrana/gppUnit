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
#include "MethodResult.h"

#include "Notification.h"
#include "TestCaseMethodCaller.h"
#include "TestResult.h"
#include "MethodTimer.h"
#include "AssertException.h"

namespace gppUnit {

	MethodResult::MethodResult(TestCaseMethodCaller& method, Notification& notify, MethodTimer& timer): method(method),
		notify(notify),
		timer(timer),
		methodData(method.methodName()) {
		method.setReport(this);
		notify.StartMethod(*this);
	}
	MethodResult::~MethodResult() { notify.EndMethod(); }

	bool MethodResult::protectMethodFromAssertException() {
		bool result = false;
		try {
			timer.timeMethod(method, *this);
			result = true;
		} catch(AssertException&) {
			//
			// Deliberately catch, then ignore exception
			//
		}
		return result;
	}
	bool MethodResult::protectMethodFromCommonExceptions() {
		bool result = false;
		try {
			result = protectMethodFromAssertException();
		} catch(std::exception& e) {
			reportException(e.what());
		} catch(std::string& e) {
			reportException(e);
		} catch(const char* e) {
			reportException(e);
		} catch(int e) {
			reportException(e);
		}
		return result;
	}

	bool MethodResult::protectMethod() {
		bool result = false;
		try {
			result = protectMethodFromCommonExceptions();
		} catch(...) {
			reportException("Unknown Exception");
		}
		methodData.checkForExceptions(result);
		return result;
	}

	void MethodResult::Report(const TestResult& result) {
		methodData.accrueResult(result.result);
		notify.Result(result);
	}

	void MethodResult::Exception(const std::string& what) {
		notify.Exception(what);
	}

}

