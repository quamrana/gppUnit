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
#ifndef LOGICALMATCHERS_H_01F26AC1_1835_4173_B311_A9E6226CEE7D
#define LOGICALMATCHERS_H_01F26AC1_1835_4173_B311_A9E6226CEE7D

#include "MatcherResult.h"

namespace gppUnit {

	struct any_of_helper {
		MatcherResult match(const MatcherResult& left, const MatcherResult& right) const ;
		MatcherResult nestedMatch(const MatcherResult& left, const MatcherResult& right) const ;
	};
	template<typename Matcher1, typename Matcher2>
	struct any_of_base: any_of_helper {
		any_of_base(const Matcher1& m1, const Matcher2& m2):m1(m1),m2(m2){}

		const Matcher1 m1;
		const Matcher2 m2;

	};

	template<typename Matcher1, typename Matcher2>
	struct any_of_t: any_of_base<Matcher1,Matcher2> {
		any_of_t(const Matcher1& m1, const Matcher2& m2):any_of_base<Matcher1,Matcher2>(m1,m2){}

		typedef any_of_t<Matcher1,Matcher2> self;
		template <typename ACTUAL>
		MatcherResult match(const ACTUAL& actual) const {
			return any_of_helper::match(self::m1.match(actual),self::m2.match(actual));
		}

		template <typename ACTUAL>
		MatcherResult nestedMatch(const ACTUAL& actual) const {
			return any_of_helper::nestedMatch(self::m1.match(actual),self::m2.match(actual));
		}
	};

	template<typename Matcher1, typename Matcher2, typename Matcher3>
	struct any_of_t<Matcher1, any_of_t<Matcher2,Matcher3> >: any_of_base<Matcher1,any_of_t<Matcher2,Matcher3> > {
		any_of_t(const Matcher1& m1, const any_of_t<Matcher2,Matcher3>& m2):any_of_base<Matcher1,any_of_t<Matcher2,Matcher3> >(m1,m2){}

		typedef any_of_t<Matcher1, any_of_t<Matcher2,Matcher3> > self;
		template <typename ACTUAL>
		MatcherResult match(const ACTUAL& actual) const {
			return any_of_helper::match(self::m1.match(actual),self::m2.nestedMatch(actual));
		}
		template <typename ACTUAL>
		MatcherResult nestedMatch(const ACTUAL& actual) const {
			return any_of_helper::nestedMatch(self::m1.match(actual),self::m2.nestedMatch(actual));
		}
	};

	template<typename Matcher1, typename Matcher2>
	any_of_t<Matcher1, Matcher2> any_of(const Matcher1& m1, const Matcher2& m2){ return any_of_t<Matcher1, Matcher2>(m1,m2); }

	template<typename Matcher1, typename Matcher2, typename Matcher3>
	any_of_t<Matcher1, any_of_t<Matcher2,Matcher3> > 
		any_of(const Matcher1& m1, const Matcher2& m2, const Matcher3& m3){
			return any_of(m1, any_of(m2,m3));
	}

	template<typename Matcher1, typename Matcher2, typename Matcher3, typename Matcher4>
	any_of_t<Matcher1, any_of_t<Matcher2, any_of_t<Matcher3,Matcher4> > > 
		any_of(const Matcher1& m1, const Matcher2& m2, const Matcher3& m3, const Matcher4& m4){
			return any_of(m1, any_of(m2, any_of(m3,m4)));
	}

}
#endif // LOGICALMATCHERS_H_01F26AC1_1835_4173_B311_A9E6226CEE7D
