#include "ApprovalsTest/ApprovalNamer.h"

#include <string>

namespace gppUnit {
	class TextFileApprover {
	public:
		TextFileApprover(const std::string& data, ApprovalNamer& n):namer(n),actual(data){}
		bool verify() {
			return actualAndApprovedMatch();
		}
	private:
		bool actualAndApprovedMatch() {
			auto approved = getApprovedContents();
			if(actual == approved) {
				// removeReceived()
				return true;
			}
			return false;
		}

		std::string getApprovedContents() { return getFileContents(namer.getApprovedFilename()); }

		ApprovalNamer& namer;
		const std::string actual;		// received
		//const std::string approved;

		virtual std::string getFileContents(const std::string& filename) const = 0;
	};
}






#include "ApprovalsTest\SimpleNamer.h"

#include "src\TypeInformation.h"

#include "AutoRun.h"

#include <map>

namespace ApproverComponents {
	using gppUnit::equals;

	class MockApprover: public gppUnit::TextFileApprover {
	public:
		using TextFileApprover::TextFileApprover;
	private:
		std::string getFileContents(const std::string& filename) const{
			return fileSys[filename];
		}
	public:
		mutable std::map<std::string, std::string> fileSys;
	};
	class TestSimpleNamer: public Auto::TestCase {
		gppUnit::ApprovalNamer* namer{ nullptr };

		void teardown() { delete namer; }
	protected:
		void givenSimpleNamer() {
			namer = new gppUnit::SimpleNamer(gppUnit::demangleTypeName(typeid(*this).name()));
		}
		void givenSimpleNamer(const std::string& aName) {
			namer = new gppUnit::SimpleNamer(aName);
		}

		void thenApprovedFileIs(const std::string& expected) {
			confirm.that(namer->getApprovedFilename(), equals(expected), __FUNCTION__);
		}
		void thenReceivedFileIs(const std::string& expected) {
			confirm.that(namer->getReceivedFilename(), equals(expected), __FUNCTION__);
		}
	};
	class TestSimpleNamerOnThisClass: public TestSimpleNamer {
		void test() {
			givenSimpleNamer();
			thenApprovedFileIs("ApproverComponents__TestSimpleNamerOnThisClass.approved.txt");
			thenReceivedFileIs("ApproverComponents__TestSimpleNamerOnThisClass.received.txt");
		}
	} GPPUNIT_INSTANCE;
	class TestSimpleNamerOnThisStringName: public TestSimpleNamer {
		void test() {
			givenSimpleNamer("\\Slash/slash:colon?query*star\"quote<angle>brackets|pipe space");
			thenApprovedFileIs("_Slash_slash_colon_query_star_quote_angle_brackets_pipe_space.approved.txt");
			thenReceivedFileIs("_Slash_slash_colon_query_star_quote_angle_brackets_pipe_space.received.txt");
		}
	} GPPUNIT_INSTANCE;

	class TestActualAndApprovedMatch: public Auto::TestCase, gppUnit::ApprovalNamer {
		gppUnit::TextFileApprover* approver{ nullptr };
		MockApprover* mockApprover{ nullptr };

		std::string getApprovedFilename() const override { return "a"; }
		std::string getReceivedFilename() const override { return "r"; }

		// TODO: make file system
		std::string approvedContents;
		bool verifyResult{ false };

		void teardown() { delete approver; }
		void givenApproverWithContents(const std::string& contents) {
			mockApprover = new MockApprover(contents, *this);
			approver = mockApprover;
		}
		void givenApprovedContents(const std::string& contents) {
			approvedContents = contents;
			//
		}
		template<typename T>
		void whenVerifiedWith(const T& actual){
			std::stringstream str;
			str << actual;
			givenApproverWithContents(str.str());
			mockApprover->fileSys[getApprovedFilename()] = approvedContents;
			verifyResult = approver->verify();
		}
		void thenApproved() {
			confirm.isTrue(verifyResult, __FUNCTION__);
		}
		void test() {
			givenApprovedContents("42");
			whenVerifiedWith(42);
			thenApproved();
		}
	} GPPUNIT_INSTANCE;

	/*
	class Int42Matches: public Auto::TestCase {
		void givenApprover() {
			// Make an approver with
			//    SimpleNamer
			//    MockFileSystem
			//    TextFileApprover
		}
		void test() {
			givenApprover();
			givenApprovedData(42);

			whenVerifyCalledWith(42);
			thenResultIs(true);
		}
	} GPPUNIT_INSTANCE;
	*/
}