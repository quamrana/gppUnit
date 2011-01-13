#ifndef TESTCASE_H_BA9608EE_BC80_42C8_82D4_B82E10F763C7
#define TESTCASE_H_BA9608EE_BC80_42C8_82D4_B82E10F763C7

namespace Prototype1{

	class TestCase{
	protected:
		virtual ~TestCase(){}
	public:
		virtual void setup(){}
		virtual void test()=0;
		virtual void teardown(){}
	};
}

#endif // TESTCASE_H_BA9608EE_BC80_42C8_82D4_B82E10F763C7
