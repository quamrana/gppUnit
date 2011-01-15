#ifndef METHODDESCRIPTION_H_32660EAC_DB28_4549_BD53_E61D323298B0
#define METHODDESCRIPTION_H_32660EAC_DB28_4549_BD53_E61D323298B0

#include <string>

namespace gppUnit{
	class MethodDescription{
	protected:
		virtual ~MethodDescription(){}
	public:
		virtual std::string name() const =0;
		virtual size_t results() const =0;
		virtual double run_time() const =0;
	};
}

#endif // METHODDESCRIPTION_H_32660EAC_DB28_4549_BD53_E61D323298B0
