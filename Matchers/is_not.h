/*
Copyright (c) 2011-2019 Andrew Wall

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
#ifndef IS_NOT_H_61E14812_D6A8_444A_A1C0_298206DD5734
#define IS_NOT_H_61E14812_D6A8_444A_A1C0_298206DD5734

#include "MatcherResult.h"

namespace gppUnit {
	struct is_not_helper {
		static MatcherResult match(const MatcherResult& fwdresult) ;
	};
	template <typename T>
	struct is_not_t: is_not_helper {
		explicit is_not_t(const T& matcher): fwdMatcher(matcher) {}

		template <typename ACTUAL>
		MatcherResult match(const ACTUAL& actual) const {
			return is_not_helper::match(fwdMatcher.match(actual));
		}

		const T fwdMatcher;
	};
	template <typename T>
	is_not_t<T> is_not(const T& matcher) { return is_not_t<T>(matcher); }

	template <typename T>
	T is_not(const is_not_t<T>& matcher) { return matcher.fwdMatcher; }
}

#endif // IS_NOT_H_61E14812_D6A8_444A_A1C0_298206DD5734
