#include "TestMatchersHelpers.h"

namespace gppUnit{
	template <typename T>
	struct starts_with_t: value_matcher<T, starts_with_t<T> > {
		explicit starts_with_t(const T& expected): value_matcher<T, starts_with_t<T> >(expected) {}

		MatcherResult operator()(const std::string& actual, const std::string& expected) const {
			size_t exp_size=expected.size();
			MatcherResult result(0 == actual.compare(0, exp_size, expected));
			result.strm << "a string starting with '" << expected << "'";
			return result;
		}
	};
	template <typename T>
	starts_with_t<T> starts_with(const T& expected) { return starts_with_t<T>(expected); }

	template <typename T>
	struct ends_with_t: value_matcher<T, ends_with_t<T> > {
		explicit ends_with_t(const T& expected): value_matcher<T, ends_with_t<T> >(expected) {}

		MatcherResult operator()(const std::string& actual, const std::string& expected) const {
			size_t exp_size=expected.size();
			size_t act_size=actual.size();
			bool booleanResult=(exp_size>act_size) ? false : 0 == actual.compare(act_size-exp_size, exp_size, expected);

			MatcherResult result(booleanResult);
			result.strm << "a string ending with '" << expected << "'";
			return result;
		}
	};
	template <typename T>
	ends_with_t<T> ends_with(const T& expected){ return ends_with_t<T>(expected); }

}

namespace TestSubStringMatching{
	using Utilities::MatcherHelper;
	using gppUnit::starts_with;
	using gppUnit::ends_with;

	class BeginsWith: public MatcherHelper{
		void test(){
			That("foo",starts_with("f"),"a string starting with 'f'\n");
			That("bar",!starts_with("f"),"not a string starting with 'f'\n");
			That("bar",!starts_with("doof"),"not a string starting with 'doof'\n");
		}
	}GPPUNIT_INSTANCE;

	class EndsWith: public MatcherHelper{
		void test(){
			That("foo",ends_with("o"),"a string ending with 'o'\n");
			That("bar",!ends_with("o"),"not a string ending with 'o'\n");
			That("bar",!ends_with("doof"),"not a string ending with 'doof'\n");
		}
	}GPPUNIT_INSTANCE;

}
