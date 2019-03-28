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
#ifndef DATASTRUCTURES_H_4D95AE2F_F05B_430C_A724_4242350F4A87
#define DATASTRUCTURES_H_4D95AE2F_F05B_430C_A724_4242350F4A87

#include <string>

namespace gppUnit {
	struct ClassData;
	struct MethodData {
		const ClassData& classData;
		std::string title;
		size_t results;
		bool goodReport;
		double reportedTime;

		void accrueResult(bool result) {
			results += 1;
			goodReport &= result;
		}
		void checkForExceptions(bool noExceptions) {
			goodReport &= noExceptions;
		}
		explicit MethodData(const ClassData& c, const std::string& name): classData(c), title(name),
			results(0),
			goodReport(true),
			reportedTime(0)
		{}
	};

	struct ClassData {
		std::string title;
		size_t results;
		bool goodReport;
		double reportedTime;
		explicit ClassData(const std::string& title): title(title),
			results(0),
			goodReport(true),
			reportedTime(-1)
		{}
	};
}
#endif // DATASTRUCTURES_H_4D95AE2F_F05B_430C_A724_4242350F4A87
