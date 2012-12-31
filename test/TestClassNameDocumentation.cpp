#include "src\Notification.h"
#include "src\ClassDescription.h"

#include <vector>
#include <sstream>

namespace gppUnit{
    class ClassDocumentation: public Notification{
        typedef std::vector<std::string> vecstr;
		void StartClass(const ClassDescription& aClass) {
            collect.push_back(aClass.name());
        }
        void format(const std::string& spacing, vecstr::const_iterator it,std::string head, std::stringstream& str){
            for(;it!=collect.end();++it){
                std::string tail=*it;
                std::string item=tail.substr(head.size());
                str << spacing << item << std::endl;
            }
        }
    protected:
        vecstr collect;
    public:
        std::string getFormattedDocumentation(){
            std::stringstream str;
            std::string spacing="";
            std::string head=collect.front();
            std::string::size_type jt=head.find("::");
            if(jt!=std::string::npos){
                head=head.substr(0,jt);
                str << spacing << head << std::endl;
                spacing+=' ';
                head+="::";
            } else{
                head="";
            }
            format(spacing,collect.begin(),head,str);
            return str.str();
        }
    };
}

#include "src\AutoRunner.h"

#include "TestUtilities.h"

namespace {
    class NopTestCase: public Utilities::MockTestCase{
        void test(){}
    };
}

class GCase1: public NopTestCase{
} gc1;
class GCase2: public NopTestCase{
} gc2;

namespace TestClassNameDocumentation{
	using gppUnit::equals;

    class Case1: public NopTestCase{
    } c1;
    class Case2: public NopTestCase{
    } c2;

    class MockDoc: public gppUnit::ClassDocumentation{
    //public:
    //    using gppUnit::ClassDocumentation::collect;
    };
	class TestDocumentation: public Auto::TestCase{
        gppUnit::AutoRunner runner;
        MockDoc doc;

        gppUnit::TestCaseList cases;

        void setup(){
            runner << doc;
        }
    protected:
        void push_back(gppUnit::PrototypeTestCase& tc){
            cases.push_back(&tc);
        }
        void whenRun(){
            runner.run(cases);
        }
        void thenDocumentationIs(const std::string& expected){
            confirm.that(doc.getFormattedDocumentation(),equals(expected),__FUNCTION__);
        }
	};
	class GlobalTestCases: public TestDocumentation{
        void givenProject(){
            push_back(gc1);
            push_back(gc2);
        }
		void test(){
			givenProject();
            whenRun();
            thenDocumentationIs(
                "GCase1\n"
                "GCase2\n"
                );
		}
	}GPPUNIT_INSTANCE;
	class SingleNamespacedTestCases: public TestDocumentation{
        void givenProject(){
            push_back(c1);
            push_back(c2);
        }
		void test(){
			givenProject();
            whenRun();
            thenDocumentationIs(
                "TestClassNameDocumentation\n"
                " Case1\n"
                " Case2\n"
                );
		}
	}GPPUNIT_INSTANCE;
}
