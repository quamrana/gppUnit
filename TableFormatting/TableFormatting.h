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
#ifndef TABLEFORMATTING_H_108BF9D9_0404_4F82_8E5F_0C16A9C9B355
#define TABLEFORMATTING_H_108BF9D9_0404_4F82_8E5F_0C16A9C9B355

#include <string>

#include "TableLine.h"

namespace gppUnit {
	struct patch_t;

	class TableFormatter {
		std::vector<std::string> prevPages;
		std::vector<TableLine> page;
		std::vector<size_t> summarySizes;
		TableLine line;
		bool lineIsEmpty;

		friend TableFormatter& tab(TableFormatter& table);
		friend TableFormatter& endl(TableFormatter& table);
		void tab();
		void endLine();
		void clearLine();
		std::vector<std::string> partialVector(std::vector<size_t>& sizes) const;
		void streamSpareLine(const TableLine&, size_t, size_t);
	public:
		TableFormatter();
		void clear() { clearLine(); page.clear(); }
		size_t lineSize() const { return line.size(); }
		size_t indentSize() const { return summarySizes.size(); }
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
		TableFormatter& operator<<(const patch_t& patch);

		TableFormatter& patch(const TableFormatter& table);

		std::vector<std::string> toVector() const;
		std::string toString() const ;
	};
	// Manipulators for TableFormatter
	inline TableFormatter& endl(TableFormatter& table) { table.endLine(); return table; }
	inline TableFormatter& tab(TableFormatter& table) { table.tab(); return table; }

	struct patch_t {
		explicit patch_t(const TableFormatter& table): table(table) {}
		const TableFormatter& table;
	};

	inline TableFormatter& TableFormatter::operator<<(const patch_t& patch) {
		this->patch(patch.table);
		return *this;
	}

	inline patch_t patch(const TableFormatter& table) { return patch_t(table); }

}

#endif // TABLEFORMATTING_H_108BF9D9_0404_4F82_8E5F_0C16A9C9B355
