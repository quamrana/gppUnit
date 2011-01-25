#ifndef TABLEFORMATTING_H_108BF9D9_0404_4F82_8E5F_0C16A9C9B355
#define TABLEFORMATTING_H_108BF9D9_0404_4F82_8E5F_0C16A9C9B355

#include <string>
#include <vector>
#include <sstream>

namespace gppUnit {
	class Column {
		std::string contents;
	public:
		explicit Column(const std::string& str): contents(str) {}
		size_t size() const { return contents.size(); }
		std::string toString() const { return contents; }
		std::string toString(size_t requestedWidth) const;
	};

	class Line {
		std::vector<Column> columns;
		std::stringstream stream;
		bool streamIsEmpty;

		void pad(std::vector<size_t>& sizes) const ;
		void clearStream();

	public:
		Line(): columns(), stream(), streamIsEmpty(true) {}
		Line(const Line&);
		Line& operator=(Line const&);
		void clear();
		size_t size() const { return columns.size(); }

		template<typename ValueArgument>
		void append(const ValueArgument& str) { stream << str; streamIsEmpty = false; }
		void tab();

		std::string toString() const;
		std::string toString(const std::vector<size_t>& sizes) const;

		void update(std::vector<size_t>& sizes) const;
	};

	class TableFormatter {
		std::vector<Line> page;
		Line line;
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
