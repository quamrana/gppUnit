#ifndef SINGLECLASSRUNNER_H_82EAF649_94D1_44D7_9DF2_379D70E4D05A
#define SINGLECLASSRUNNER_H_82EAF649_94D1_44D7_9DF2_379D70E4D05A

#include "PrivateMethodRunners.h"
#include "TestCaseMethodCallers.h"
#include "PrivateClassContext.h"

namespace Prototype1{
	namespace Internal{
		class SingleClassRunner{
			SetupCaller sr;
			TestCaller tr;
			TeardownCaller tdr;
			MethodRunner runner;
		public:
			SingleClassRunner(ClassContext& context):sr(context.testcase),
				tr(context.testcase),
				tdr(context.testcase),
				runner(context)
			{}
			void runSingle(ClassDescription& singleClass){
				if (runner.run(singleClass,sr))
					runner.run(singleClass,tr);
				runner.run(singleClass,tdr);
			}
		};
	}
}

#endif // SINGLECLASSRUNNER_H_82EAF649_94D1_44D7_9DF2_379D70E4D05A
