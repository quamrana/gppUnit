#include "Matchers.h"

namespace gppUnit {
	MatcherResult::MatcherResult(): result(false), strm() {}
	MatcherResult::MatcherResult(bool value): result(value), strm() {}
}