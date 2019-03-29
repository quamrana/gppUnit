#pragma once

#include "ApprovalNamer.h"

namespace gppUnit {
	class SimpleNamer: public ApprovalNamer {
	public:
		//template<typename T>
		//explicit SimpleNamer(const T& base): SimpleNamer(gppUnit::demangleTypeName(typeid(base).name())) {}
		explicit SimpleNamer(const std::string& fullClassName) { makeNames(fullClassName); }
		std::string getApprovedFile() const { return approvedFileName; }
		std::string getReceivedFile() const { return receivedFileName; }

	private:
		void makeNames(const std::string& fullClassName);
		std::string approvedFileName;
		std::string receivedFileName;

		std::string sanitized(const std::string& name);
	};
}
