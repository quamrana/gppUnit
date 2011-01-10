#ifndef CLASSRUNNER_H_74FCF358_5A78_41A1_B7C6_F04E17D61476
#define CLASSRUNNER_H_74FCF358_5A78_41A1_B7C6_F04E17D61476

#include "PrivateClasses.h"
#include "PrivateClassContext.h"

namespace Prototype2{
	class ClassRunner: public Prototype1::ClassRunner{
		Prototype1::Internal::ClassContext& context;
		Prototype1::Internal::SetupCaller sr;
		Prototype1::Internal::TestCaller tr;
		Prototype1::Internal::TeardownCaller tdr;

		template<typename T>
		void reportException(T what){
			std::stringstream strm;
			strm << what;
			context.notify.Exception(strm.str());
		}
		bool callFineGrainedMethod(Prototype1::Internal::FineGrainedMethodFixture& fixture, Prototype1::Internal::TestCaseMethodCaller& caller);
		bool run(Prototype1::Internal::ClassDescription& singleClass, Prototype1::Internal::TestCaseMethodCaller& caller);

		bool runSetup(Prototype1::Internal::ClassDescription& singleClass);
		void runTest(Prototype1::Internal::ClassDescription& singleClass);
		void runTeardown(Prototype1::Internal::ClassDescription& singleClass);
		void runSingle(Prototype1::Internal::ClassDescription& singleClass);
	public:
		explicit ClassRunner(Prototype1::Internal::ClassContext& context):context(context),
			sr(context.testcase),
			tr(context.testcase),
			tdr(context.testcase)
		{}
		void run(Prototype1::Internal::ClassDescription& singleClass);
	};
	template<>
	inline void ClassRunner::reportException<const std::string&>(const std::string& what){
		context.notify.Exception(what);
	}
}

#endif // CLASSRUNNER_H_74FCF358_5A78_41A1_B7C6_F04E17D61476
