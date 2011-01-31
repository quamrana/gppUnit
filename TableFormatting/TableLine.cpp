#include "TableLine.h"

#include <numeric>
#include <algorithm>

namespace gppUnit {
	TableLine::TableLine(const TableLine& other): columns(other.columns),
		stream(),
		streamIsEmpty(other.streamIsEmpty) {
		stream << other.stream.str();
	}
	TableLine& TableLine::operator=(TableLine const& other) {
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
		Column column(stream.str());
		columns.push_back(column);
		clearStream();
	}

	namespace LineFunctors {
		struct Accumulator {
			std::string operator()(const std::string& value, const Column& column) {
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
			size_t operator()(const Column& column, size_t size) {
				size_t other = column.size();
				return (size >= other) ? size : other;
			}
		};
	}
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

		return std::accumulate(columns.begin(),
		                       columns.end(),
		                       std::string(),
		                       LineFunctors::PaddingAccumulator(modifiedSizes.begin())
		                      ) + stream.str();
	}
	void TableLine::update(std::vector<size_t>& sizes) const {
		pad(sizes);

		std::transform(columns.begin(), columns.end(), sizes.begin(), sizes.begin(), LineFunctors::Update());
	}

}