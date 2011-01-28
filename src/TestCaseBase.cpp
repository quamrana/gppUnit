#include "TestCaseBase.h"

namespace gppUnit {
	void TestCaseBase::setReport(ReportResult* reporter){
		gppUnit::setReport(confirm,reporter);
		gppUnit::setReport(expect,reporter);
	}
}

