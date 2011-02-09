#ifndef IS_NOT_H_61E14812_D6A8_444A_A1C0_298206DD5734
#define IS_NOT_H_61E14812_D6A8_444A_A1C0_298206DD5734

#include "MatcherResult.h"

namespace gppUnit {
	struct is_not_helper {
		MatcherResult match(const MatcherResult& fwdresult) const ;
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
