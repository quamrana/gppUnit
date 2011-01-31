#ifndef COLUMN_H_AC90107C_94A3_4326_87B6_C3FF5A839FB7
#define COLUMN_H_AC90107C_94A3_4326_87B6_C3FF5A839FB7

#include <string>

namespace gppUnit {
	class Column {
		std::string contents;
	public:
		explicit Column(const std::string& str): contents(str) {}
		size_t size() const { return contents.size(); }
		std::string toString() const { return contents; }
		std::string toString(size_t requestedWidth) const;
	};
}

#endif // COLUMN_H_AC90107C_94A3_4326_87B6_C3FF5A839FB7
