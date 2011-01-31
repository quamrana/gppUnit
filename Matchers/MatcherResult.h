#ifndef MATCHERRESULT_H_1E2E601F_63D8_4E29_994C_BAD8A7DC8C0E
#define MATCHERRESULT_H_1E2E601F_63D8_4E29_994C_BAD8A7DC8C0E

#include "TableFormatting\TableFormatting.h"

namespace gppUnit {
	struct MatcherResult {
		bool result;
		TableFormatter strm;

		MatcherResult(): result(false), strm() {}
		explicit MatcherResult(bool value): result(value), strm() {}
		std::string description() const { return strm.toString();}
	};
}

#endif // MATCHERRESULT_H_1E2E601F_63D8_4E29_994C_BAD8A7DC8C0E
