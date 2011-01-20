#ifndef PROJECTDESCRIPTION_H_7F78488D_CF48_4219_80EE_F764A6F6FCB5
#define PROJECTDESCRIPTION_H_7F78488D_CF48_4219_80EE_F764A6F6FCB5

#include <string>

namespace gppUnit{
	class ProjectDescription{
	protected:
		virtual ~ProjectDescription(){}
	public:
		virtual std::string name() const =0;
		virtual size_t classes() const =0;
		virtual size_t results() const =0;
		virtual double run_time() const =0;
		//virtual double elapsed_time() const =0;
	};
}

#endif // PROJECTDESCRIPTION_H_7F78488D_CF48_4219_80EE_F764A6F6FCB5
