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
#include "TestMatchersHelpers.h"
#include "Matchers\LogicalMatchers.h"

typedef std::vector<std::string> strvec;

namespace TestLogicalOrMatcher{
	using Utilities::MatcherHelper;
	using gppUnit::less_than;
	using gppUnit::equals;
	using gppUnit::any_of;
	using gppUnit::tab;
	using gppUnit::endl;

	class TestLogicalMatchersHelper: public Auto::TestCase{
	protected:
		template<typename MATCHER, typename ACTUAL>
		void That(const ACTUAL& actual, MATCHER m, const strvec& desc){
			gppUnit::MatcherResult result=m.match(actual);
			confirm.isTrue(result.result,"result is true");

			const strvec& matcherDescription=result.strm.toVector();
			expect.that(matcherDescription.size(),equals(desc.size()),"Description has same number of lines");
			confirm.isTrue(desc==matcherDescription,"Whole Description should match");

			strvec::const_iterator test=matcherDescription.begin();
			for(strvec::const_iterator it=desc.begin(), end=desc.end(); it!=end; ++it){
				confirm.that(*test++,equals(*it),(*it).c_str());
			}
		}
	};

	class TestIntegers: public TestLogicalMatchersHelper{
		void test(){
			int integer=1;
			long longint=2;
			signed char schar=-4;
			std::vector<MatcherHelper*> vec;

			gppUnit::TableFormatter tf;
			tf << "a match with one of:" << tab << "a value less than '1'" << endl;
			tf << "or" << tab << "'2'" << endl;
			That(longint,any_of(less_than(integer),equals(longint)),tf.toVector());

			tf.clear();
			tf << "a match with one of:" << tab << "a value less than '0'" << endl;
			tf << "or" << tab << "'1'" << endl;
			That(schar,any_of(less_than(vec.size()),equals(integer)),tf.toVector());
		}
	}GPPUNIT_INSTANCE;

	class TestThreeTerms: public TestLogicalMatchersHelper{
		void test(){
			int integer=1;
			long longint=2;
			signed char schar=-4;
			std::vector<MatcherHelper*> vec;

			gppUnit::TableFormatter tf;
			tf << "a match with one of:" << tab << "a value less than '1'" << endl;
			tf << "or" << tab << "'2'" << endl;
			tf << "or" << tab << "a value less than '-4'" << endl;
			That(longint,any_of(less_than(integer),equals(longint),less_than(schar)),tf.toVector());

		}
	}GPPUNIT_INSTANCE;

	class TestFourTerms: public TestLogicalMatchersHelper{
		void test(){
			int integer=1;
			long longint=2;
			signed char schar=-4;
			std::vector<MatcherHelper*> vec;

			gppUnit::TableFormatter tf;
			tf << "a match with one of:" << tab << "a value less than '1'" << endl;
			tf << "or" << tab << "'2'" << endl;
			tf << "or" << tab << "a value less than '-4'" << endl;
			tf << "or" << tab << "a value less than '0'" << endl;
			That(longint,any_of(less_than(integer),equals(longint),less_than(schar),less_than(vec.size())),tf.toVector());

			//confirm.that(15,any_of(less_than(integer),equals(longint),less_than(schar),less_than(vec.size())));
		}
	}GPPUNIT_INSTANCE;

}
