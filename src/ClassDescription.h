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
#ifndef CLASSDESCRIPTION_H_BDC873D7_B4F5_4B0B_AB40_7C3647B5CC28
#define CLASSDESCRIPTION_H_BDC873D7_B4F5_4B0B_AB40_7C3647B5CC28

#include <string>

namespace gppUnit {
	class ClassDescription {
	protected:
		virtual ~ClassDescription() {}
	public:
		virtual std::string name() const = 0;
		virtual size_t methods() const = 0;
		virtual size_t results() const = 0;
		virtual double run_time() const = 0;
	};
}

#endif // CLASSDESCRIPTION_H_BDC873D7_B4F5_4B0B_AB40_7C3647B5CC28
