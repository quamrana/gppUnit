#ifndef ASSERTBASE_H_3C026444_4356_4580_B677_3F7411D37DCA
#define ASSERTBASE_H_3C026444_4356_4580_B677_3F7411D37DCA

#include "ContextSetter.h"

namespace Prototype1{
	struct TestResult;

	class AssertBase: public ContextSetter{
		Internal::ClassContext* context;
		virtual void setContext(Internal::ClassContext* aContext){ context=aContext; }

	protected:
		virtual void Result(const Prototype1::TestResult& result);
	};

	class Confirm: public AssertBase{
	public:
		void fail(const char* message="fail");
		void pass(const char* message="pass");
		void isTrue(bool result, const char* message="Should be True");
	};
	class Expect: public Confirm{
		void Result(const TestResult& result);
	};

}

#endif // ASSERTBASE_H_3C026444_4356_4580_B677_3F7411D37DCA
