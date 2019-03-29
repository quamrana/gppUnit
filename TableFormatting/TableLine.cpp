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
#include "TableLine.h"

#include <numeric>
#include <algorithm>

namespace gppUnit {
	TableLine::TableLine(const TableLine& other): columns(other.columns),
		stream(other.stream.str()),
		streamIsEmpty(other.streamIsEmpty) {
	}
	TableLine& TableLine::operator=(const TableLine& other) {
		if(this == &other) { return *this; }

		columns = other.columns;
		stream.str(other.stream.str());
		streamIsEmpty = other.streamIsEmpty;

		return *this;
	}

	void TableLine::clearStream() {
		stream.str("");
		streamIsEmpty = true;
	}
	void TableLine::clear() {
		columns.clear();
		clearStream();
	}
	void TableLine::tab() {
		//if (!streamIsEmpty) {
		Column column(stream.str());
		columns.push_back(column);
		clearStream();
		//}
	}
	void TableLine::append(const TableLine& line) {
		std::vector<Column>::const_iterator it = line.columns.begin(), end = line.columns.end();
		if(!streamIsEmpty) {
			stream << (*it++).toString();
			tab();
		}
		for(; it != end; ++it) {
			columns.push_back(*it);
		}
		if(!line.streamIsEmpty) {
			append(line.stream.str());
		}
	}

	namespace LineFunctors {
		struct Accumulator {
			std::string operator()(const std::string& value, const Column& column) const {
				return value + column.toString();
			}
		};
		struct PaddingAccumulator {
			explicit PaddingAccumulator(std::vector<size_t>::const_iterator it): it(it) {}
			std::vector<size_t>::const_iterator it;
			std::string operator()(const std::string& value, const Column& column) {
				return value + column.toString(*it++);
			}
		};
		struct Update {
			size_t operator()(const Column& column, size_t size) const {
				size_t other = column.size() + 1;
				return (size >= other) ? size : other;
			}
		};
	}
	/*
		void TableLine::patch(const TableLine& line) {
			//if (!streamIsEmpty)
			//	tab();
			std::copy(line.columns.begin(), line.columns.end(), back_inserter(columns));
			if(!line.streamIsEmpty) {
				//Column column(line.stream.str());
				//columns.push_back(column);
				stream.str(line.stream.str());
			}
		}
	*/
	std::string TableLine::toString() const {
		return std::accumulate(columns.begin(), columns.end(), std::string(), LineFunctors::Accumulator()) + stream.str();
	}
	void TableLine::pad(std::vector<size_t>& sizes) const {
		size_t target_size = columns.size() + (streamIsEmpty ? 0 : 1);

		while(sizes.size() < target_size) { sizes.push_back(0); }
	}
	std::string TableLine::toString(const std::vector<size_t>& sizes) const {
		std::vector<size_t> modifiedSizes = sizes;
		pad(modifiedSizes);

		std::string termination = stream.str();

		// Avoid padding last column with extra spaces
		if(termination.empty() && !columns.empty()) {
			size_t index = columns.size();
			modifiedSizes[index - 1] = 0;
		}

		return std::accumulate(columns.begin(),
		                       columns.end(),
		                       std::string(),
		                       LineFunctors::PaddingAccumulator(modifiedSizes.begin())
		                      ) + termination;
	}
	void TableLine::update(std::vector<size_t>& sizes) const {
		pad(sizes);

		std::transform(columns.begin(), columns.end(), sizes.begin(), sizes.begin(), LineFunctors::Update());
	}
}
