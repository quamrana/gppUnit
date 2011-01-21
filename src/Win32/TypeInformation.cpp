#include "TypeInformation.h"

namespace gppUnit {

	void replaceAll(std::string& name, char oldChar, char newChar) {
		std::string::size_type index = 0;
		goto from;
		do {
			name.replace(index, 1, 1, newChar);
from:
			index = name.find(oldChar, index);
		} while(index != std::string::npos);
	}

	void replaceQuotesWithParentheses(std::string& name) {
		replaceAll(name, '`', '(');
		replaceAll(name, '\'', ')');
	}

	std::string demangleTypeName(const std::string& name) {
		if(name.length() <= 6) {
			return name;
		}
		std::string result = name;
		replaceQuotesWithParentheses(result);
		return result.substr(6);
	}
}
