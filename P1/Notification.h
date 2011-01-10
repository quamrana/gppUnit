#ifndef NOTIFICATION_H_3B31E9B5_B12D_4F3D_B4BC_44D3DAC4C624
#define NOTIFICATION_H_3B31E9B5_B12D_4F3D_B4BC_44D3DAC4C624

#include <string>

namespace Prototype1{

	class ProjectDescription;
	class ClassDescription;
	class FineGrainedMethodDescription;
	struct TestResult;

	class Notification{
	public:
		virtual void StartProject(const ProjectDescription& ){}
		virtual void StartClass(const ClassDescription& ){}
		virtual void StartFineGrainedMethod(const FineGrainedMethodDescription& ){}
		virtual void Result(const TestResult&){}
		virtual void Exception(const std::string& /* what */){}
		virtual void EndFineGrainedMethod(){}
		virtual void EndClass(){}
		virtual void EndProject(){}
	};
}

#endif // NOTIFICATION_H_3B31E9B5_B12D_4F3D_B4BC_44D3DAC4C624
