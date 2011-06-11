/*
Copyright (c) 2011 Andrew Wall

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "src\SuccessLogger.h"
#include "src\ProjectDescription.h"

#include "AutoRun.h"

namespace TestFileLogger{
	using gppUnit::equals;

	class MockProject1: public gppUnit::ProjectDescription{
		virtual std::string name() const { return "MockProject1"; }
		virtual size_t classes() const { return 0; }
		virtual bool hasPassed() const { return false; }
		virtual size_t results() const { return 0; }
		virtual double run_time() const { return 0; }
	}mp1;
	class MockProject2: public gppUnit::ProjectDescription{
		virtual std::string name() const { return "MockProject2"; }
		virtual size_t classes() const { return 0; }
		virtual bool hasPassed() const { return true; }
		virtual size_t results() const { return 0; }
		virtual double run_time() const { return 0; }
	}mp2;

	class FileLoggerThatCanBeDeletedForCoverage: public gppUnit::FileLoggerInterface {
		void LogToFile(const std::string&, const gppUnit::ProjectDescription*){}
	};
	class TestNotification: public Auto::TestCase, gppUnit::FileLoggerInterface{
		std::string fileName;
		const gppUnit::ProjectDescription* project;

		gppUnit::FileLoggerNotification* fileNotify;

		void LogToFile(const std::string& fileName, const gppUnit::ProjectDescription* project){
			this->fileName=fileName;
			this->project=project;
		}

		void givenNotification(){
			fileName="";
			project=0;
			fileNotify= new gppUnit::FileLoggerNotification("foo",*this);
		}
		void whenStartAndEndProjectCalled(){
			gppUnit::Notification* notify=fileNotify;
			notify->StartProject(mp1);
			notify->EndProject();
		}
		void thenDetailsPassedToInterface(){
			confirm.that(fileName,equals("foo"),"filename should be foo");
			confirm.that((gppUnit::ProjectDescription*)project,
				equals((gppUnit::ProjectDescription*)&mp1),"project is mp1");
		}
		void teardown(){ delete fileNotify; }
		void test(){
			givenNotification();
			whenStartAndEndProjectCalled();
			thenDetailsPassedToInterface();
			FileLoggerThatCanBeDeletedForCoverage d;
		}
	}GPPUNIT_INSTANCE;

	class SuccessLoggerTestBase: public Auto::TestCase, gppUnit::LoggerAlgorithm{

		mutable std::stringstream collect;
		gppUnit::FileLoggerNotification* fileNotify;
		bool exists;

		bool allowedToProceed(const gppUnit::ProjectDescription* project) const {
			return project->hasPassed();
		}
		virtual bool fileExists(const std::string& fileName) const { 
			collect << "e." << fileName << '.';
			return exists; 
		}
		virtual void openFileForAppend(const std::string& fileName){
			collect << "a." << fileName << '.';
		}
		virtual void openFileForWriting(const std::string& fileName){
			collect << "o." << fileName << '.';
		}
		virtual void writeHeader(const std::string& fileName, const gppUnit::ProjectDescription* /*project*/){ 
			collect << "h." << fileName << '.'; 
		}
        virtual std::ostream& getFile(){ return collect; }

		void writeLog(const gppUnit::ProjectDescription* /*project*/){ collect << "w."; }
		void closeFile(){ collect << "c."; }

		void teardown(){ delete fileNotify; }
	protected:
		void givenNotification(){
			fileNotify= new gppUnit::FileLoggerNotification("foo",*this);
			exists=true;
		}
		void whenStartAndEndProjectCalled(const gppUnit::ProjectDescription& desc, bool exists=true){
			this->exists=exists;
			gppUnit::Notification* notify=fileNotify;
			notify->StartProject(desc);
			notify->EndProject();
		}
		void thenNoActionTaken(){
			confirm.that(collect.str(),equals(""),"No action");
		}
		void thenActionTakenIs(const char* action){
			confirm.that(collect.str(),equals(action),"Expected action");
		}
	};
	class SuccessLoggerTakesNoAction: public SuccessLoggerTestBase{

		void test(){
			givenNotification();
			whenStartAndEndProjectCalled(mp1);
			thenNoActionTaken();
		}
	}GPPUNIT_INSTANCE;

	class SuccessLoggerAppendsToBase: public SuccessLoggerTestBase{
		void test(){
			givenNotification();
			whenStartAndEndProjectCalled(mp2);
			thenActionTakenIs("e.foo.a.foo.w.c.");
		}
	}GPPUNIT_INSTANCE;
	class SuccessLoggerWritesHeader: public SuccessLoggerTestBase{
		void test(){
			givenNotification();
			whenStartAndEndProjectCalled(mp2,false);
			thenActionTakenIs("e.foo.o.foo.h.foo.w.c.");
		}
	}GPPUNIT_INSTANCE;

    class TestLoggerImplementations: public Auto::TestCase, public virtual gppUnit::LoggerAlgorithm{
		mutable std::stringstream collect;
        virtual std::ostream& getFile(){ return collect; }
        // nop implementations!!
        bool fileExists(const std::string&) const { return false; }
        void openFileForAppend(const std::string&){}
		void openFileForWriting(const std::string&){}
		void closeFile(){}

    protected:
        void thenAllowedToProceed(const gppUnit::ProjectDescription& project, bool expected){
            confirm.that(allowedToProceed(&project),equals(expected),"Should be allowed to proceed");
        }

	};
    class TestSuccessLoggerImplementation: public TestLoggerImplementations, gppUnit::SuccessLoggerImplementation{
        void test(){
            thenAllowedToProceed(mp1,false);
            thenAllowedToProceed(mp2,true);
		}
	}GPPUNIT_INSTANCE;
    class TestAllRunsLoggerImplementation: public TestLoggerImplementations, gppUnit::AllRunsLoggerImplementation{
        void test(){
            thenAllowedToProceed(mp1,true);
            thenAllowedToProceed(mp2,true);
		}
	}GPPUNIT_INSTANCE;

}
