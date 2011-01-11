#include "AssertBase.h"
#include "TestResult.h"
#include "PrivateClassContext.h"
#include "AssertException.h"

namespace Prototype1{
	void AssertBase::Result(const TestResult& result){
		if(context){
			context->Result(result);
		}
	}

	void Confirm::fail(const char* message){
		TestResult result;
		result.result=false;
		result.message="Fail: ";
		result.message+=message;
		Result(result);
	}
	void Confirm::pass(const char* message){
		TestResult result;
		result.result=true;
		result.message=message;
		Result(result);
	}
	void Confirm::isTrue(bool result, const char* message){
		if(result){
			pass(message);
		} else {
			fail(message);
		}
	}

	void Expect::Result(const TestResult& result){
		AssertBase::Result(result);
		if(!result.result){
			throw assertException;
		}
	}

}
