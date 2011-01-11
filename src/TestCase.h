#ifndef TESTCASE_H_9227601C_F5E5_47F6_A89A_F47B3BBB576B
#define TESTCASE_H_9227601C_F5E5_47F6_A89A_F47B3BBB576B

namespace gppUnit{
	class TestCase{
	public:
		virtual void setup(){}
		virtual void test()=0;
		virtual void teardown(){}
	};
}

#endif // TESTCASE_H_9227601C_F5E5_47F6_A89A_F47B3BBB576B
