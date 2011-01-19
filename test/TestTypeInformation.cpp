#include "src\TypeInformation.h"

#include "AutoRun.h"

#include <typeinfo>

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
			//confirm.equals("ClassInEmptyNamespace",gppUnit::demangleTypeName(typeid(ClassInEmptyNamespace).name()));
			confirm.equals("int",gppUnit::demangleTypeName(typeid(int).name()));
		}
	}GPPUNIT_INSTANCE;
}
