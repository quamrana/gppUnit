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
