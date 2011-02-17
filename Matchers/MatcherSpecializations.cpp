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
#include "MatcherSpecializations.h"

namespace gppUnit {
	StringFormatting::StringFormatting(): aperture(100),
		elipsis("..."),
		ray(aperture - elipsis.size()),
		segment(ray - elipsis.size()),
		fixedColumn(aperture / 2),
		fixedColumnPlus(fixedColumn + 1)
	{}

	std::string StringFormatting::rayString(const std::string& str) const {
		std::stringstream strm;
		strm << "'";
		if(str.size() <= aperture) {
			strm << str;
		} else {
			strm << str.substr(0, ray) << elipsis;
		}
		strm << "'";
		return strm.str();
	}
	std::string StringFormatting::segmentString(const std::string& str, size_t mismatch) const {
		std::stringstream strm;
		size_t startColumn = mismatch - fixedColumn + elipsis.size();
		strm << "'" << elipsis  << str.substr(startColumn, segment) << elipsis << "'";
		return strm.str();
	}


	equal_to_trait<std::string>::equal_to_trait(const std::string& actual, const std::string& expected): equal_to_trait_base<std::string>(actual, expected)
	{}

	equal_to_trait<std::string>::sizes equal_to_trait<std::string>::getSizes(void) {
		sizes s;
		s.shortest = actualValue.size();
		size_t longest = expectedValue.size();
		if(longest < s.shortest) {
			std::swap(s.shortest, longest);
		}

		s.mismatch = s.shortest;
		for(size_t i = 0; i < s.shortest; ++i) {
			if(actualValue[i] != expectedValue[i]) {
				s.mismatch = i;
				break;
			}
		}
		return s;
	}
	equal_to_trait<std::string>::formatParameters equal_to_trait<std::string>::getParams(bool result) {
		formatParameters params;
		if(!result) {
			sizes s = getSizes();
			if(s.shortest <= 10) {
				params.mmType = SHORT;
			} else if(s.mismatch <= raySize()) {
				params.mmType = MEDIUM;
				params.mismatch = s.mismatch;
			} else {
				params.mmType = LONG;
				params.mismatch = s.mismatch;
			}
		}
		return params;
	}
	MatcherResult equal_to_trait<std::string>::match() {
		MatcherResult result(equals());

		formatDescription(result, getParams(result.result));
		return result;
	}
	void equal_to_trait<std::string>::formatDescription(MatcherResult& result, formatParameters params) {
		TableFormatter& strm = result.strm;
		TableFormatter& actualStrm = result.actualStrm;
		switch(params.mmType) {
		case SHORT:
			strm << "string" << tab << rayString(expectedValue);
			actualStrm << "actual" << tab << rayString(actualValue) << endl;
			result.hasActual = true;
			break;
		case MEDIUM:
			strm << "string" << tab << rayString(expectedValue) << endl;
			strm << "first mismatch" << tab << std::string(params.mismatch + 1, ' ') << '^' << endl;
			strm << "index " << params.mismatch << tab << std::string(params.mismatch + 1, '-') << '|' << endl;
			strm << "actual" << tab << rayString(actualValue) << endl;
			break;
		case LONG:
			strm << "string" << tab << segmentString(expectedValue, params.mismatch) << endl;
			strm << "first mismatch" << tab << std::string(adjustedFixedColumn(), ' ') << '^' << endl;
			strm << "index " << params.mismatch << tab << std::string(adjustedFixedColumn(), '-') << '|' << endl;
			strm << "actual" << tab << segmentString(actualValue, params.mismatch) << endl;
			break;
		}
	}

	equal_to_t<double>::equal_to_t(const double& expected): value_matcher<double, equal_to_t<double> >(expected),
		withinValue(0)
	{}

	MatcherResult equal_to_t<double>::operator()(const double& actual, const double& expected) const {
		MatcherResult result(
		    ((expected - withinValue) <= actual) &&
		    (actual <= (expected + withinValue))
		);
		result.strm << "'" << expected << "'" << " within '"  << withinValue << "'" ;
		result.actualStrm << "'" << actual << "'";
		result.hasActual=true;
		return result;
	}

	equal_to_t<float>::equal_to_t(const float& expected): equal_to_t<double>(floatExpected),
		floatExpected(expected)
	{}
}

