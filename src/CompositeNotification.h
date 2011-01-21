#ifndef COMPOSITENOTIFICATION_H_37B4CC72_D39B_4B9F_BCA4_F4F2515937CD
#define COMPOSITENOTIFICATION_H_37B4CC72_D39B_4B9F_BCA4_F4F2515937CD

#include "Notification.h"

#include <vector>

namespace gppUnit {

	class CompositeNotification: public Notification {
		typedef std::vector<Notification*> NotificationCollection;
		NotificationCollection collection;

		void StartProject(const ProjectDescription&);
		void StartClass(const ClassDescription&);
		void StartMethod(const MethodDescription&);
		void Result(const TestResult&);
		void Exception(const std::string& /* what */);
		void EndMethod();
		void EndClass();
		void EndProject();
	public:
		void add(Notification* notify) { collection.push_back(notify); }
	};
}

#endif // COMPOSITENOTIFICATION_H_37B4CC72_D39B_4B9F_BCA4_F4F2515937CD
