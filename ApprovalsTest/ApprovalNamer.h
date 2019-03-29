#pragma once
#include <string>

namespace gppUnit {
	class ApprovalNamer {
	public:
		virtual std::string getApprovedFile() const = 0;
		virtual std::string getReceivedFile() const = 0;
		virtual ~ApprovalNamer() {}
	};
}
