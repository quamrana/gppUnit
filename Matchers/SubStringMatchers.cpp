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

#include "SubStringMatchers.h"

namespace gppUnit {
	namespace SubStringMatchers {
		MatcherResult starts_with(const std::string& actual, const std::string& expected) {
			size_t exp_size = expected.size();
			MatcherResult result(0 == actual.compare(0, exp_size, expected));
			result.strm << "a string starting with '" << expected << "'";
			return result;
		}
		MatcherResult ends_with(const std::string& actual, const std::string& expected) {
			size_t exp_size = expected.size();
			size_t act_size = actual.size();
			bool booleanResult = (exp_size > act_size) ? false : 0 == actual.compare(act_size - exp_size, exp_size, expected);

			MatcherResult result(booleanResult);
			result.strm << "a string ending with '" << expected << "'";
			return result;
		}
		MatcherResult contains(const std::string& actual, const std::string& expected) {
			MatcherResult result(actual.find(expected) != std::string::npos);
			result.strm << "a string that contains '" << expected << "'";
			return result;
		}
	}
}
