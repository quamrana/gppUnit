#ifndef PROJECTRUNNER_H_E1CE6833_9AF2_4103_91F0_A9A5AB7F8885
#define PROJECTRUNNER_H_E1CE6833_9AF2_4103_91F0_A9A5AB7F8885

#include "ProjectDescription.h"
#include "TestCase.h"
#include "DataStructures.h"


namespace gppUnit{
	class Notification;
	class MethodTimer;

	class ProjectRunner: public ProjectDescription{
		Notification& notify;
		MethodTimer& timer;
		TestCaseList cases;

		std::vector<ClassData> classData;
		ClassData projectData;

		std::string name() const { return projectData.title; }
		size_t classes() const { return cases.size(); }
		bool hasPassed() const { return projectData.goodReport; }
		size_t results() const { return projectData.results; }
		double run_time() const { return projectData.reportedTime; }

		void call(gppUnit::PrototypeTestCase* testcase);
		void calculateProjectData();
	public:
		ProjectRunner(const std::string& title,
			gppUnit::Notification& notify, 
			gppUnit::MethodTimer& timer,
			const gppUnit::TestCaseList& cases);
		~ProjectRunner();

		bool run();
	};
}
#endif // PROJECTRUNNER_H_E1CE6833_9AF2_4103_91F0_A9A5AB7F8885
