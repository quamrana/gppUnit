#include "ApprovalsTest\TextFileApprover.h"

#include "ApprovalsTest\SimpleNamer.h"

#include "src\TypeInformation.h"

#include "AutoRun.h"

#include <map>
#include <functional>
#include <numeric>

namespace ApproverComponents {
	using gppUnit::equals;

	class MockApprover: public gppUnit::TextFileApprover {
	public:
		using TextFileApprover::TextFileApprover;

		// Mock implementations of file system
		std::string getFileContents(const std::string& filename) const override {
			if(fileExists(filename)) {
				return fileSys[filename];
			}
			return "";
		}
		void makeFileWithContents(const std::string& filename, const std::string& contents) const override {
			fileSys[filename] = contents;
		}
		virtual void remove(const std::string& filename)const override { fileSys.erase(filename); }

		bool fileExists(const std::string& filename) const {
			return fileSys.count(filename) > 0;
		}
		mutable std::map<std::string, std::string> fileSys;

		virtual void startDiff(const std::string& lhsFilename, const std::string& rhsFilename) const override {
			userRequest(*this, lhsFilename, rhsFilename);
		}

		std::function<void(const MockApprover&, const std::string&, const std::string&)> userRequest{ [](const MockApprover&, const std::string& /*lhsFilename*/, const std::string& /*rhsFilename*/) {} };
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

	class TestTextFileApprover: public Auto::TestCase, gppUnit::ApprovalNamer {
		gppUnit::TextFileApprover* approver{ nullptr };
		MockApprover* mockApprover{ nullptr };

		std::string getApprovedFilename() const override { return "a"; }
		std::string getReceivedFilename() const override { return "r"; }

		// TODO: make file system
		bool pleaseCreateApproved{ false };
		std::string approvedContents;
		bool userWillAcceptReceived{ false };
		bool verifyResult{ false };

		void teardown() { delete approver; }
	protected:
		void givenApproverWithContents(const std::string& contents) {
			mockApprover = new MockApprover(contents, *this);
			approver = mockApprover;
		}
		void givenApprovedContents(const std::string& contents) {
			approvedContents = gppUnit::TextFileApprover::makeBoundedContents(contents);
			pleaseCreateApproved = true;
		}
		void givenUserWillAcceptReceived() {
			userWillAcceptReceived = true;
		}
		void thenTheseFilesExist(const std::string& lhs, const std::string& rhs) {
			expect.isTrue(mockApprover->fileExists(lhs), "During report lhs file should exist");
			expect.isTrue(mockApprover->fileExists(rhs), "During report rhs file should exist");
		}

		template<typename T>
		void whenVerifiedWith(const T& actual) {
			std::stringstream str;
			str << actual;
			givenApproverWithContents(str.str());
			if(pleaseCreateApproved) {
				mockApprover->fileSys[getApprovedFilename()] = approvedContents;
			}
			if(userWillAcceptReceived) {
				mockApprover->userRequest = [this](const MockApprover & mock, const std::string & lhs, const std::string & rhs) {
					thenTheseFilesExist(lhs, rhs);
					mock.makeFileWithContents(getApprovedFilename(), mock.getFileContents(getReceivedFilename()));
				};
			} else {
				mockApprover->userRequest = [this](const MockApprover& /*mock*/, const std::string & lhs, const std::string & rhs) {
					thenTheseFilesExist(lhs, rhs);
				};
			}
			verifyResult = approver->verify();
		}
		void thenApproved() {
			confirm.isTrue(verifyResult, __FUNCTION__);
		}
		void thenNotApproved() {
			confirm.isFalse(verifyResult, __FUNCTION__);
		}
		void thenReceivedFileDoesNotExist() {
			confirm.isFalse(mockApprover->fileExists(getReceivedFilename()), __FUNCTION__);
		}
		void thenReceivedFileDoesExist() {
			confirm.isTrue(mockApprover->fileExists(getReceivedFilename()), __FUNCTION__);
		}
		void thenApprovedFileIsEmpty() {
			expect.isTrue(mockApprover->fileExists(getApprovedFilename()), "Approved file should exist");
			confirm.that(mockApprover->getFileContents(getApprovedFilename()), equals(""), "Approved file should be empty");
		}
	};
	class ActualAndApprovedMatch: public TestTextFileApprover {
		void test() {
			givenApprovedContents("42");
			whenVerifiedWith(42);
			thenApproved();
			thenReceivedFileDoesNotExist();
		}
	} GPPUNIT_INSTANCE;
	class MismatchButUserApprovesReceived: public TestTextFileApprover {
		void test() {
			givenApprovedContents("42");
			givenUserWillAcceptReceived();
			whenVerifiedWith(43);
			thenApproved();
			thenReceivedFileDoesNotExist();
		}
	} GPPUNIT_INSTANCE;
	class MismatchAndUserAgrees: public TestTextFileApprover {
		void test() {
			givenApprovedContents("42");
			whenVerifiedWith(43);
			thenNotApproved();
			thenReceivedFileDoesExist();
		}
	} GPPUNIT_INSTANCE;
	class MismatchDueToMissingApprovedFileUserAgrees: public TestTextFileApprover {
		void test() {
			whenVerifiedWith(43);
			thenNotApproved();
			thenReceivedFileDoesExist();
			thenApprovedFileIsEmpty();
		}
	} GPPUNIT_INSTANCE;
	/*
	class VerifyString: public Auto::TestCase {
		std::string launch(std::vector<std::string> argv) {
			//if (!exists(argv.front())) {
			//	return false;
			//}

			std::string command = std::accumulate(argv.begin(), argv.end(), std::string(""), [](std::string a, std::string b) {return a + " " + "\"" + b + "\""; });
			std::string startCommand = "start \"\" " + command;
			//system(startCommand.c_str());
			return startCommand;
		}

		void test() {
			confirm.that(launch({ "merge", "f1.txt", "f2.txt" }), equals(""), "merge command");
			confirm.verify("A String2");
		}
	} GPPUNIT_INSTANCE;
	*/
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
