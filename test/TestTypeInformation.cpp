#include "src\TypeInformation.h"

#include "AutoRun.h"

#include <typeinfo>


class ClassInGlobalNamespace{};

namespace{
	class ClassInEmptyNamespace{};
}

namespace TestTypeInformation{
	using gppUnit::equals;

	class ClassInNamespace{};
	class Test: public Auto::TestCase{
		void test(){
			confirm.that("TestTypeInformation::ClassInNamespace",equals(gppUnit::demangleTypeName(typeid(ClassInNamespace).name())));
			confirm.that("(anonymous namespace)::ClassInEmptyNamespace",equals(gppUnit::demangleTypeName(typeid(ClassInEmptyNamespace).name())));
			confirm.that("ClassInGlobalNamespace",equals(gppUnit::demangleTypeName(typeid(ClassInGlobalNamespace).name())));
			confirm.that("int",equals(gppUnit::demangleTypeName(typeid(int).name())));
		}
	}GPPUNIT_INSTANCE;
}
