#include "Matchers.h"

namespace gppUnit {
	StringFormatting::StringFormatting(): aperture(100),
			elipsis("..."),
			ray(aperture - elipsis.size()),
			segment(ray - elipsis.size()),
			fixedColumn(aperture / 2),
			fixedColumnPlus(fixedColumn + 1)
		{}

	std::string StringFormatting::rayString(const std::string& str) {
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
	std::string StringFormatting::segmentString(const std::string& str, size_t mismatch) {
		std::stringstream strm;
		size_t startColumn = mismatch - fixedColumn + elipsis.size();
		strm << "'" << elipsis  << str.substr(startColumn, segment) << elipsis << "'";
		return strm.str();
	}



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

		formatDescription(result.strm, getParams(result.result));
		return result;
	}
	void equal_to_trait<std::string>::formatDescription(TableFormatter& strm, formatParameters params) {
		switch(params.mmType) {
		case SHORT:
			strm << "string" << tab << rayString(expectedValue);
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


}