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
#include "ClassDocumentation.h"

#include "ClassDescription.h"

#include <sstream>
#include <stack>

namespace gppUnit {

	void ClassDocumentation::StartClass(const ClassDescription& aClass) {
		collect.push_back(aClass.name());
	}

	std::string ClassDocumentation::getFormattedDocumentation() const {
		std::stringstream str;

		Head head;
		std::stack<Head> headstack;
		std::string tail;

		vecstr::const_iterator it = collect.begin();
		vecstr::const_iterator end = collect.end();

		for(;;) {
			if(tail.empty()) {
				if(it == end) {
					return str.str();
				} else {
					tail = *it++;
				}
			}

			for(;;) {
				std::string::size_type jt = tail.find(head.head);
				if(jt == 0) {
					tail = tail.substr(head.head.size());
					break;
				} else {
					head = headstack.top();
					headstack.pop();
				}
			}

			for(;;) {
				std::string::size_type ct = tail.find("::");
				if(ct != std::string::npos) {
					std::string nexthead = tail.substr(0, ct);
					std::string tmphead = nexthead + "::";
					tail = tail.substr(tmphead.size());
					headstack.push(head);
					head.head += tmphead;
					str << head.spacing << nexthead << std::endl;
					head.spacing += ' ';
				} else {
					break;
				}
			}
			str << head.spacing << tail << std::endl;
			tail = "";
		}
	}
}
