#ifndef TESTCASE_H_9227601C_F5E5_47F6_A89A_F47B3BBB576B
#define TESTCASE_H_9227601C_F5E5_47F6_A89A_F47B3BBB576B

namespace gppUnit{
	class TestCase{
	protected:
		virtual ~TestCase(){}
	public:
		virtual void setup(){}
		virtual void test()=0;
		virtual void teardown(){}
	};

	class ReportResult{
	protected:
		virtual ~ReportResult(){}
	public:
		virtual void Result()=0;
	};
	class ResultSetter{
	protected:
		virtual ~ResultSetter(){}
	public:
		virtual void setReport(ReportResult*)=0;
	};

	class PrototypeTestCase: public TestCase, public ResultSetter{
	protected:
		virtual ~PrototypeTestCase(){}
	};

	/**
	TestCaseList is subject to changes in definition and location
	*/
	typedef std::vector<PrototypeTestCase*> TestCaseList;
}

#endif // TESTCASE_H_9227601C_F5E5_47F6_A89A_F47B3BBB576B
