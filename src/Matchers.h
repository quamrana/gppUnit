#ifndef MATCHERS_H_A1A948B8_4BB3_4E59_8A68_E4E99CC5EEC2
#define MATCHERS_H_A1A948B8_4BB3_4E59_8A68_E4E99CC5EEC2

#include "TableFormatting.h"

#include <string>

namespace gppUnit {
	struct MatcherResult {
		bool result;
		TableFormatter strm;

		MatcherResult();
		std::string description() const { return strm.toString();}
	};

	template<typename T, typename U=T>
	struct ProxyTypeBase
	{
		typedef T original_type;
		typedef U conversion_type;

		conversion_type value;
		explicit ProxyTypeBase(const original_type& from):value(from){}

		static ProxyTypeBase<original_type,conversion_type> create(const original_type& from){ return ProxyTypeBase(from); }

	protected:
	private:
		// Don't Use
		ProxyTypeBase(){}
	};

	// Define a degenerate derived class
	template<typename T>
	struct ProxyType: ProxyTypeBase<T> {};

	template<>
	struct ProxyType<int>: ProxyTypeBase<int,long> {};
	template<>
	struct ProxyType<const char*>: ProxyTypeBase<const char*,std::string> {};

	template<typename _OP, typename T, typename U>
	MatcherResult binary_op(const _OP& op, const T& expected, const U& actual)
	{
		return op(ProxyType<T>::create(expected).value,ProxyType<U>::create(actual).value);
	}

	template<typename _OP, typename T, typename U, size_t size>
	MatcherResult binary_op(const _OP& op, const T (&expected)[size], const U& actual)
	{
		return op(ProxyType<const T*>::create(expected).value,ProxyType<U>::create(actual).value);
	}

	template<typename _OP, typename T, typename U, size_t size>
	MatcherResult binary_op(const _OP& op, const T& expected, const U (&actual)[size])
	{
		return op(ProxyType<T>::create(expected).value,ProxyType<const U*>::create(actual).value);
	}

	template<typename _OP, typename T, typename U, size_t sizeT, size_t sizeU>
	MatcherResult binary_op(const _OP& op, const T (&expected)[sizeT], const U (&actual)[sizeU])
	{
		return op(ProxyType<const T*>::create(expected).value,ProxyType<const U*>::create(actual).value);
	}

	struct is_null {
		MatcherResult match(const void* actual) const {
			MatcherResult result;
			result.result = (actual == 0);
			return result;
		}
	};

	template <typename T, typename DERIVED>
	struct value_matcher{
		explicit value_matcher(const T& expected):expectedValue(expected){}

		const DERIVED& derivedMatcher() const { return static_cast<const DERIVED&>(*this); }

		template <typename _Act>
		MatcherResult match(const _Act& actual) const {
			return binary_op(derivedMatcher(),actual,expectedValue);
		}

		//is_not_t<_Derived> operator!() const { return is_not(derivedMatcher()); }

		const T& expectedValue;
	};

	template <typename T>
	struct equal_to_trait_base {
		equal_to_trait_base(const T& actual, const T& expected):actualValue(actual),expectedValue(expected){}

		bool equals(){ return (actualValue==expectedValue); }

		const T& actualValue;
		const T& expectedValue;
	};
	template <typename T>
	struct equal_to_trait: equal_to_trait_base<T> {
		equal_to_trait(const T& actual, const T& expected):equal_to_trait_base<T>(actual,expected){}

		MatcherResult match(){
			MatcherResult r;
			r.result = equal_to_trait_base<T>::equals();
			r.strm << "'" << equal_to_trait_base<T>::expectedValue << "'";
			return r;
		}
	};
	template <>
	struct equal_to_trait<std::string>: equal_to_trait_base<std::string> {
		equal_to_trait(const std::string& actual, const std::string& expected):equal_to_trait_base<std::string>(actual,expected),
				aperture(100),
				elipsis("..."),
				ray(aperture-elipsis.size()),
				segment(ray-elipsis.size()),
				fixedColumn(aperture/2)
			{}
		const size_t aperture;
		const std::string elipsis;
		const size_t ray;
		const size_t segment;
		const size_t fixedColumn;

		enum StringMismatchFormat { SHORT, MEDIUM, LONG };
		struct sizes {
			size_t shortest;
			size_t mismatch;
		};
		sizes getSizes(void){
			sizes s;
			s.shortest=actualValue.size();
			size_t longest=expectedValue.size();
			if (longest<s.shortest){
				std::swap(s.shortest,longest);
			}

			s.mismatch=s.shortest;
			for(size_t i=0;i<s.shortest;++i){
				if (actualValue[i]!=expectedValue[i]){
					s.mismatch=i;
					break;
				}
			}
			return s;
		}
		struct formatParameters {
			formatParameters():mmType(SHORT),mismatch(0){}
			StringMismatchFormat mmType;
			size_t mismatch;
		};
		formatParameters getParams(bool result) {
			formatParameters params;
			if (!result) {
				sizes s=getSizes();
				if(s.shortest<=10){
					params.mmType=SHORT;
				} else if (s.mismatch<=ray){
					params.mmType=MEDIUM;
					params.mismatch=s.mismatch;
				} else {
					params.mmType=LONG;
					params.mismatch=s.mismatch;
				}
			}
			return params;
		}
		MatcherResult match(){
			MatcherResult r;
			r.result = equals();

			formatDescription(r.strm,getParams(r.result));
			return r;
		}
		void formatDescription(TableFormatter& strm,formatParameters params){
			switch (params.mmType){
			case SHORT:
				strm << "string" << tab << rayString(expectedValue);
				break;
			case MEDIUM:
				strm << "string" << tab << rayString(expectedValue) << endl;
				strm << "first mismatch" << tab << std::string(params.mismatch+1,' ') << '^' << endl;
				strm << "index " << params.mismatch << tab << std::string(params.mismatch+1,'-') << '|' << endl;
				strm << "actual" << tab << rayString(actualValue) << endl;
				break;
			case LONG:
				strm << "string" << tab << segmentString(expectedValue,params.mismatch) << endl;
				strm << "first mismatch" << tab << std::string(fixedColumn+1,' ') << '^' << endl;
				strm << "index " << params.mismatch << tab << std::string(fixedColumn+1,'-') << '|' << endl;
				strm << "actual" << tab << segmentString(actualValue,params.mismatch) << endl;
				break;
			}
		}
		std::string rayString(const std::string& str){
			std::stringstream strm;
			strm << "'";
			if(str.size()<=aperture){
				strm << str;
			} else {
				strm << str.substr(0,ray) << elipsis;
			}
			strm << "'";
			return strm.str();
		}
		std::string segmentString(const std::string& str, size_t mismatch){
			std::stringstream strm;
			size_t startColumn=mismatch-fixedColumn+elipsis.size();
			strm << "'" << elipsis  << str.substr(startColumn,segment) << elipsis << "'";
			return strm.str();
		}
	};

	template <typename T>
	struct equal_to_t: value_matcher<T,equal_to_t<T> > {
		explicit equal_to_t(const T& expected):value_matcher<T,equal_to_t<T> >(expected){}

		template<typename V>
		MatcherResult operator()(const V& actual, const V& expected) const
		{
			equal_to_trait<V> helper(actual,expected);
			return helper.match();

			//MatcherResult result;
			//result.result=(actual==expected);
			//result.strm << "'" << expected << "'";
			//return result;
		}
	};
	template <typename T>
	equal_to_t<T> equal_to(const T& expected){ return equal_to_t<T>(expected); }
}

#endif // MATCHERS_H_A1A948B8_4BB3_4E59_8A68_E4E99CC5EEC2
