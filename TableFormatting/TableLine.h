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

		template<typename ValueArgument>
		void append(const ValueArgument& str) { stream << str; streamIsEmpty = false; }
		void tab();

		std::string toString() const;
		std::string toString(const std::vector<size_t>& sizes) const;

		void update(std::vector<size_t>& sizes) const;
	};
}

#endif // TABLELINE_H_8DC577D3_F15F_49BA_95F6_36C427673947
