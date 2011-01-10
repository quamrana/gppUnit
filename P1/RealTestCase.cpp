#include "RealTestCase.h"
#include "PrivateClassContext.h"

namespace Prototype1{

	void RealTestCase::setContext(Internal::ClassContext* context){ 
		context->setContextOn(confirm);
		context->setContextOn(expect);
	}
}