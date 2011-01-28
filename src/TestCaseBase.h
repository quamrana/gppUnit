#ifndef TESTCASEBASE_H_0643B0E7_9A3D_4B3F_8AB1_CAEFE7AC6E9F
#define TESTCASEBASE_H_0643B0E7_9A3D_4B3F_8AB1_CAEFE7AC6E9F

#include "Confirmation.h"

namespace gppUnit {
	class TestCaseBase: public virtual PrototypeTestCase {
		void setReport(ReportResult*);
	protected:
		Confirm confirm;
		Expect expect;
	public:
		TestCaseBase(): confirm(), expect() {}
	};
}

#endif // TESTCASEBASE_H_0643B0E7_9A3D_4B3F_8AB1_CAEFE7AC6E9F
