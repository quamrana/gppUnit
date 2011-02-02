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
#include "TableFormatting.h"

#include <numeric>
#include <algorithm>

namespace gppUnit {
	void TableFormatter::tab() {
		//*this << ' ';
		line.tab();
	}
	void TableFormatter::endLine() {
		if (!lineIsEmpty)
			line.tab();
		page.push_back(line);
		clearLine();
	}
	void TableFormatter::clearLine() {
		line.clear();
		lineIsEmpty = true;
	}

	namespace TableFunctors {
		struct NewLines {
			std::string operator()(const std::string& init, const std::string& item)const {
				return init + item + "\n";
			}
		};
		struct Update {
			std::vector<size_t> sizes;
			void operator()(const TableLine& line) { line.update(sizes); }
		};
		struct Accumulator {
			explicit Accumulator(const std::vector<size_t>& sizes): sizes(sizes) {}
			std::vector<std::string> result;
			std::vector<size_t> sizes;
			void operator()(const TableLine& line) { result.push_back(line.toString(sizes)); }
		};
		struct UpdateTable {
			explicit UpdateTable(TableFormatter* table): table(table), size(table->lineSize()), firstLine(true) {}
			TableFormatter* table;
			size_t size;
			bool firstLine;
			void operator()(const std::string& line) {
				using gppUnit::tab;
				if(firstLine) {
					firstLine = false;
				} else {
					for(size_t i = 0; i < size; ++i) {
						(*table) << tab;
					}
				}
				(*table) << line << endl;
			}
		};
	}
	TableFunctors::Accumulator partialVector(const std::vector<TableLine>& page, const TableLine& line, bool lineIsEmpty){
		TableFunctors::Update update = std::for_each(page.begin(), page.end(), TableFunctors::Update());
		if(!lineIsEmpty) { line.update(update.sizes); }

		return std::for_each(page.begin(), page.end(), TableFunctors::Accumulator(update.sizes));
	}

	TableFormatter& TableFormatter::operator<<(const TableFormatter& table) {
		std::vector<std::string> result = table.toVector();

		std::for_each(result.begin(), result.end(), TableFunctors::UpdateTable(this));

		return *this;
	}
	TableFormatter& TableFormatter::patch(TableFormatter& table){
		std::vector<TableLine>::iterator it=table.page.begin(), end= table.page.end();

		line.patch(*it++);
		endLine();

		std::copy (it,end,back_inserter(page));

		return *this;
	}

	std::vector<std::string> TableFormatter::toVector() const {
		TableFunctors::Accumulator result = partialVector(page,line,lineIsEmpty);
		if(!lineIsEmpty) { result(line); }
		return result.result;
	}
	std::string TableFormatter::toString() const {
		std::vector<std::string> asVector = toVector();
		return std::accumulate(asVector.begin(), asVector.end(), std::string(), TableFunctors::NewLines());
	}
}
