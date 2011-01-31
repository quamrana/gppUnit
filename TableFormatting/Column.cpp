#include "Column.h"

namespace gppUnit {
	std::string Column::toString(size_t requestedWidth) const {
		size_t actualWidth = contents.size();
		std::string result = contents;
		if(requestedWidth > actualWidth) {
			result.insert(result.end(), requestedWidth - actualWidth, ' ');
		}
		return result;
	}
}

