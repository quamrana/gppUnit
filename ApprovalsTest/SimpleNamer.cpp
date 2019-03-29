#include "SimpleNamer.h"

#include <algorithm>

namespace gppUnit {
	bool isForbidden(char c) {
		static std::string forbiddenChars("\\/:?*\"<>| ");
		return std::string::npos != forbiddenChars.find(c);
	}
	void SimpleNamer::makeNames(const std::string& fullClassName) {
		approvedFileName = sanitized(fullClassName) + ".approved" + ".txt";
		receivedFileName = sanitized(fullClassName) + ".received" + ".txt";
	}

	std::string SimpleNamer::sanitized(const std::string& name) {
		std::string ret = name;
		std::replace_if(ret.begin(), ret.end(), isForbidden, '_');
		return ret;
	}
}
