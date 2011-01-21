#include "ClassRunner.h"
#include "Notification.h"
#include "TypeInformation.h"

#include "Helpers.h"

#include <numeric>
#include <typeinfo>

namespace gppUnit{
	MethodData ClassRunner::callMethod(TestCaseMethodCaller& method){
		MethodResult desc(method,notify,timer);

		desc.protectMethod();

		return desc.methodSummary();
	}
	bool ClassRunner::add(const MethodData& data){ methodData.push_back(data); return data.goodReport; }
	bool ClassRunner::run(TestCaseMethodCaller* method){
		return add(callMethod(*method));
	}

	void ClassRunner::runMethods(){
		if (setup())
		{
			test();
		}
		teardown();
	}
		void ClassRunner::calculateClassData(){
			classData.results=std::accumulate(methodData.begin(),methodData.end(),long(),Results<MethodData>());
			classData.reportedTime=std::accumulate(methodData.begin(),methodData.end(),double(),RunTime<MethodData>());
		}
		ClassRunner::ClassRunner(Notification& notify, 
			PrototypeTestCase& testcase,
			MethodTimer& timer):notify(notify),
			testcase(testcase),
			timer(timer),
			setup(testcase,*this),
			test(testcase,*this),
			teardown(testcase,*this),
			classData(demangleTypeName(typeid(testcase).name()))
		{
			notify.StartClass(*this);
		}
		ClassRunner::~ClassRunner(){ notify.EndClass(); }

}
