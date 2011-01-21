#include "src\TypeInformation.h"

namespace gppUnit{
	void replaceQuotesWithParentheses(std::string& name);
}

#include "AutoRun.h"


namespace TestTypeInformation{
	class TestQuotesToParentheses: public Auto::TestCase{
		template<typename T>
		std::string demangleTypeName(){}
		void test(){
			std::string typicalName="`anonymous namespace'::";
			gppUnit::replaceQuotesWithParentheses(typicalName);
			confirm.equals("(anonymous namespace)::",typicalName);
		}
	}GPPUNIT_INSTANCE;
}
