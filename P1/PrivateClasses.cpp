#include "PrivateClasses.h"
#include "SingleClassRunner.h"
#include "PrototypeTestCase.h"

#include <sstream>
#include <typeinfo>

namespace Prototype1{
	namespace Internal{

		std::string ClassDescription::name() const { return typeid(*testcase).name(); }

		template<typename T>
		struct RunTime{
			double operator()(double init, const T& description){
				return init+description.run_time();
			}
		};

		template<typename T>
		struct Results{
			long operator()(long init, const T& description){
				return init+description.results();
			}
		};

		double ClassDescription::run_time() const { 
			return std::accumulate(descriptions.begin(),descriptions.end(),double(),RunTime<FineGrainedMethodDescription>());
		}
		long ClassDescription::results() const { 
			return std::accumulate(descriptions.begin(),descriptions.end(),long(),Results<FineGrainedMethodDescription>());
		}

		double ProjectDescription::run_time() const {
			return std::accumulate(classlist.begin(),classlist.end(),double(),RunTime<Prototype1::ClassDescription>());
		}
		long ProjectDescription::results() const { 
			return std::accumulate(classlist.begin(),classlist.end(),long(),Results<Prototype1::ClassDescription>());
		}
	}
}

