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

#include <sstream>

namespace gppUnit{

	template<class STREAM, class DELIM>
	struct format_iterator_t: std::iterator<std::output_iterator_tag, void,void,void,void>{
		format_iterator_t(STREAM& strm, const DELIM* delim):strm(&strm),
			delim(delim),
			first(true)
		{}
		template<class _Ty>
		format_iterator_t& operator=(const _Ty& value){
			if (!first) {
				if (delim != 0) {
					*strm << delim;
				}
			}
			first=false;
			*strm << value;
			return (*this);
		}
		// operator* and operator++ to satisfy std::copy
		format_iterator_t& operator*(){	return (*this);	}
		format_iterator_t& operator++(){ return (*this); }

	protected:
		STREAM* strm;
		const DELIM* delim;
		bool first;
	};
	template<class STREAM, class DELIM>
	format_iterator_t<STREAM,DELIM> format_iterator(STREAM& strm, const DELIM* delim){ return format_iterator_t<STREAM,DELIM>(strm,delim); }

	template <typename T>
	struct equal_to_trait<std::vector<T> >: equal_to_trait_base<std::vector<T> > {
		equal_to_trait(const std::vector<T>& actual, const std::vector<T>& expected): equal_to_trait_base<std::vector<T> >(actual, expected) {}
		typedef equal_to_trait<std::vector<T> > self;

		MatcherResult match() {
			const std::vector<T>& exp=self::expectedValue;
			MatcherResult result(self::equals());
			if (exp.size()==0){
				result.strm << "Empty Vector";
			} else {
				result.strm << '[';
				std::copy(exp.begin(),exp.end(),format_iterator(result.strm," "));
				result.strm << ']';
			}
			return result;
		}
	};

}

namespace TestCollectionEquals{
	using gppUnit::equals;
	using Utilities::MatcherHelper;

	template<typename T>
	class VectorHelper: public MatcherHelper{
		void setup(){
			v1.clear();
			v2.clear();
		}
	protected:
		std::vector<T> v1;
		std::vector<T> v2;
	};
	class EmptyIntVector: public VectorHelper<int>{
		void test(void){
			That(v1,equals(v2),"Empty Vector\n");
		}
	}GPPUNIT_INSTANCE;

	class UnequalIntVector: public VectorHelper<int>{
		void test(void){
			v1.push_back(1);
			That(v1,!equals(v2),"not Empty Vector\n");
		}
	}GPPUNIT_INSTANCE;

	class EqualIntVector: public VectorHelper<int>{
		void test(void){
			v1.push_back(1);
			v2.push_back(1);
			That(v1,equals(v2),"[1]\n");
		}
	}GPPUNIT_INSTANCE;

	class EqualIntVectorTwoElements: public VectorHelper<int>{
		void test(void){
			v1.push_back(1);
			v2.push_back(1);
			v1.push_back(2);
			v2.push_back(2);
			That(v1,equals(v2),"[1 2]\n");
			// TODO: Fix that to be able to stream anything.
			//confirm.that(v1,equals(v2));
		}
	}GPPUNIT_INSTANCE;
}
