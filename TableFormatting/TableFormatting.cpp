#include "TableFormatting.h"

#include <numeric>
#include <algorithm>

namespace gppUnit {
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
