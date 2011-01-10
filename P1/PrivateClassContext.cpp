#include "PrivateClassContext.h"
#include "Notification.h"
#include "TestResult.h"
#include "PrivateMethodRunners.h"
#include "ContextSetter.h"
#include "PrivateClasses.h"
#include "RealTestCase.h"

namespace Prototype1{
	namespace Internal{
		void ClassContext::StartClass(const ClassDescription& description){
			PrototypeTestCase* testCase=description.getTestCase();
			setContextOn(*testCase);
			testcase.set(testCase);
			notify.StartClass(description);
		}
		void ClassContext::StartFineGrainedMethod(FineGrainedMethodFixture& aFixture){
			fixture=&aFixture;
			resultCount=0;
			notify.StartFineGrainedMethod(*fixture);
		}
		void ClassContext::Result(const TestResult& result){
			resultCount+=1;
			notify.Result(result);
		}
		void ClassContext::EndFineGrainedMethod(){
			if(fixture){
				fixture->reportResultCount(resultCount);
			}
			fixture=0;
			notify.EndFineGrainedMethod();
		}
		void ClassContext::EndClass(){
			notify.EndClass();
		}
		void ClassContext::setContextOn(ContextSetter& setter){
			setter.setContext(this);
		}

	}
}