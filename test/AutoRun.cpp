#include "MethodTimer.h"
#include "TimeReport.h"
#include "TestCaseMethodCallers.h"
#include "PrivateClassContext.h"
#include "Notification.h"
#include "ProjectDescription.h"
#include "ProjectFixture.h"
#include "FineGrainedMethodDescription.h"
#include "ClassDescription.h"
#include "AutoTest.h"
#include "AutoTimer.h"

#include "TestResult.h"

#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace Prototype1;
using Prototype1::Internal::MethodCaller;
using Prototype1::Internal::ClassContext;


class MainNotifier: public Notification{
	const ProjectDescription* project;
	const ClassDescription* classDesc;
	bool classShown;
	const FineGrainedMethodDescription* method;
	bool finalResult;
	std::stringstream out;
	virtual void StartProject(const ProjectDescription& description){
		out << "Start Project: " << description.name() << std::endl;
		out << "Number of Classes: " << description.numClasses() << std::endl;
		project=&description;
		finalResult=true;
	}
	virtual void StartClass(const ClassDescription& description){
		//out << " Start Class: " << description.name() << std::endl;
		classDesc=&description;
		classShown=false;
	}
	virtual void StartFineGrainedMethod(const FineGrainedMethodDescription& description){
		//out << "  Start Method: " << description.name() << std::endl;
		method=&description;
	}
	void ShowClass(){
		if(!classShown){
			out << " In Class: " << classDesc->name() << std::endl;
			classShown=true;
		}
	}
	void Show(const std::string output){ out << "     " << output << std::endl; }
	virtual void Result(const TestResult& result){
		if (!result.result){
			ShowClass();
			out << "   Test Failed!" << std::endl;
			out << "    Message: " << result.message << std::endl;
			std::for_each(result.description.begin(),result.description.end(),
				std::bind1st(
					std::mem_fun(&MainNotifier::Show),
					this
				)
			);

			finalResult=false;
		}
	}
	virtual void Exception(const std::string& what){
		ShowClass();
		out << "   Exception: " << what << std::endl;
	}

	virtual void EndFineGrainedMethod(){ 
		//out << "  End Method, time:" << method->run_time() << " results:" << method->results() << std::endl; 
	}
	virtual void EndClass(){ 
		//out << " End Class, time:" << classDesc->run_time() << " results:" << classDesc->results() << std::endl; 
	}
	virtual void EndProject(){ 
		out << "End Project" <<  std::endl; 
		out << " results:" << project->results() << std::endl; 
		out << " runtime:" << project->run_time() << std::endl; 
		out << " elapsed time:" << project->elapsed_time() << std::endl; 
	}
public:
	void printOutput(std::ostream& output){ output << out.str(); }
	bool Result(){ return finalResult; }
}notifier;

class DefaultMethodTimer: public MethodTimer{
	void timeMethod(MethodCaller& caller, TimeReport& report){
		AutoTimer timer(report);
		caller.forward();
	}
}timer;

ClassContext context(notifier,timer);

bool DoAutoRun(const char* title)
{
	ProjectFixture fixture;
	fixture.run(title,Auto::autoTests(),context);
	notifier.printOutput(std::cout);
	return notifier.Result();
}