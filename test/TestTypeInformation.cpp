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
			confirm.that(gppUnit::demangleTypeName(typeid(ClassInNamespace).name()),equals("TestTypeInformation::ClassInNamespace"));
			confirm.that(gppUnit::demangleTypeName(typeid(ClassInEmptyNamespace).name()),equals("(anonymous namespace)::ClassInEmptyNamespace"));
			confirm.that(gppUnit::demangleTypeName(typeid(ClassInGlobalNamespace).name()),equals("ClassInGlobalNamespace"));
			confirm.that(gppUnit::demangleTypeName(typeid(int).name()),equals("int"));
		}
	}GPPUNIT_INSTANCE;
}
