#ifndef REPORTRESULT_H_4241BF2A_7CEF_47C1_8BEF_6911CD34852F
#define REPORTRESULT_H_4241BF2A_7CEF_47C1_8BEF_6911CD34852F

namespace gppUnit{
	struct TestResult;

	class ReportResult{
	protected:
		virtual ~ReportResult(){}
	public:
		virtual void Result(const TestResult&)=0;
	};
}

#endif // REPORTRESULT_H_4241BF2A_7CEF_47C1_8BEF_6911CD34852F
