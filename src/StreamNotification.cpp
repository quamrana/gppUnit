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
#include "StreamNotification.h"
#include "ProjectDescription.h"
#include "ClassDescription.h"
#include "MethodDescription.h"
#include "TestResult.h"

#include <sstream>
#include <algorithm>
#include <functional>

namespace gppUnit {
	std::string asterisks(size_t n) {
		std::string asterisk = "*";
		asterisk.replace(0, 1, n, '*');
		return asterisk;
	}
	std::string PrintFormatter::centreInAsterisks(const std::string& title) const {
		std::string t;
		if(title.size() > size - 4) {
			t = title.substr(0, size - 4);
		} else {
			t = title;
		}
		size_t centre = t.size() + 2;
		size_t left = (size - centre) / 2;
		size_t right = (size - (left + centre));

		std::stringstream strm;
		strm << asterisks(left) << ' ' << t << ' ' << asterisks(right);

		return strm.str();
	}
	std::string PrintFormatter::updateRunningAsterisks(size_t max, size_t current) {
		size_t target = (size * current) / max;
		if(target <= size) {
			if(target > asteriskCounter) {
				size_t count = target - asteriskCounter;
				asteriskCounter = target;
				return asterisks(count);
			}
		}
		return "";
	}
	std::string PrintFormatter::fullWidthAsterisks() const {
		return asterisks(size);
	}

	PrintFormatter::PrintFormatter(size_t size): size(size), asteriskCounter(0) {}

	StreamNotification::StreamNotification(std::ostream& out): out(out),
		formatter(50),
		proj(0),
		desc(0),
		method(0),
		hasFailed(false),
		classCount(0),
		classShown(false),
		methodShown(false)
	{}

	/*
	const char* plural(size_t n) {
		return (n == 1) ? "" : "s";
	}
	*/
	const char* plurale(size_t n) {
		return (n == 1) ? "" : "es";
	}

	void StreamNotification::StartProject(const ProjectDescription& desc) {
		classCount = 0;
		proj = &desc;
		out << formatter.centreInAsterisks(proj->name()) << std::endl;
		out << proj->classes() << " class" << plurale(proj->classes()) << " to run." << std::endl;
	}
	void StreamNotification::StartClass(const ClassDescription& desc) {
		this->desc = &desc;
		classShown = false;
		classCount += 1;
		if(!hasFailed) {
			out << formatter.updateRunningAsterisks(proj->classes(), classCount);
		}
	}
	void StreamNotification::StartMethod(const MethodDescription& desc) {
		method = &desc;
		methodShown = false;
	}
	void StreamNotification::Result(const TestResult& result) {
		if(!result.result) {
			BeforeFailure();
			ShowFailure(result);
		}
	}

	void StreamNotification::BeforeFailure() {
		if(!hasFailed) {
			hasFailed = true;
			out << std::endl;
		}
	}

	const char* ClassPrefix =		" ";
	const char* MethodPrefix =		"  ";
	const char* MessagePrefix =		"   ";
	const char* DescriptionPrefix =	"    ";
	void StreamNotification::ShowClass() {
		if(!classShown) {
			out << ClassPrefix << "In Class: " << desc->name() << std::endl;
			classShown = true;
		}
	}
	void StreamNotification::ShowMethod() {
		if(!methodShown) {
			out << MethodPrefix << "In Method: " << method->name() << std::endl;
			methodShown = true;
		}
	}
	void StreamNotification::ShowDescription(std::string output) const {
		out << DescriptionPrefix << output << std::endl;
	}
	void StreamNotification::ShowFailure(const TestResult& result) {
		ShowClass();
		ShowMethod();
		out << MessagePrefix;
		if(result.message.empty()) {
			out << "Failure" << std::endl;
		} else {
			out << "Message: " << result.message << std::endl;
		}
		std::for_each(result.description.begin(), result.description.end(),
		              std::bind1st(
		                  std::mem_fun(&StreamNotification::ShowDescription),
		                  this
		              )
		             );
	}
	void StreamNotification::Exception(const std::string& what) {
		BeforeFailure();
		ShowClass();
		ShowMethod();
		out << MessagePrefix << what << std::endl;
	}
	void StreamNotification::EndProject() {
		if(!hasFailed) {
			out << std::endl;
			out << "100% tests passed!" << std::endl;
			if(proj->run_time()) {
				out << "run time: " << proj->run_time() << std::endl;
			}
			out << formatter.fullWidthAsterisks() << std::endl;
		}
	}

	void StreamNotification::EndMethod() {
		//out << method->run_time() << std::endl;
	}

}
