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
#ifndef COMPOSITENOTIFICATION_H_37B4CC72_D39B_4B9F_BCA4_F4F2515937CD
#define COMPOSITENOTIFICATION_H_37B4CC72_D39B_4B9F_BCA4_F4F2515937CD

#include "Notification.h"

#include <vector>

namespace gppUnit {

	class CompositeNotification: public Notification {
		typedef std::vector<Notification*> NotificationCollection;
		NotificationCollection collection;

		void StartProject(const ProjectDescription&) override;
		void StartClass(const ClassDescription&) override;
		void StartMethod(const MethodDescription&) override;
		void Result(const TestResult&) override;
		void Exception(const std::string& /* what */) override;
		void EndMethod() override;
		void EndClass() override;
		void EndProject() override;
	public:
		CompositeNotification();
		void add(Notification& notify) { collection.push_back(&notify); }
	};
}

#endif // COMPOSITENOTIFICATION_H_37B4CC72_D39B_4B9F_BCA4_F4F2515937CD
