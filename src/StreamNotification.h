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
#ifndef STREAMNOTIFICATION_H_9DE37245_C9F0_4B33_A0A5_25E32A5DECE9
#define STREAMNOTIFICATION_H_9DE37245_C9F0_4B33_A0A5_25E32A5DECE9

#include "Notification.h"

namespace gppUnit {

	class PrintFormatter {
		size_t size;
		size_t asteriskCounter;
	public:
		std::string centreInAsterisks(const std::string& title) const ;
		std::string updateRunningAsterisks(size_t max, size_t current);
		std::string fullWidthAsterisks() const ;
		explicit PrintFormatter(size_t size);
	};

	class StreamNotification: public Notification {
	private:
		void StartProject(const ProjectDescription&);
		void StartClass(const ClassDescription&);
		void StartMethod(const MethodDescription&);

        size_t resultCount;
		void Result(const TestResult&);
		void Exception(const std::string& /* what */);

		void EndMethod();

		void EndProject();

	protected:
		std::ostream& out;
		PrintFormatter formatter;
		const ProjectDescription* proj;
		const ClassDescription* desc;
		const MethodDescription* method;

		bool hasFailed;
		size_t classCount;
		bool classShown;
		bool methodShown;

		void BeforeFailure();
		void ShowClass();
		void ShowMethod();
		void BeforeMessage();

		void ShowDescription(std::string) const ;
		void ShowFailure(const TestResult&);
	public:
		explicit StreamNotification(std::ostream& out);
	};
}

#endif // STREAMNOTIFICATION_H_9DE37245_C9F0_4B33_A0A5_25E32A5DECE9
