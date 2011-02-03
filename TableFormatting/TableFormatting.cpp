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
		line.tab();
	}
	void TableFormatter::endLine() {
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
			explicit Update(std::vector<size_t>& sizes): sizes(sizes) {}
			std::vector<size_t>& sizes;
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
			void operator()(const TableLine& line) {
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

	std::vector<std::string> TableFormatter::partialVector(std::vector<size_t>& sizes) const {
		TableFunctors::Update update = std::for_each(page.begin(), page.end(), TableFunctors::Update(sizes));
		if(!lineIsEmpty) { line.update(update.sizes); }

		return std::for_each(page.begin(), page.end(), TableFunctors::Accumulator(update.sizes)).result;
	}

	TableFormatter& TableFormatter::operator<<(const TableFormatter& table) {
		std::vector<std::string> result = partialVector(summarySizes);
		std::copy(result.begin(), result.end(), back_inserter(prevPages));
		page.clear();
		// TODO: Limit sizes
		//size_t lsize=line.size();
		//size_t ssize=summarySizes.size();
		//summarySizes.erase(

		std::for_each(table.page.begin(), table.page.end(), TableFunctors::UpdateTable(this));
		if (!table.line.isEmpty()) {
			(*this) << table.line;
			endLine();
		}
		return *this;
	}

	TableFormatter& TableFormatter::patch(TableFormatter& table) {
		std::vector<TableLine>::iterator it = table.page.begin(), end = table.page.end();

		line.patch(*it++);
		endLine();

		std::copy(it, end, back_inserter(page));

		return *this;
	}

	std::vector<std::string> TableFormatter::toVector() const {
		std::vector<size_t> sizes=summarySizes;
		std::vector<std::string> result = partialVector(sizes);

		// TODO: this is the same as Accumulator.  Refactor?
		if(!lineIsEmpty) { result.push_back(line.toString(sizes)); }

		std::vector<std::string> allLines;
		std::copy(prevPages.begin(), prevPages.end(), back_inserter(allLines));
		std::copy(result.begin(), result.end(), back_inserter(allLines));

		return allLines;
	}
	std::string TableFormatter::toString() const {
		std::vector<std::string> asVector = toVector();
		return std::accumulate(asVector.begin(), asVector.end(), std::string(), TableFunctors::NewLines());
	}
}
