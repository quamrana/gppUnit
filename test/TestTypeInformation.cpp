#include "src\TypeInformation.h"

#include "AutoRun.h"

#include <typeinfo>

class ClassInGlobalNamespace{};

namespace{
	class ClassInEmptyNamespace{};
}

namespace TestTypeInformation{
	class ClassInNamespace{};
	class Test: public Auto::TestCase{
		template<typename T>
		std::string demangleTypeName(){}
		void test(){
			confirm.equals("TestTypeInformation::ClassInNamespace",gppUnit::demangleTypeName(typeid(ClassInNamespace).name()));
			confirm.equals("(anonymous namespace)::ClassInEmptyNamespace",gppUnit::demangleTypeName(typeid(ClassInEmptyNamespace).name()));
			confirm.equals("ClassInGlobalNamespace",gppUnit::demangleTypeName(typeid(ClassInGlobalNamespace).name()));
			confirm.equals("int",gppUnit::demangleTypeName(typeid(int).name()));
		}
	}GPPUNIT_INSTANCE;
}
