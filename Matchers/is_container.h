/*
Copyright (c) 2011-2019 Andrew Wall

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
#ifndef IS_CONTAINER_H_5E6D4350_35BB_45E9_93C2_B2F0C124D89E
#define IS_CONTAINER_H_5E6D4350_35BB_45E9_93C2_B2F0C124D89E
////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above copyright
//     notice appear in all copies and that both that copyright notice and this
//     permission notice appear in supporting documentation.
// The author or Addison-Welsey Longman make no representations about the
//     suitability of this software for any purpose. It is provided "as is"
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

namespace Loki {
////////////////////////////////////////////////////////////////////////////////
// class template Select
// Selects one of two types based upon a boolean constant
// Invocation: Select<flag, T, U>::Result
// where:
// flag is a compile-time boolean constant
// T and U are types
// Result evaluates to T if flag is true, and to U otherwise.
////////////////////////////////////////////////////////////////////////////////

	template <bool flag, typename T, typename U>
	struct Select {
		typedef T Result;
	};
	template <typename T, typename U>
	struct Select<false, T, U> {
		typedef U Result;
	};
////////////////////////////////////////////////////////////////////////////////
// Helper types Small and Big - guarantee that sizeof(Small) < sizeof(Big)
////////////////////////////////////////////////////////////////////////////////

	template <class T>
	struct ConversionHelper {
		typedef char Small;
		struct Big { Small dummy[2]; };

		static T MakeT();
	};
}
namespace stackoverflow {
	// is_container from a stackoverflow answer:
	// http://stackoverflow.com/questions/4347921/sfinae-compiler-troubles/4410310#4410310
	template <typename T>
	struct is_container {
		typedef Loki::ConversionHelper<T> H;
		template <typename U> static typename H::Big Test(...);

		template <typename U>
		static typename H::Small Test(const U& u,
		                              typename U::const_iterator b = ((U*)0)->begin(),
		                              typename U::const_iterator e = ((U*)0)->end());

		enum { result = (sizeof(typename H::Small) == sizeof Test<T>(H::MakeT())) };
	};
}
namespace gppUnit {
	struct false_type { enum { result = false }; };
	struct true_type { enum { result = true }; };

	template <typename>
	struct is_string: false_type {};
	template <>
	struct is_string<std::string>: true_type { };

	template <typename>
	struct is_array: false_type {};
	template <typename T, size_t SIZE>
	struct is_array<T[SIZE]>: true_type { };
}

#endif // IS_CONTAINER_H_5E6D4350_35BB_45E9_93C2_B2F0C124D89E
