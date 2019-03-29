#include "src\TypeInformation.h"

#include <string>
#include <algorithm>

namespace gppUnit {
	class ApprovalNamer {
	public:
		virtual std::string getApprovedFile() const = 0;
		virtual std::string getReceivedFile() const = 0;
		virtual ~ApprovalNamer() {}
	};

	class SimpleNamer: public ApprovalNamer {
	public:
		template<typename T>
		explicit SimpleNamer(const T& base): SimpleNamer(gppUnit::demangleTypeName(typeid(base).name())) {}
		explicit SimpleNamer(const std::string& fullClassName) { makeNames(fullClassName); }
		std::string getApprovedFile() const { return approvedFileName; }
		std::string getReceivedFile() const { return receivedFileName; }

	private:
		void makeNames(const std::string& fullClassName);
		std::string approvedFileName;
		std::string receivedFileName;

		std::string sanitized(const std::string& name);
	};
}

namespace gppUnit {
	bool isForbidden(char c) {
		static std::string forbiddenChars("\\/:?*\"<>| ");
		return std::string::npos != forbiddenChars.find(c);
	}
	void SimpleNamer::makeNames(const std::string& fullClassName) {
		approvedFileName = sanitized(fullClassName) + ".approved" + ".txt";
		receivedFileName = sanitized(fullClassName) + ".received" + ".txt";
	}

	std::string SimpleNamer::sanitized(const std::string& name) {
		std::string ret = name;
		std::replace_if(ret.begin(), ret.end(), isForbidden, '_');
		return ret;
	}
}


#include "AutoRun.h"

namespace ApproverComponents {
	using gppUnit::equals;
	class TestSimpleNamer: public Auto::TestCase {
		gppUnit::ApprovalNamer* namer{ nullptr };

		void teardown() { delete namer; }
	protected:
		void givenSimpleNamer() {
			namer = new gppUnit::SimpleNamer(*this);
		}
		void givenSimpleNamer(const std::string& aName) {
			namer = new gppUnit::SimpleNamer(aName);
		}

		void thenApprovedFileIs(const std::string& expected) {
			confirm.that(namer->getApprovedFile(), equals(expected), __FUNCTION__);
		}
		void thenReceivedFileIs(const std::string& expected) {
			confirm.that(namer->getReceivedFile(), equals(expected), __FUNCTION__);
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
