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
		stream(),
		streamIsEmpty(other.streamIsEmpty) {
		stream << other.stream.str();
	}
	Line& Line::operator=(Line const& other) {
		if(this == &other) { return *this; }

		columns = other.columns;
		stream.str(other.stream.str());
		streamIsEmpty = other.streamIsEmpty;

		return *this;
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
	std::string Line::toString() const {
		return std::accumulate(columns.begin(), columns.end(), std::string(), LineFunctors::Accumulator()) + stream.str();
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
		                       LineFunctors::PaddingAccumulator(modifiedSizes.begin())
		                      ) + stream.str();
	}
	void Line::update(std::vector<size_t>& sizes) const {
		pad(sizes);

		std::transform(columns.begin(), columns.end(), sizes.begin(), sizes.begin(), LineFunctors::Update());
	}

	void TableFormatter::tab() {
		*this << ' ';
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
			std::vector<size_t> sizes;
			void operator()(const Line& line) { line.update(sizes); }
		};
		struct Accumulator {
			explicit Accumulator(const std::vector<size_t>& sizes): sizes(sizes) {}
			std::vector<std::string> result;
			std::vector<size_t> sizes;
			void operator()(const Line& line) { result.push_back(line.toString(sizes)); }
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
	TableFormatter& TableFormatter::operator<<(const TableFormatter& table) {
		std::vector<std::string> result = table.toVector();

		std::for_each(result.begin(), result.end(), TableFunctors::UpdateTable(this));

		return *this;
	}

	std::vector<std::string> TableFormatter::toVector() const {
		TableFunctors::Update update = std::for_each(page.begin(), page.end(), TableFunctors::Update());
		if(!lineIsEmpty) { line.update(update.sizes); }

		TableFunctors::Accumulator result = std::for_each(page.begin(), page.end(), TableFunctors::Accumulator(update.sizes));
		if(!lineIsEmpty) { result(line); }
		return result.result;
	}
	std::string TableFormatter::toString() const {
		std::vector<std::string> asVector = toVector();
		return std::accumulate(asVector.begin(), asVector.end(), std::string(), TableFunctors::NewLines());
	}
}
