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
#ifndef METHODDESCRIPTION_H_32660EAC_DB28_4549_BD53_E61D323298B0
#define METHODDESCRIPTION_H_32660EAC_DB28_4549_BD53_E61D323298B0

#include <string>

namespace gppUnit {
	class MethodDescription {
	protected:
		virtual ~MethodDescription() {}
	public:
		virtual std::string name() const = 0;
		virtual size_t results() const = 0;
		virtual double run_time() const = 0;
	};
}

#endif // METHODDESCRIPTION_H_32660EAC_DB28_4549_BD53_E61D323298B0
