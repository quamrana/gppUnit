/*
Copyright (c) 2011 Andrew Wall

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef SUBSTRINGMATCHERS_H_EA3AE2EC_560A_4648_932E_C2B399560CC3
#define SUBSTRINGMATCHERS_H_EA3AE2EC_560A_4648_932E_C2B399560CC3

#include "Matchers.h"

namespace gppUnit {
	namespace SubStringMatchers {
		MatcherResult starts_with(const std::string& actual, const std::string& expected);
		MatcherResult ends_with(const std::string& actual, const std::string& expected);
		MatcherResult contains(const std::string& actual, const std::string& expected);
	}

	template <typename T>
	struct starts_with_t: value_matcher<T, starts_with_t<T> > {
		explicit starts_with_t(const T& expected): value_matcher<T, starts_with_t<T> >(expected) {}

		MatcherResult operator()(const std::string& actual, const std::string& expected) const {
			return SubStringMatchers::starts_with(actual, expected);
		}
	};
	template <typename T>
	starts_with_t<T> starts_with(const T& expected) { return starts_with_t<T>(expected); }

	template <typename T>
	struct ends_with_t: value_matcher<T, ends_with_t<T> > {
		explicit ends_with_t(const T& expected): value_matcher<T, ends_with_t<T> >(expected) {}

		MatcherResult operator()(const std::string& actual, const std::string& expected) const {
			return SubStringMatchers::ends_with(actual, expected);
		}
	};
	template <typename T>
	ends_with_t<T> ends_with(const T& expected) { return ends_with_t<T>(expected); }

	template <typename T>
	struct contains_t: value_matcher<T, contains_t<T> > {
		explicit contains_t(const T& expected): value_matcher<T, contains_t<T> >(expected) {}

		MatcherResult operator()(const std::string& actual, const std::string& expected) const {
			return SubStringMatchers::contains(actual, expected);
		}
	};
	template <typename T>
	contains_t<T> contains(const T& expected) { return contains_t<T>(expected); }
}
#endif // SUBSTRINGMATCHERS_H_EA3AE2EC_560A_4648_932E_C2B399560CC3
