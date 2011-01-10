#ifndef PROJECTDESCRIPTION_H_C1020259_D49E_4862_9D6B_CEB2DBF70104
#define PROJECTDESCRIPTION_H_C1020259_D49E_4862_9D6B_CEB2DBF70104

#include <string>

namespace Prototype1{
	class ProjectDescription{
	public:
		virtual std::string name() const =0;
		virtual size_t numClasses() const =0;
		virtual long results() const =0;
		virtual double run_time() const =0;
		virtual double elapsed_time() const =0;
	};
}

#endif // PROJECTDESCRIPTION_H_C1020259_D49E_4862_9D6B_CEB2DBF70104
