#include "src\Notification.h"

#include "AutoRun.h"

namespace gppUnit{
	class CompositeNotification: public Notification{
	};
}

namespace {
	class Test: public Auto::TestCase, public gppUnit::Notification{
		gppUnit::CompositeNotification composite;
		bool wasCalled;

		virtual void StartProject(const gppUnit::ProjectDescription&){ wasCalled=true; }

		void givenComposite(){
			wasCalled=false;
		}
		void whenCalled(){
			composite.StartProject( *(gppUnit::ProjectDescription*)0);
		}
		void thenNoCallsReceived(){
			confirm.isFalse(wasCalled,"thenNoCallsReceived");
		}
		void test(){
			givenComposite();
			whenCalled();
			thenNoCallsReceived();
		}
	}GPPUNIT_INSTANCE;
}
