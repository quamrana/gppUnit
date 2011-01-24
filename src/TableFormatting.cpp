#include "TableFormatting.h"

#include <numeric>
#include <algorithm>

namespace gppUnit {
	std::string Column::toString(size_t requestedWidth) const {
		size_t actualWidth = contents.size();
		std::string result = contents;
		if(requestedWidth > actualWidth) {
			result.insert(result.end(), requestedWidth - actualWidth, ' ');
		}
		return result;
	}

	Line::Line(const Line& other): columns(other.columns),
		streamIsEmpty(other.streamIsEmpty) {
		stream << other.stream.str();
	}
	void Line::clearStream() {
		stream.str("");
		streamIsEmpty = true;
	}
	void Line::clear() {
		columns.clear();
		clearStream();
	}
	void Line::tab() {
		Column column(stream.str());
		columns.push_back(column);
		clearStream();
	}

	namespace Functors {
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
	std::string Line::toString() const {
		return std::accumulate(columns.begin(), columns.end(), std::string(), Functors::Accumulator()) + stream.str();
	}
	void Line::pad(std::vector<size_t>& sizes) const {
		size_t target_size = columns.size() + (streamIsEmpty ? 0 : 1);

		while(sizes.size() < target_size) { sizes.push_back(0); }
	}
	std::string Line::toString(const std::vector<size_t>& sizes) const {
		std::vector<size_t> modifiedSizes = sizes;
		pad(modifiedSizes);

		return std::accumulate(columns.begin(),
		                       columns.end(),
		                       std::string(),
		                       Functors::PaddingAccumulator(modifiedSizes.begin())
		                      ) + stream.str();
	}
	void Line::update(std::vector<size_t>& sizes) const {
		pad(sizes);

		std::transform(columns.begin(), columns.end(), sizes.begin(), sizes.begin(), Functors::Update());
	}
}
