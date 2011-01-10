#include "ClassRunner.h"

#include "AssertException.h"

namespace Prototype2{
	bool ClassRunner::callFineGrainedMethod(Prototype1::Internal::FineGrainedMethodFixture& fixture, Prototype1::Internal::TestCaseMethodCaller& caller){
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

	void ClassRunner::run(Prototype1::Internal::ClassDescription& singleClass){
		context.StartClass(singleClass);
		runSingle(singleClass);
		context.EndClass();
	}
	void ClassRunner::runSingle(Prototype1::Internal::ClassDescription& singleClass){
		if (runSetup(singleClass))
		{
			runTest(singleClass);
		}
		runTeardown(singleClass);
	}
	bool ClassRunner::runSetup(Prototype1::Internal::ClassDescription& singleClass){
		return run(singleClass,sr);
	}
	void ClassRunner::runTest(Prototype1::Internal::ClassDescription& singleClass){
		run(singleClass,tr);
	}
	void ClassRunner::runTeardown(Prototype1::Internal::ClassDescription& singleClass){
		run(singleClass,tdr);
	}

	bool ClassRunner::run(Prototype1::Internal::ClassDescription& singleClass, Prototype1::Internal::TestCaseMethodCaller& caller){
		Prototype1::Internal::FineGrainedMethodFixture fixture(caller.methodName());
		bool result = callFineGrainedMethod(fixture,caller);
		singleClass.add(fixture);
		return result;
	}

}
