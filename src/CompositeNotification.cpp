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
#include "CompositeNotification.h"

namespace gppUnit {

	CompositeNotification::CompositeNotification(): collection() {}

	template<typename C, typename N, typename A>
	void caller1(C& collection, void (N::*f)(const A&), const A* a) {
		for(typename C::iterator it = collection.begin(), end = collection.end(); it != end; ++it) {
			((*it)->*f)(*a);
		}
	}
	template<typename C, typename N>
	void caller(C& collection, void (N::*f)()) {
		for(typename C::iterator it = collection.begin(), end = collection.end(); it != end; ++it) {
			((*it)->*f)();
		}
	}

	void CompositeNotification::StartProject(const ProjectDescription& desc) {
		caller1(collection, &Notification::StartProject, &desc);
	}
	void CompositeNotification::StartClass(const ClassDescription& desc) {
		caller1(collection, &Notification::StartClass, &desc);
	}
	void CompositeNotification::StartMethod(const MethodDescription& desc) {
		caller1(collection, &Notification::StartMethod, &desc);
	}
	void CompositeNotification::Result(const TestResult& result) {
		caller1(collection, &Notification::Result, &result);
	}
	void CompositeNotification::Exception(const std::string& what) {
		caller1(collection, &Notification::Exception, &what);
	}
	void CompositeNotification::EndMethod() {
		caller(collection, &Notification::EndMethod);
	}
	void CompositeNotification::EndClass() {
		caller(collection, &Notification::EndClass);
	}
	void CompositeNotification::EndProject() {
		caller(collection, &Notification::EndProject);
	}

}
