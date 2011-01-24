#include "src\StreamNotification.h"
#include "src\ProjectDescription.h"
#include "src\ClassDescription.h"
#include "src\MethodDescription.h"
#include "src\TestResult.h"

#include "AutoRun.h"

#include <sstream>

namespace TestPrintFormatter{
	class PrintFormatterHelper: public Auto::TestCase{
		gppUnit::PrintFormatter* format;
		std::string result;
		std::string update;
	protected:
		void givenFormatter(size_t size){
			format=new gppUnit::PrintFormatter(size);
		}
		void whenCentering(const std::string& title){
			result=format->centreInAsterisks(title);
		}
		void whenUpdatedWith(size_t max, size_t current){
			update=format->updateRunningAsterisks(max,current);
		}
		void thenResultIs(const std::string& result){
			confirm.equals(result,this->result,"Result is centred");
		}
		void thenUpdateIs(const std::string& update){
			confirm.equals(update,this->update,"Update is correct");
		}
		void teardown(){ delete format; }
	};

	class SingleCharTitle: public PrintFormatterHelper{
		void test(){
			givenFormatter(5);
			whenCentering("x");
			thenResultIs("* x *");
		}
	}GPPUNIT_INSTANCE;
	class SingleCharTitleMultipleAsterisks: public PrintFormatterHelper{
		void test(){
			givenFormatter(9);
			whenCentering("x");
			thenResultIs("*** x ***");
		}
	}GPPUNIT_INSTANCE;
	class SingleCharTitleNonSymmetrical: public PrintFormatterHelper{
		void test(){
			givenFormatter(8);
			whenCentering("x");
			thenResultIs("** x ***");
		}
	}GPPUNIT_INSTANCE;

	class TitleLongerThanField: public PrintFormatterHelper{
		void test(){
			givenFormatter(5);
			whenCentering("TitleLongerThanField");
			thenResultIs("* T *");
		}
	}GPPUNIT_INSTANCE;

	class LongTitleLongField: public PrintFormatterHelper{
		void test(){
			givenFormatter(50);
			whenCentering("LongTitleLongField");
			thenResultIs("*************** LongTitleLongField ***************");
		}
	}GPPUNIT_INSTANCE;
	class LongTitleLongFieldNonSymmetrical: public PrintFormatterHelper{
		void test(){
			givenFormatter(50);
			whenCentering("LongTitleLongFieldNonSymmetrica");
			thenResultIs("******** LongTitleLongFieldNonSymmetrica *********");
		}
	}GPPUNIT_INSTANCE;

	class RunningAsterisks: public PrintFormatterHelper{
		void test(){
			givenFormatter(5);
			whenUpdatedWith(5,0);
			thenUpdateIs("");

			whenUpdatedWith(5,1);
			thenUpdateIs("*");

			whenUpdatedWith(5,1);
			thenUpdateIs("");

			whenUpdatedWith(5,3);
			thenUpdateIs("**");

			whenUpdatedWith(5,5);
			thenUpdateIs("**");

			whenUpdatedWith(5,5);
			thenUpdateIs("");

			whenUpdatedWith(5,6);
			thenUpdateIs("");
		}
	}GPPUNIT_INSTANCE;
}
namespace TestStreamNotification{
	class MockProject1: public gppUnit::ProjectDescription{
		virtual std::string name() const { return "MockProject1"; }
		virtual size_t classes() const { return 5; }
		virtual bool hasPassed() const { return 0; }
		virtual size_t results() const { return 0; }
		virtual double run_time() const { return 0; }
	}mp1;
	class MockClass1: public gppUnit::ClassDescription{
		virtual std::string name() const { return "MockClass1"; }
		virtual size_t methods() const { return 0; }
		virtual size_t results() const { return 0; }
		virtual double run_time() const { return 0; }
	}mc1;
	class MockMethod1: public gppUnit::MethodDescription{
		virtual std::string name() const { return "MockMethod1"; }
		virtual size_t results() const { return 0; }
		virtual double run_time() const { return 0; }
	}mm1;
	class StreamNotificationHelper: public Auto::TestCase{
		std::stringstream out;
		gppUnit::StreamNotification* stream;
		gppUnit::Notification* notify;
	protected:
		void givenStreamNotification(){
			notify=stream=new gppUnit::StreamNotification(out);
		}
		void whenStartProjectCalled(){
			notify->StartProject(mp1);
		}
		void whenStartClassCalled(){
			whenStartProjectCalled();
			out.str("");
			notify->StartClass(mc1);
		}
		void whenStartClassCalledAgain(){
			out.str("");
			notify->StartClass(mc1);
		}
		void whenResultPass(){
			notify->StartProject(mp1);
			notify->StartClass(mc1);
			out.str("");
			notify->StartMethod(mm1);
			gppUnit::TestResult result;
			result.result=true;
			notify->Result(result);
		}
		void whenResultFailed(){
			gppUnit::TestResult result;
			notify->Result(result);
		}

		void thenProjectTitleAndClassesPrinted(){
			const char* expected=
				"****************** MockProject1 ******************\n"
				"5 classes to run.\n";
			confirm.equals(expected,out.str());
		}
		void thenAsteriskPrinted(){
			const char* expected="**********";
			confirm.equals(expected,out.str());
		}
		void thenNothingPrinted(){
			confirm.equals("",out.str());
		}
		void thenFullResultPrinted(){
			const char* expected=
				"\n"
				" In Class: MockClass1\n"
				"  In Method: MockMethod1\n"
				"   Failure\n";
			confirm.equals(expected,out.str());
		}
		void teardown(){ delete stream; }
	};

	class ProjectStarted: StreamNotificationHelper{
		void test(){
			givenStreamNotification();
			whenStartProjectCalled();
			thenProjectTitleAndClassesPrinted();
		}
	}GPPUNIT_INSTANCE;
	class ClassStarted: StreamNotificationHelper{
		void test(){
			givenStreamNotification();
			whenStartClassCalled();
			thenAsteriskPrinted();
			whenStartClassCalledAgain();
			thenAsteriskPrinted();
		}
	}GPPUNIT_INSTANCE;
	class ResultPassed: StreamNotificationHelper{
		void test(){
			givenStreamNotification();
			whenResultPass();
			thenNothingPrinted();
			whenResultFailed();
			thenFullResultPrinted();
		}
	}GPPUNIT_INSTANCE;
}
