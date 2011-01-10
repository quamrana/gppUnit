#ifndef PRIVATECLASSES_H_AF48FD94_9DB7_40F6_A19F_6999193E6752
#define PRIVATECLASSES_H_AF48FD94_9DB7_40F6_A19F_6999193E6752

#include "ProjectDescription.h"
#include "ClassDescription.h"
#include "ProjectFixture.h"
#include "PrivateMethodRunners.h"
#include "SingleClassRunner.h"

#include <vector>
#include <numeric>

namespace Prototype1{
	namespace Internal{
		typedef std::vector<FineGrainedMethodFixture> MethodDescriptions;
		class ClassDescription: public Prototype1::ClassDescription{
			PrototypeTestCase* testcase;
			MethodDescriptions descriptions;
			std::string name() const ;
			double run_time() const ;
			long results() const ;
		public:
			ClassDescription(PrototypeTestCase* testcase):testcase(testcase){}
			PrototypeTestCase* getTestCase() const { return testcase; }
			void add(FineGrainedMethodFixture& description){ descriptions.push_back(description); }
		};
		typedef std::vector<ClassDescription> ClassList;
	}
	class ClassRunner{
	public:
		virtual void run(Internal::ClassDescription& singleClass)=0;
	};

	namespace Internal{
		class MethodCaller;
		class FineGrainedMethodFixture;

		class ClassRunner: public Prototype1::ClassRunner{
			ClassContext& context;

			SingleClassRunner scRunner;
		public:
			explicit ClassRunner(ClassContext& context):context(context),
				scRunner(context)
			{}
			void run(ClassDescription& singleClass){
				context.StartClass(singleClass);
				scRunner.runSingle(singleClass);
				context.EndClass();
			}
		};

		class ProjectDescription: public Prototype1::ProjectDescription{
			const std::string title;
			ClassList classlist;
			double elapsedTime;
			std::string name() const { return title; }
			size_t numClasses() const { return classlist.size(); }
			long results() const ;
			double run_time() const ;
			virtual double elapsed_time() const { return elapsedTime; }
		public:
			ProjectDescription(const std::string& title, const TestCaseList& caselist):title(title)
			{
				for(TestCaseList::const_iterator it=caselist.begin(), end=caselist.end(); it!=end; ++it){
					classlist.push_back(ClassDescription(*it));
				}
			}
			void run(Prototype1::ClassRunner& runner){
				for(ClassList::iterator it=classlist.begin(), end=classlist.end(); it!=end; ++it){
					runner.run(*it);
				}
			}
			virtual void reportElapsedTime(double time){ elapsedTime=time; }
		};
	}
}

#endif // PRIVATECLASSES_H_AF48FD94_9DB7_40F6_A19F_6999193E6752
