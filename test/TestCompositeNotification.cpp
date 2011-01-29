#include "src\CompositeNotification.h"
#include "src\TestResult.h"

#include "AutoRun.h"

#include <sstream>

namespace TestCompositeNotification{
	using gppUnit::equals;

	class TestCompositeUtility: public Auto::TestCase, public gppUnit::Notification{
		virtual void StartProject(const gppUnit::ProjectDescription&){ wasCalled+=1; }
		virtual void EndProject(){ wasCalled+=1; }
		gppUnit::CompositeNotification composite;
	protected:
		void add(){ composite.add(*this); }
		size_t wasCalled;

		void call(Notification& notify){
			notify.StartProject( *(gppUnit::ProjectDescription*)0);
		}
		void whenCalled(){
			call(composite);
		}
		void callEnd(Notification& notify){
			notify.EndProject();
		}
		void whenEndCalled(){
			callEnd(composite);
		}
		void whenAllCalled(){
			gppUnit::Notification* notify=&composite;
			notify->StartProject(*(gppUnit::ProjectDescription*)0);
			notify->StartClass(*(gppUnit::ClassDescription*)0);
			notify->StartMethod(*(gppUnit::MethodDescription*)0);
			notify->Result(gppUnit::TestResult());
			notify->Exception("EX");
			notify->EndMethod();
			notify->EndClass();
			notify->EndProject();

		}
	};
	class NoComponents: public TestCompositeUtility{

		void givenComposite(){
			wasCalled=0;
		}
		void thenNoCallsReceived(){
			confirm.that(wasCalled,equals(0),"thenNoCallsReceived");
		}
		void test(){
			givenComposite();
			whenCalled();
			thenNoCallsReceived();
		}
	}GPPUNIT_INSTANCE;

	class OneComponent: public TestCompositeUtility{

		void givenComposite(){
			wasCalled=0;
			add();
		}
		void thenOneCallReceived(){
			confirm.that(wasCalled,equals(1),"thenOneCallReceived");
		}
		void test(){
			givenComposite();
			whenCalled();
			thenOneCallReceived();
		}
	}GPPUNIT_INSTANCE;

	class TwiceSelf: public TestCompositeUtility{

		void givenComposite(){
			wasCalled=0;
			add();
			add();
		}
		void thenTwoCallsReceived(){
			confirm.that(wasCalled,equals(2),"thenTwoCallsReceived");
		}
		void test(){
			givenComposite();
			whenCalled();
			thenTwoCallsReceived();
		}
	}GPPUNIT_INSTANCE;

	class ThriceSelf: public TestCompositeUtility{

		void givenComposite(){
			wasCalled=0;
			add();
			add();
			add();
		}
		void thenThreeCallsReceived(){
			confirm.that(wasCalled,equals(3),"thenThreeCallsReceived");
		}
		void test(){
			givenComposite();
			whenEndCalled();
			thenThreeCallsReceived();
		}
	}GPPUNIT_INSTANCE;

	class AllMethodsCalled: public TestCompositeUtility{
		std::stringstream collect;

		virtual void StartProject(const gppUnit::ProjectDescription&){collect << "SP.";}
		virtual void StartClass(const gppUnit::ClassDescription&){collect << "SC.";}
		virtual void StartMethod(const gppUnit::MethodDescription&){collect << "SM.";}
		virtual void Result(const gppUnit::TestResult&){collect << "TR.";}
		virtual void Exception(const std::string& what){collect << what << '.';}
		virtual void EndMethod(){collect << "EM.";}
		virtual void EndClass(){collect << "EC.";}
		virtual void EndProject(){collect << "EP.";}

		void givenComposite(){
			collect.str("");
			add();
		}
		void thenAllMethodsCalled(){
			confirm.that(collect.str(),equals("SP.SC.SM.TR.EX.EM.EC.EP."),"thenAllMethodsCalled");
		}
		void test(){
			givenComposite();
			whenAllCalled();
			thenAllMethodsCalled();
		}
	}GPPUNIT_INSTANCE;
}
