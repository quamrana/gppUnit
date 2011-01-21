#include "CompositeNotification.h"

namespace gppUnit{

	template<typename C, typename N, typename A>
	void caller1(C& collection, void (N::*f)(const A&), const A* a){
		for(typename C::iterator it=collection.begin(), end=collection.end(); it!=end; ++it){
			((*it)->*f)(*a);
		}
	}
	template<typename C, typename N>
	void caller(C& collection, void (N::*f)()){
		for(typename C::iterator it=collection.begin(), end=collection.end(); it!=end; ++it){
			((*it)->*f)();
		}
	}

	void CompositeNotification::StartProject(const ProjectDescription& desc){
		caller1(collection,&Notification::StartProject,&desc);
	}
	void CompositeNotification::StartClass(const ClassDescription& desc){
		caller1(collection,&Notification::StartClass,&desc);
	}
	void CompositeNotification::StartMethod(const MethodDescription& desc){
		caller1(collection,&Notification::StartMethod,&desc);
	}
	void CompositeNotification::Result(const TestResult& result){
		caller1(collection,&Notification::Result,&result);
	}
	void CompositeNotification::Exception(const std::string& what){
		caller1(collection,&Notification::Exception,&what);
	}
	void CompositeNotification::EndMethod(){
		caller(collection,&Notification::EndMethod);
	}
	void CompositeNotification::EndClass(){
		caller(collection,&Notification::EndClass);
	}
	void CompositeNotification::EndProject(){
		caller(collection,&Notification::EndProject);
	}

}
