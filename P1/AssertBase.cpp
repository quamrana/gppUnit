#include "AssertBase.h"
#include "TestResult.h"
#include "PrivateClassContext.h"
#include "AssertException.h"

#include <sstream>

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
	void Confirm::isFalse(bool result, const char* message){
		if(!result){
			pass(message);
		} else {
			fail(message);
		}
	}
	void Confirm::equals(const std::string& expected, const std::string& actual, const char* message){
		TestResult result;
		result.result=(expected==actual);
		result.message=message;
		if(result.result){
			result.description.push_back("Both expected and actual are equal to:");
			result.description.push_back(actual);
		} else {
			result.description.push_back("Expected:");
			result.description.push_back(expected);
			result.description.push_back("But got :");
			result.description.push_back(actual);
		}
		Result(result);
	}
	void Confirm::equals(const size_t& expected, const size_t& actual, const char* message){
		TestResult result;
		result.result=(expected==actual);
		result.message=message;

		std::stringstream stractual;
		stractual << actual;
		if(result.result){
			result.description.push_back("Both expected and actual are equal to:");
			result.description.push_back(stractual.str());
		} else {
			std::stringstream strexpected;
			strexpected << expected;
			result.description.push_back("Expected:");
			result.description.push_back(strexpected.str());
			result.description.push_back("But got :");
			result.description.push_back(stractual.str());
		}
		Result(result);
	}

	void Expect::Result(const TestResult& result){
		AssertBase::Result(result);
		if(!result.result){
			throw assertException;
		}
	}

}
