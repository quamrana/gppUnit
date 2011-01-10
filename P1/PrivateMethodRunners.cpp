#include "PrivateMethodRunners.h"
#include "PrivateClasses.h"
#include "HiResTimer.h"
#include "TestCaseMethodCallers.h"
#include "AutoTimer.h"

#include "AssertException.h"

namespace Prototype1{
	namespace Internal{

		bool MethodRunner::callFineGrainedMethod(FineGrainedMethodFixture& fixture, TestCaseMethodCaller& caller){
			bool result=false;
			context.StartFineGrainedMethod(fixture);

			try {
				context.timer.timeMethod(caller,fixture);
				result=true;
			} catch (Prototype1::AssertException&) {
				// Exception is ignored because its only job was to
				// unwind the stack to here
			} catch (std::exception& e) {
				reportException(e.what());
			} catch (std::string& e) {
				reportException(e);
			} catch (const char* e) {
				reportException(e);
			} catch (int e) {
				reportException(e);
			} catch (...) {
				reportException("Unknown Exception");
			}

			context.EndFineGrainedMethod();
			return result;
		}

		bool MethodRunner::run(ClassDescription& singleClass, TestCaseMethodCaller& caller){
			FineGrainedMethodFixture fixture(caller.methodName());
			bool result = callFineGrainedMethod(fixture,caller);
			singleClass.add(fixture);
			return result;
		}
	}
}