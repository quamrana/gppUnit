#include "src\Confirmation.h"

#include "src\ReportResult.h"
#include "src\AssertException.h"

#include "AutoRun.h"

typedef std::vector<std::string> strvec;

namespace TestAsserts{
	using gppUnit::equals;

	class Base: public Auto::TestCase, gppUnit::ReportResult{ 
		gppUnit::TestResult testResult;
		virtual void Report(const gppUnit::TestResult& result){
			testResult=result;
		}
		const strvec& description(){ return testResult.description; }
		size_t descriptionSize(){ return testResult.description.size(); }
	protected:
		void setReportOnSetter(gppUnit::ResultSetter& setter){
			setter.setReport(this);
		}
		void thenDescriptionIsEmpty(){
			confirm.that(descriptionSize(),equals(0),"Description is empty");
		}
		void thenDescriptionIs(const std::string& desc){
			expect.that(descriptionSize(),equals(1),"Description has one line");
			confirm.that(description().front(),equals(desc),desc.c_str());
		}
		void thenDescriptionIs(const strvec& desc){
			expect.that(description().size(),equals(desc.size()),"Description has same number of lines");
			confirm.isTrue(desc==description(),"Whole Description should match");
			strvec::const_iterator test=description().begin();
			for(strvec::const_iterator it=desc.begin(), end=desc.end(); it!=end; ++it){
				confirm.that(*test++,equals(*it),(*it).c_str());
			}
		}
		void thenResultIsFail(){
			confirm.isFalse(testResult.result,"thenResultIsFail");
			confirm.that(testResult.message,equals("fail"),"message is fail");
			//thenDescriptionIsEmpty();
		}
		void thenResultIsPass(){
			confirm.isTrue(testResult.result,"thenResultIsPass");
			confirm.that(testResult.message,equals("pass"),"message is pass");
			thenDescriptionIsEmpty();
		}
		void thenResultIsFalse(const char* message){
			confirm.isFalse(testResult.result,"thenResultIsFalse");
			confirm.that(testResult.message,equals(message),message);
			//thenDescriptionIsEmpty();
		}
		void thenResultIsTrue(const char* message){
			confirm.isTrue(testResult.result,"thenResultIsTrue");
			confirm.that(testResult.message,equals(message),message);
			//thenDescriptionIsEmpty();
		}
	};
	class ConfirmBase: public Base{
	protected:
		gppUnit::Confirm conf;
		void givenConfirm(){
			setReportOnSetter(conf);
		}
	};
	class ConfirmPassAndFail: public ConfirmBase{
		void whenFailCalled(){
			conf.fail("fail");
		}
		void whenPassCalled(){
			conf.pass("pass");
		}
		void test(){
			givenConfirm();
			whenFailCalled();
			thenResultIsFail();
			whenPassCalled();
			thenResultIsPass();
		}
	}GPPUNIT_INSTANCE;
	class ConfirmIsTrue: public ConfirmBase{
		void whenIsTrueCalled(bool value){
			conf.isTrue(value);
		}
		void test(){
			givenConfirm();
			whenIsTrueCalled(false);
			thenResultIsFalse("Should be True");
			whenIsTrueCalled(true);
			thenResultIsTrue("Should be True");
		}
	}GPPUNIT_INSTANCE;

	class CatchExceptionsFromExpect: public Base{
		gppUnit::Expect exp;
		bool caughtException;
	protected:
		void givenExpect(){
			setReportOnSetter(exp);
			caughtException=false;
		}
		void whenFailCalled(){
			try{
				exp.fail("fail");
			} catch (gppUnit::AssertException e){
				caughtException=true;
			}
		}
		void whenThatCalled(){
			try{
				exp.that(this,gppUnit::is_null(),"fail");
			} catch (gppUnit::AssertException e){
				caughtException=true;
			}
		}
		void thenExceptionCaught(){
			confirm.isTrue(caughtException,"thenExceptionCaught");
		}
		void whenPassCalled(){
			exp.pass("pass");
		}
	};
	class CatchExceptionsFromExpectFail: public CatchExceptionsFromExpect{
		void test(){
			givenExpect();
			whenFailCalled();
			thenResultIsFail();
			thenExceptionCaught();
			whenPassCalled();
			thenResultIsPass();
		}
	}GPPUNIT_INSTANCE;
	class CatchExceptionsFromExpectThat: public CatchExceptionsFromExpect{
		void test(){
			givenExpect();
			whenThatCalled();
			thenResultIsFail();
			thenExceptionCaught();
		}
	}GPPUNIT_INSTANCE;
}
namespace ConfirmThat{
	using TestAsserts::Base;
	using gppUnit::TableFormatter;
	using gppUnit::tab;
	using gppUnit::endl;

	class ConfirmThatResult: public TestAsserts::ConfirmBase{
		void test(){
			givenConfirm();
			conf.that(0,gppUnit::equal_to(0));
			thenResultIsTrue("Should match");
		}
	}GPPUNIT_INSTANCE;
	class ConfirmThatPassDescription: public TestAsserts::ConfirmBase{
		void test(){
			givenConfirm();
			conf.that(0,gppUnit::equal_to(0));

			gppUnit::TableFormatter f;
			f << "Expected" << tab << "'0'" << endl;
			f << "and got" << tab << "'0'" << endl;
			thenDescriptionIs(f.toVector());
		}
	}GPPUNIT_INSTANCE;
	class ConfirmThatFailDescription: public TestAsserts::ConfirmBase{
		void test(){
			givenConfirm();
			conf.that(1,gppUnit::equal_to(0));
			thenResultIsFalse("Should match");

			gppUnit::TableFormatter f;
			f << "Expected" << tab << "'0'" << endl;
			f << "but got" << tab << "'1'" << endl;
			thenDescriptionIs(f.toVector());
		}
	}GPPUNIT_INSTANCE;
	class ConfirmThatFailDescriptionIntChar: public TestAsserts::ConfirmBase{
		void test(){
			givenConfirm();
			long longint=2;
			signed char schar=-4;

			conf.that(schar,gppUnit::equal_to(longint));
			thenResultIsFalse("Should match");

			gppUnit::TableFormatter f;
			f << "Expected" << tab << "'2'" << endl;
			f << "but got" << tab << "'-4'" << endl;
			thenDescriptionIs(f.toVector());
		}
	}GPPUNIT_INSTANCE;
	class ConfirmThatFailDescriptionCharsChars: public TestAsserts::ConfirmBase{
		void test(){
			givenConfirm();
			const char* actual="1";
			const char* expected="2";

			conf.that(actual,gppUnit::equal_to(expected));
			thenResultIsFalse("Should match");

			gppUnit::TableFormatter f;
			f << "Expected" << tab << "string '2'" << endl;
			f << "but got" << tab << "'1'" << endl;
			thenDescriptionIs(f.toVector());
		}
	}GPPUNIT_INSTANCE;
	class ConfirmThatFailDescriptionCharsCharArray: public TestAsserts::ConfirmBase{
		void test(){
			givenConfirm();
			const char* actual="1";
			const char expected[]="2";

			conf.that(actual,gppUnit::equal_to(expected));
			thenResultIsFalse("Should match");

			gppUnit::TableFormatter f;
			f << "Expected" << tab << "string '2'" << endl;
			f << "but got" << tab << "'1'" << endl;
			thenDescriptionIs(f.toVector());
		}
	}GPPUNIT_INSTANCE;
}
