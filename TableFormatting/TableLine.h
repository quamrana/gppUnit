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
#ifndef TABLELINE_H_8DC577D3_F15F_49BA_95F6_36C427673947
#define TABLELINE_H_8DC577D3_F15F_49BA_95F6_36C427673947

#include "Column.h"

#include <vector>
#include <sstream>

namespace gppUnit {
	class TableLine {
		std::vector<Column> columns;
		std::stringstream stream;
		bool streamIsEmpty;

		void pad(std::vector<size_t>& sizes) const ;
		void clearStream();

	public:
		TableLine(): columns(), stream(), streamIsEmpty(true) {}
		TableLine(const TableLine&);
		TableLine& operator=(TableLine const&);
		void clear();
		size_t size() const { return columns.size(); }
		bool isEmpty() const { return streamIsEmpty && size() == 0; }

		template<typename ValueArgument>
		void append(const ValueArgument& str) { stream << str; streamIsEmpty = false; }
		void append(const TableLine& line);
		void tab();

		//void patch(const TableLine& line);
		std::string toString() const;
		std::string toString(const std::vector<size_t>& sizes) const;

		void update(std::vector<size_t>& sizes) const;
	};
}

#endif // TABLELINE_H_8DC577D3_F15F_49BA_95F6_36C427673947
