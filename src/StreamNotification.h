#ifndef STREAMNOTIFICATION_H_9DE37245_C9F0_4B33_A0A5_25E32A5DECE9
#define STREAMNOTIFICATION_H_9DE37245_C9F0_4B33_A0A5_25E32A5DECE9

#include "Notification.h"

namespace gppUnit {

	class PrintFormatter {
		size_t size;
		size_t asteriskCounter;
	public:
		std::string centreInAsterisks(const std::string& title) const ;
		std::string updateRunningAsterisks(size_t max, size_t current);
		std::string fullWidthAsterisks() const ;
		explicit PrintFormatter(size_t size);
	};

	class StreamNotification: public Notification {
		std::ostream& out;
		PrintFormatter formatter;
		const ProjectDescription* proj;
		const ClassDescription* desc;
		const MethodDescription* method;

		bool hasFailed;
		size_t classCount;
		bool classShown;
		bool methodShown;

		void BeforeFailure();
		void ShowFailure(const TestResult&);

		void ShowClass();
		void ShowMethod();
		void ShowDescription(std::string) const ;

		void StartProject(const ProjectDescription&);
		void StartClass(const ClassDescription&);
		void StartMethod(const MethodDescription&);
		void Result(const TestResult&);
		void Exception(const std::string& /* what */);

		void EndMethod();

		void EndProject();
	public:
		explicit StreamNotification(std::ostream& out);
	};
}

#endif // STREAMNOTIFICATION_H_9DE37245_C9F0_4B33_A0A5_25E32A5DECE9
