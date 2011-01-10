#ifndef PRIVATEMETHODRUNNERS_H_17C47048_503F_457D_A7B3_B50728C78D28
#define PRIVATEMETHODRUNNERS_H_17C47048_503F_457D_A7B3_B50728C78D28

#include "Notification.h"
#include "FineGrainedMethodDescription.h"
#include "PrivateClassContext.h"
#include "TimeReport.h"

#include <sstream>

namespace Prototype1{
	namespace Internal{

		class TestCaseMethodCaller;
		class ClassDescription;

		class FineGrainedMethodFixture: public FineGrainedMethodDescription, public TimeReport{
			std::string title;
			double time;
			long resultCount;

			std::string name() const { return title; }
			double run_time() const { return time; }
			long results() const { return resultCount; }
		public:
			explicit FineGrainedMethodFixture(const std::string& name):title(name),time(0),resultCount(0){}
			void reportTime(double run_time){ time=run_time; }
			void reportResultCount(long count){ resultCount=count; }
		};

		class MethodRunner{
			ClassContext& context;

			template<typename T>
			void reportException(T what){
				std::stringstream strm;
				strm << what;
				context.notify.Exception(strm.str());
			}
			bool callFineGrainedMethod(FineGrainedMethodFixture& fixture, TestCaseMethodCaller& caller);
		public:
			explicit MethodRunner(ClassContext& context):context(context){}
			bool run(ClassDescription& singleClass, TestCaseMethodCaller& caller);
		};
		template<>
		inline void MethodRunner::reportException<const std::string&>(const std::string& what){
			context.notify.Exception(what);
		}
	}
}

#endif // PRIVATEMETHODRUNNERS_H_17C47048_503F_457D_A7B3_B50728C78D28
