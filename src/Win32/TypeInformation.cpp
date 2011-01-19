#include "TypeInformation.h"

namespace gppUnit{
	std::string demangleTypeName(const std::string& name){
		//name.replace(
		if (name.length()>6) {
			return name.substr(6);
		}
		return name;
	}

}
