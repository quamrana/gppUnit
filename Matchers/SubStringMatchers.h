#ifndef SUBSTRINGMATCHERS_H_EA3AE2EC_560A_4648_932E_C2B399560CC3
#define SUBSTRINGMATCHERS_H_EA3AE2EC_560A_4648_932E_C2B399560CC3

#include "Matchers.h"

namespace gppUnit{
	namespace SubStringMatchers{
		MatcherResult starts_with(const std::string& actual, const std::string& expected);
		MatcherResult ends_with(const std::string& actual, const std::string& expected);
		MatcherResult contains(const std::string& actual, const std::string& expected);
	}

	template <typename T>
	struct starts_with_t: value_matcher<T, starts_with_t<T> > {
		explicit starts_with_t(const T& expected): value_matcher<T, starts_with_t<T> >(expected) {}

		MatcherResult operator()(const std::string& actual, const std::string& expected) const {
			return SubStringMatchers::starts_with(actual,expected);
		}
	};
	template <typename T>
	starts_with_t<T> starts_with(const T& expected) { return starts_with_t<T>(expected); }

	template <typename T>
	struct ends_with_t: value_matcher<T, ends_with_t<T> > {
		explicit ends_with_t(const T& expected): value_matcher<T, ends_with_t<T> >(expected) {}

		MatcherResult operator()(const std::string& actual, const std::string& expected) const {
			return SubStringMatchers::ends_with(actual,expected);
		}
	};
	template <typename T>
	ends_with_t<T> ends_with(const T& expected){ return ends_with_t<T>(expected); }

	template <typename T>
	struct contains_t: value_matcher<T, contains_t<T> > {
		explicit contains_t(const T& expected): value_matcher<T, contains_t<T> >(expected) {}

		MatcherResult operator()(const std::string& actual, const std::string& expected) const {
			return SubStringMatchers::contains(actual,expected);
		}
	};
	template <typename T>
	contains_t<T> contains(const T& expected){ return contains_t<T>(expected); }
}
#endif // SUBSTRINGMATCHERS_H_EA3AE2EC_560A_4648_932E_C2B399560CC3
