#ifndef TABLEFORMATTING_H_108BF9D9_0404_4F82_8E5F_0C16A9C9B355
#define TABLEFORMATTING_H_108BF9D9_0404_4F82_8E5F_0C16A9C9B355

#include <string>
#include <vector>
#include <sstream>

#include "TableLine.h"

namespace gppUnit {
	class TableFormatter {
		std::vector<TableLine> page;
		TableLine line;
		bool lineIsEmpty;

		friend TableFormatter& tab(TableFormatter& table);
		friend TableFormatter& endl(TableFormatter& table);
		void tab();
		void endLine();
		void clearLine();
	public:
		TableFormatter(): page(), line(), lineIsEmpty(true) {}
		void clear() { clearLine(); page.clear(); }
		size_t lineSize() { return line.size(); }
		template<typename ValueArgument>
		TableFormatter& operator<<(const ValueArgument& str) {
			line.append(str);
			lineIsEmpty = false;
			return *this;
		}
		TableFormatter& operator<<(const TableFormatter& table);
		TableFormatter& operator<<(TableFormatter & (*FunctionPointer)(TableFormatter&)) {
			return ((*FunctionPointer)(*this));
		}

		std::vector<std::string> toVector() const;
		std::string toString() const ;
	};
	// Manipulators for TableFormatter
	inline TableFormatter& endl(TableFormatter& table) { table.endLine(); return table; }
	inline TableFormatter& tab(TableFormatter& table) { table.tab(); return table; }
}

#endif // TABLEFORMATTING_H_108BF9D9_0404_4F82_8E5F_0C16A9C9B355
