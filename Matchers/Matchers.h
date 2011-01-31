#ifndef MATCHERS_H_A1A948B8_4BB3_4E59_8A68_E4E99CC5EEC2
#define MATCHERS_H_A1A948B8_4BB3_4E59_8A68_E4E99CC5EEC2

#include "TableFormatting\TableFormatting.h"
#include "MatcherResult.h"
#include "ProxyType.h"

#include <string>
#include <sstream>

namespace gppUnit {
	template <typename T>
	struct is_not_t {
		explicit is_not_t(const T& matcher): fwdMatcher(matcher) {}

		template <typename ACTUAL>
		MatcherResult match(const ACTUAL& actual) const {
			MatcherResult fwdresult = fwdMatcher.match(actual);
			MatcherResult result(!fwdresult.result);
			result.strm << "not" << tab << fwdresult.strm;
			return result;
		}

		const T fwdMatcher;
	};
	template <typename T>
	is_not_t<T> is_not(const T& matcher) { return is_not_t<T>(matcher); }

	template <typename T>
	T is_not(const is_not_t<T>& matcher) { return matcher.fwdMatcher; }

	struct is_null {
		template <typename ACTUAL>
		MatcherResult match(const ACTUAL& actual) const {
			MatcherResult result(actual == 0);
			result.strm << "is null";
			return result;
		}

		is_not_t<is_null> operator!() const { return is_not(*this); }
	};

	template <typename T, typename DERIVED>
	struct value_matcher {
		explicit value_matcher(const T& expected): expectedValue(expected) {}

		const DERIVED& derivedMatcher() const { return static_cast<const DERIVED&>(*this); }

		template <typename ACTUAL>
		MatcherResult match(const ACTUAL& actual) const {
			return derivedMatcher()(ProxyValue(actual), ProxyValue(expectedValue));
		}

		is_not_t<DERIVED> operator!() const { return is_not(derivedMatcher()); }

		const T& expectedValue;
	};

	template <typename T>
	struct value_trait_base {
		value_trait_base(const T& actual, const T& expected): actualValue(actual), expectedValue(expected) {}

		const T& actualValue;
		const T& expectedValue;
	};
	template <typename T>
	struct equal_to_trait_base: value_trait_base<T> {
		equal_to_trait_base(const T& actual, const T& expected): value_trait_base<T>(actual, expected) {}

		bool equals() { return (equal_to_trait_base<T>::actualValue == equal_to_trait_base<T>::expectedValue); }

	};
	template <typename T>
	struct equal_to_trait: equal_to_trait_base<T> {
		equal_to_trait(const T& actual, const T& expected): equal_to_trait_base<T>(actual, expected) {}

		MatcherResult match() {
			MatcherResult result(equal_to_trait<T>::equals());
			result.strm << "'" << equal_to_trait<T>::expectedValue << "'";
			return result;
		}
	};
	class StringFormatting {
		const size_t aperture;
		const std::string elipsis;
		const size_t ray;
		const size_t segment;
		const size_t fixedColumn;
		const size_t fixedColumnPlus;
	public:
		StringFormatting();

		size_t raySize() { return ray; }
		size_t adjustedFixedColumn() { return fixedColumnPlus; }

		std::string rayString(const std::string& str);
		std::string segmentString(const std::string& str, size_t mismatch);
	};

	template <>
	struct equal_to_trait<std::string>: equal_to_trait_base<std::string>, StringFormatting {
		equal_to_trait(const std::string& actual, const std::string& expected): equal_to_trait_base<std::string>(actual, expected)
			{}
		MatcherResult match();

		enum StringMismatchFormat { SHORT, MEDIUM, LONG };
		struct sizes {
			size_t shortest;
			size_t mismatch;
		};
		sizes getSizes(void);

		struct formatParameters {
			formatParameters(): mmType(SHORT), mismatch(0) {}
			StringMismatchFormat mmType;
			size_t mismatch;
		};
		formatParameters getParams(bool result);
		void formatDescription(TableFormatter& strm, formatParameters params);
	};

	template <typename T>
	struct equal_to_t: value_matcher<T, equal_to_t<T> > {
		explicit equal_to_t(const T& expected): value_matcher<T, equal_to_t<T> >(expected) {}

		template<typename V>
		MatcherResult operator()(const V& actual, const V& expected) const {
			equal_to_trait<V> helper(actual, expected);
			return helper.match();
		}
	};
	template <typename T>
	equal_to_t<T> equal_to(const T& expected) { return equal_to_t<T>(expected); }
	template <typename T>
	equal_to_t<T> equals(const T& expected) { return equal_to_t<T>(expected); }


	template <typename T>
	struct greater_than_t: value_matcher<T, greater_than_t<T> > {
		explicit greater_than_t(const T& expected): value_matcher<T, greater_than_t<T> >(expected) {}

		template<typename V>
		MatcherResult operator()(const V& actual, const V& expected) const {
			MatcherResult result(actual > expected);
			result.strm  << "a value greater than '" << expected << "'";
			return result;
		}
	};
	template <typename T>
	greater_than_t<T> greater_than(const T& expected) { return greater_than_t<T>(expected); }
}

#endif // MATCHERS_H_A1A948B8_4BB3_4E59_8A68_E4E99CC5EEC2
