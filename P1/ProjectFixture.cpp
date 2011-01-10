#include "ProjectFixture.h"

#include "PrivateClasses.h"
#include "HiResTimer.h"
#include "PrivateClassContext.h"

#include "ClassRunner.h"

namespace Prototype1{

	void ProjectFixture::run(const std::string& title, const TestCaseList& caselist, Internal::ClassContext& context){
		time_interval time=getTime();
		// Generate a model of the whole project run.
		Internal::ProjectDescription description(title,caselist);

		//Internal::ClassRunner runner(context);
		Prototype2::ClassRunner runner(context);
		context.notify.StartProject(description);

		description.run(runner);

		description.reportElapsedTime(timeDifference(time,getTime()));
		context.notify.EndProject();
	}
}
