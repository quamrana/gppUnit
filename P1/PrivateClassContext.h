#ifndef PRIVATECLASSCONTEXT_H_B6725F09_3C87_4AA4_83F0_971C0101E167
#define PRIVATECLASSCONTEXT_H_B6725F09_3C87_4AA4_83F0_971C0101E167

#include "TestCaseForwarder.h"
#include "MethodTimer.h"

namespace Prototype1{
	class Notification;
	class TestCase;
	struct TestResult;
	class ContextSetter;

	namespace Internal{
		class FineGrainedMethodFixture;
		class ClassDescription;

		class ClassContext{
			FineGrainedMethodFixture* fixture;
			long resultCount;
		public:
			Notification& notify;
			MethodTimer& timer;
			TestCaseForwarder testcase;

			void StartClass(const ClassDescription& );
			void StartFineGrainedMethod(FineGrainedMethodFixture& fixture);
			void Result(const TestResult& result);
			void EndFineGrainedMethod();
			void EndClass();


			void setContextOn(ContextSetter& setter);
			ClassContext(Notification& notify, MethodTimer& timer):fixture(0),
				resultCount(0),
				notify(notify),
				timer(timer),
				testcase()
			{}
		};
	}
}

#endif // PRIVATECLASSCONTEXT_H_B6725F09_3C87_4AA4_83F0_971C0101E167
