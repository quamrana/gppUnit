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
#ifndef HELPERS_H_6D7D0E77_E929_4264_9FE6_0D30D0530B62
#define HELPERS_H_6D7D0E77_E929_4264_9FE6_0D30D0530B62

namespace gppUnit {
	template<typename T>
	struct Report {
		bool operator()(bool init, const T& description) {
			return init & description.goodReport;
		}
	};
	template<typename T>
	struct Results {
		size_t operator()(size_t init, const T& description) {
			return init + description.results;
		}
	};
	template<typename T>
	struct RunTime {
		double operator()(double init, const T& description) {
			return init + description.reportedTime;
		}
	};
}

#endif // HELPERS_H_6D7D0E77_E929_4264_9FE6_0D30D0530B62
