#include "MatcherResult.h"

namespace gppUnit {
	MatcherResult::MatcherResult(): result(false),
		strm(),
		hasActual(false),
		actualStrm()
	{}
	MatcherResult::MatcherResult(bool value): result(value),
		strm(),
		hasActual(false),
		actualStrm()
	{}
	std::string MatcherResult::description() const {
		std::string desc = strm.toString();
		if(hasActual) {
			desc += actualStrm.toString();
		}
		return desc;
	}
}
