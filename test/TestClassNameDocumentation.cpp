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
    protected:
        vecstr collect;
    public:
        std::string getFormattedDocumentation(){
            std::stringstream str;
            std::string spacing;
            std::string head;
            std::string tail;

            vecstr::const_iterator it=collect.begin();
            vecstr::const_iterator end=collect.end();


            for(;;){
                if(tail.empty()){
                    if (it==end){
                        return str.str();
                    } else {
                        tail=*it++;
                    }
                }
                std::string::size_type jt=tail.find(head);
                if(jt==0){
                    tail=tail.substr(head.size());
                }
                
                for(;;){
                std::string::size_type ct=tail.find("::");
                if(ct!=std::string::npos){
                    std::string nexthead=tail.substr(0,ct);
                    std::string tmphead=nexthead+"::";
                    tail=tail.substr(tmphead.size());
                    head+=tmphead;
                    str << spacing << nexthead << std::endl;
                    spacing+=' ';
                    // stack head
                } else{
                    break;
                }
                }
                str << spacing << tail << std::endl;
                tail="";
            }
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

    namespace NextLevel{
        class Case1: public NopTestCase{
        } nc1;
        class Case2: public NopTestCase{
        } nc2;
    }
    using namespace NextLevel;

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
	class NextLevelNamespacedTestCases: public TestDocumentation{
        void givenProject(){
            push_back(nc1);
            push_back(nc2);
        }
		void test(){
			givenProject();
            whenRun();
            thenDocumentationIs(
                "TestClassNameDocumentation\n"
                " NextLevel\n"
                "  Case1\n"
                "  Case2\n"
                );
		}
	}GPPUNIT_INSTANCE;
	class IncreasingNamespacedTestCases: public TestDocumentation{
        void givenProject(){
            push_back(gc1);
            push_back(gc2);
            push_back(c1);
            push_back(c2);
            push_back(nc1);
            push_back(nc2);
        }
		void test(){
			givenProject();
            whenRun();
            thenDocumentationIs(
                "GCase1\n"
                "GCase2\n"
                "TestClassNameDocumentation\n"
                " Case1\n"
                " Case2\n"
                " NextLevel\n"
                "  Case1\n"
                "  Case2\n"
                );
		}
	}GPPUNIT_INSTANCE;
}
