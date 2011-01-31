#ifndef PROXYTYPE_H_EA518192_C981_4852_9876_7525B8F209C8
#define PROXYTYPE_H_EA518192_C981_4852_9876_7525B8F209C8

namespace gppUnit {
	template<typename T, typename U>
	struct ProxyTypeConverter {
		typedef U conversion_type;
		U value;
		explicit ProxyTypeConverter(const T& from): value(from) {}
	};
	//template<>
	//struct ProxyTypeConverter<std::stringstream, std::stringstream> {
	//	typedef std::string conversion_type;
	//	std::string value;
	//	explicit ProxyTypeConverter(const std::stringstream& from): value(from.str()) {}
	//};

	template<typename T, typename U = T>
	struct ProxyTypeBase: ProxyTypeConverter<T, U> {
		typedef T original_type;

		explicit ProxyTypeBase(const original_type& from): ProxyTypeConverter<T, U>(from) {}

		static ProxyTypeBase<T, U> create(const original_type& from) { return ProxyTypeBase(from); }

	private:
		ProxyTypeBase() {}
	};


	// Define a degenerate derived class
	template<typename T>
	struct ProxyType: ProxyTypeBase<T> {};

	template<typename T>
	typename ProxyType<T>::conversion_type ProxyValue(const T& value) { return ProxyType<T>::create(value).value; }

	template<typename T, size_t size>
	typename ProxyType<const T*>::conversion_type ProxyValue(const T(&value)[size]) { return ProxyType<const T*>::create(value).value; }

	//// Sample Proxies
	//template<> struct ProxyType<int>: ProxyTypeBase<int, long> {};
	//template<> struct ProxyType<const char*>: ProxyTypeBase<const char*, std::string> {};
	//template<> struct ProxyType<size_t>: ProxyTypeBase<size_t, long> {};
	//template<> struct ProxyType<signed char>: ProxyTypeBase<signed char, long> {};
	//template<typename T> struct ProxyType<T*>: ProxyTypeBase<void*> {};
}

#endif // PROXYTYPE_H_EA518192_C981_4852_9876_7525B8F209C8
