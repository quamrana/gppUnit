#include "is_not.h"

namespace gppUnit {
	MatcherResult is_not_helper::match(const MatcherResult& fwdresult) const {
		MatcherResult result(!fwdresult.result);
		result.strm << "not" << tab << fwdresult.strm;
		return result;
	}
}
