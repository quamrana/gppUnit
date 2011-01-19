#include "TypeInformation.h"

#include <cxxabi.h>
#include <memory.h>

namespace gppUnit{
	std::string demangleTypeName(const std::string& name){
		size_t size;
		int status;
		char* demangled = abi::__cxa_demangle(name.c_str(), NULL, &size, &status);
		if (demangled) {
      		std::string result(demangled);
      		// TODO: discover and fix leak
			//free(demangled);
			return result;
		}
		return name;
	}

}
