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
		Line(): streamIsEmpty(true) {}
		Line(const Line&);
		Line& operator=(Line const&);
		void clear();
		//size_t size() const { return columns.size(); }

		template<typename ValueArgument>
		void append(const ValueArgument& str) { stream << str; streamIsEmpty = false; }
		void tab();

		std::string toString() const;
		std::string toString(const std::vector<size_t>& sizes) const;

		void update(std::vector<size_t>& sizes) const;
	};

	class TableFormatter {
	public:
		void clear() {}
		std::string toString() { return ""; }
	};
}

#endif // TABLEFORMATTING_H_108BF9D9_0404_4F82_8E5F_0C16A9C9B355
