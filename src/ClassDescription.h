#include <string>

namespace gppUnit{
	class ClassDescription{
	protected:
		virtual ~ClassDescription(){}
	public:
		virtual std::string name() const =0;
		virtual size_t methods() const =0;
		virtual size_t results() const =0;
		virtual double run_time() const =0;
	};
}
