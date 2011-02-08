#include "SubStringMatchers.h"

namespace gppUnit{
	namespace SubStringMatchers{
		MatcherResult starts_with(const std::string& actual, const std::string& expected){
			size_t exp_size=expected.size();
			MatcherResult result(0 == actual.compare(0, exp_size, expected));
			result.strm << "a string starting with '" << expected << "'";
			return result;
		}
		MatcherResult ends_with(const std::string& actual, const std::string& expected) {
			size_t exp_size=expected.size();
			size_t act_size=actual.size();
			bool booleanResult=(exp_size>act_size) ? false : 0 == actual.compare(act_size-exp_size, exp_size, expected);

			MatcherResult result(booleanResult);
			result.strm << "a string ending with '" << expected << "'";
			return result;
		}
		MatcherResult contains(const std::string& actual, const std::string& expected) {
			MatcherResult result(actual.find(expected)!=std::string::npos);
			result.strm << "a string that contains '" << expected << "'";
			return result;
		}
	}

}
