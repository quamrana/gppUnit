#ifndef CLASSDESCRIPTION_H_BDC873D7_B4F5_4B0B_AB40_7C3647B5CC28
#define CLASSDESCRIPTION_H_BDC873D7_B4F5_4B0B_AB40_7C3647B5CC28

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

#endif // CLASSDESCRIPTION_H_BDC873D7_B4F5_4B0B_AB40_7C3647B5CC28
