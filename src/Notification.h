#ifndef NOTIFICATION_H_FE7AAFFA_316E_4165_9D82_C593A049C539
#define NOTIFICATION_H_FE7AAFFA_316E_4165_9D82_C593A049C539

#include <string>

namespace gppUnit{
	class MethodDescription;
	struct TestResult;

	class Notification{
	protected:
		virtual ~Notification(){}
	public:
		virtual void StartClass(const std::string /* name */){}
		virtual void StartMethod(const MethodDescription&){}
		virtual void Result(const TestResult&){}
		virtual void Exception(const std::string& /* what */){}
		virtual void EndMethod(){}
		virtual void EndClass(){}
	};
}

#endif // NOTIFICATION_H_FE7AAFFA_316E_4165_9D82_C593A049C539
