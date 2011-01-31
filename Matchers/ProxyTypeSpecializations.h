#ifndef PROXYTYPESPECIALIZATIONS_H_233A77F5_B2B1_445C_A5CA_FA24D177BE97
#define PROXYTYPESPECIALIZATIONS_H_233A77F5_B2B1_445C_A5CA_FA24D177BE97

#include "ProxyType.h"

#include <sstream>

namespace gppUnit {
	template<>
	struct ProxyTypeConverter<std::stringstream, std::stringstream> {
		typedef std::string conversion_type;
		std::string value;
		explicit ProxyTypeConverter(const std::stringstream& from): value(from.str()) {}
	};

	// Sample Proxy Specializations
	template<> struct ProxyType<int>: ProxyTypeBase<int, long> {};
	template<> struct ProxyType<const char*>: ProxyTypeBase<const char*, std::string> {};
	template<> struct ProxyType<size_t>: ProxyTypeBase<size_t, long> {};
	template<> struct ProxyType<signed char>: ProxyTypeBase<signed char, long> {};
	template<typename T> struct ProxyType<T*>: ProxyTypeBase<void*> {};

}

#endif // PROXYTYPESPECIALIZATIONS_H_233A77F5_B2B1_445C_A5CA_FA24D177BE97
