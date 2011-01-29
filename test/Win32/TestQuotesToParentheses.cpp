#include "src\TypeInformation.h"

namespace gppUnit{
	void replaceQuotesWithParentheses(std::string& name);
}

#include "AutoRun.h"


namespace TestTypeInformation{
	using gppUnit::equal_to;

	class TestQuotesToParentheses: public Auto::TestCase{
		template<typename T>
		std::string demangleTypeName(){}
		void test(){
			std::string typicalName="`anonymous namespace'::";
			gppUnit::replaceQuotesWithParentheses(typicalName);
			confirm.that(typicalName,equal_to("(anonymous namespace)::"));
		}
	}GPPUNIT_INSTANCE;
}
