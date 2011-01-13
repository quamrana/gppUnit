#ifndef REALTESTCASE_H_519C1A50_FCFB_48B3_921A_31CF16372ADB
#define REALTESTCASE_H_519C1A50_FCFB_48B3_921A_31CF16372ADB

#include "PrototypeTestCase.h"
#include "AssertBase.h"

namespace Prototype1{
	class RealTestCase: public virtual PrototypeTestCase{
		void setContext(Internal::ClassContext* aContext);
	protected:
		Confirm confirm;
		Expect expect;
	public:
		RealTestCase():confirm(),expect(){}
	};
}

#endif // REALTESTCASE_H_519C1A50_FCFB_48B3_921A_31CF16372ADB
