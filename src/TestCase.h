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
#ifndef TESTCASE_H_9227601C_F5E5_47F6_A89A_F47B3BBB576B
#define TESTCASE_H_9227601C_F5E5_47F6_A89A_F47B3BBB576B

#include <vector>

namespace gppUnit {
	class TestCase {
	protected:
		virtual ~TestCase() {}
	public:
		virtual void setup() {}
		virtual void test() = 0;
		virtual void teardown() {}
	};

	class ReportResult;
	class ResultSetter {
	protected:
		virtual ~ResultSetter() {}
	public:
		virtual void setReport(ReportResult*) = 0;
	};
	inline void setReport(ResultSetter& setter, ReportResult* reporter) {
		setter.setReport(reporter);
	}

	class PrototypeTestCase: public TestCase, public ResultSetter {
	};

	/**
	TestCaseList is subject to changes in definition and location
	*/
	typedef std::vector<PrototypeTestCase*> TestCaseList;
}

#endif // TESTCASE_H_9227601C_F5E5_47F6_A89A_F47B3BBB576B
