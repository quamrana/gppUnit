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
#ifndef PROXYTYPE_H_EA518192_C981_4852_9876_7525B8F209C8
#define PROXYTYPE_H_EA518192_C981_4852_9876_7525B8F209C8

namespace gppUnit {
	template<typename T, typename U>
	struct ProxyTypeConverter {
		typedef U conversion_type;
		U value;
		explicit ProxyTypeConverter(const T& from): value(from) {}
	};

	template<typename T, typename U = T>
	struct ProxyTypeBase: ProxyTypeConverter<T, U> {
		typedef T original_type;

		explicit ProxyTypeBase(const original_type& from): ProxyTypeConverter<T, U>(from) {}

		static ProxyTypeBase<T, U> create(const original_type& from) { return ProxyTypeBase(from); }

	private:
		ProxyTypeBase() {}
	};


	// Define a degenerate derived class
	template<typename T>
	struct ProxyType: ProxyTypeBase<T> {};

	template<typename T>
	typename ProxyType<T>::conversion_type ProxyValue(const T& value) { return ProxyType<T>::create(value).value; }

	template<typename T, size_t size>
	typename ProxyType<const T*>::conversion_type ProxyValue(const T(&value)[size]) { return ProxyType<const T*>::create(value).value; }

}

#endif // PROXYTYPE_H_EA518192_C981_4852_9876_7525B8F209C8
