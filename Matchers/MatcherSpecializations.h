#ifndef MATCHERSPECIALIZATIONS_H_A2C47514_540D_4DD4_8484_ACE6142B81F7
#define MATCHERSPECIALIZATIONS_H_A2C47514_540D_4DD4_8484_ACE6142B81F7
#include "Matchers.h"

namespace gppUnit{
	class StringFormatting {
		const size_t aperture;
		const std::string elipsis;
		const size_t ray;
		const size_t segment;
		const size_t fixedColumn;
		const size_t fixedColumnPlus;
	public:
		StringFormatting();

		size_t raySize() const { return ray; }
		size_t adjustedFixedColumn() const { return fixedColumnPlus; }

		std::string rayString(const std::string& str) const;
		std::string segmentString(const std::string& str, size_t mismatch) const;
	};

	template <>
	struct equal_to_trait<std::string>: equal_to_trait_base<std::string>, StringFormatting {
		equal_to_trait(const std::string& actual, const std::string& expected);
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

	template <>
	struct equal_to_t<double>: value_matcher<double, equal_to_t<double> > {
		explicit equal_to_t(const double& expected);

		MatcherResult operator()(const double& actual, const double& expected) const ;
		equal_to_t<double>& within(const double& within){ withinValue=within; return *this; }
		double withinValue;
	};
	template <>
	struct equal_to_t<float>: equal_to_t<double> {
		explicit equal_to_t(const float& expected);
		double floatExpected;
	};
}
#endif // MATCHERSPECIALIZATIONS_H_A2C47514_540D_4DD4_8484_ACE6142B81F7
