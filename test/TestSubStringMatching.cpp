#include "TestMatchersHelpers.h"

namespace gppUnit{
	template <typename T>
	struct begins_with_t: value_matcher<T, begins_with_t<T> > {
		explicit begins_with_t(const T& expected): value_matcher<T, begins_with_t<T> >(expected) {}

		MatcherResult operator()(const std::string& actual, const std::string& expected) const {
			size_t exp_size=expected.size();
			MatcherResult result(0 == actual.compare(0, exp_size, expected));
			result.strm << "a string starting with '" << expected << "'";
			return result;
		}
	};
	template <typename T>
	begins_with_t<T> begins_with(const T& expected) { return begins_with_t<T>(expected); }

}

namespace TestSubStringMatching{
	using Utilities::MatcherHelper;
	using gppUnit::begins_with;

	class BeginsWith: public MatcherHelper{
		void test(){
			That("foo",begins_with("f"),"a string starting with 'f'\n");
			That("bar",!begins_with("f"),"not a string starting with 'f'\n");
		}
	}GPPUNIT_INSTANCE;

}
