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

namespace gppUnit {

	template<typename Matcher1, typename Matcher2>
	struct any_of_base {
		any_of_base(const Matcher1& m1, const Matcher2& m2):m1(m1),m2(m2){}
		//any_of_base(const any_of_base<T,U>& m):m1(m.m1),m2(m.m2){}

		const Matcher1 m1;
		const Matcher2 m2;
	};

	template<typename Matcher1, typename Matcher2>
	struct any_of_t: any_of_base<Matcher1,Matcher2> {
		any_of_t(const Matcher1& m1, const Matcher2& m2):any_of_base<Matcher1,Matcher2>(m1,m2){}

		typedef any_of_t<Matcher1,Matcher2> self;
		template <typename ACTUAL>
		MatcherResult match(const ACTUAL& actual) const {
			MatcherResult resultLeft= self::m1.match(actual);
			MatcherResult resultRight= self::m2.match(actual);
			MatcherResult result(resultLeft.result || resultRight.result);
			result.strm << "a match with one of:" << tab << resultLeft.strm;
			result.strm << "or" << tab << resultRight.strm;
			return result;
		}

		template <typename ACTUAL>
		MatcherResult nestedMatch(const ACTUAL& actual) const {
			MatcherResult resultLeft= self::m1.match(actual);
			MatcherResult resultRight= self::m2.match(actual);
			MatcherResult result(resultLeft.result || resultRight.result);
			result.strm << resultLeft.strm;
			result.strm << "or" << tab;
			result.strm.patch(resultRight.strm);
			return result;
		}
	};

	template<typename Matcher1, typename Matcher2, typename Matcher3>
	struct any_of_t<Matcher1, any_of_t<Matcher2,Matcher3> >: any_of_base<Matcher1,any_of_t<Matcher2,Matcher3> > {
		any_of_t(const Matcher1& m1, const any_of_t<Matcher2,Matcher3>& m2):any_of_base<Matcher1,any_of_t<Matcher2,Matcher3> >(m1,m2){}

		typedef any_of_t<Matcher1, any_of_t<Matcher2,Matcher3> > self;
		template <typename ACTUAL>
		MatcherResult match(const ACTUAL& actual) const {
			MatcherResult resultLeft= self::m1.match(actual);
			MatcherResult resultRight= self::m2.nestedMatch(actual);
			MatcherResult result(resultLeft.result || resultRight.result);
			result.strm << "a match with one of:" << tab << resultLeft.strm;
			result.strm << "or" << tab;
			result.strm.patch(resultRight.strm);
			return result;
		}
		template <typename ACTUAL>
		MatcherResult nestedMatch(const ACTUAL& actual) const {
			MatcherResult resultLeft= self::m1.match(actual);
			MatcherResult resultRight= self::m2.nestedMatch(actual);
			MatcherResult result(resultLeft.result || resultRight.result);
			result.strm << resultLeft.strm;
			result.strm << "or" << tab;
			result.strm.patch(resultRight.strm);
			return result;
		}
	};



	template<typename Matcher1, typename Matcher2>
	any_of_t<Matcher1, Matcher2> any_of(const Matcher1& m1, const Matcher2& m2){ return any_of_t<Matcher1, Matcher2>(m1,m2); }

	template<typename Matcher1, typename Matcher2, typename Matcher3>
	any_of_t<Matcher1, any_of_t<Matcher2,Matcher3> > 
		any_of(const Matcher1& m1, const Matcher2& m2, const Matcher3& m3){
			return any_of(m1, any_of(m2,m3));
	}

}

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
			//TODO: I want a solution which does not introduce this tab:
			//    vvv
			tf << tab << "or" << tab << "a value less than '-4'" << endl;
			That(longint,any_of(less_than(integer),equals(longint),less_than(schar)),tf.toVector());

		}
	}; // GPPUNIT_INSTANCE;

}
