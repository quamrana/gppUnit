#ifndef CLASSDESCRIPTION_H_8FB67FC2_A64D_482E_8A12_8AB6CD787F1C
#define CLASSDESCRIPTION_H_8FB67FC2_A64D_482E_8A12_8AB6CD787F1C

namespace Prototype1{
	class ClassDescription{
	public:
		virtual std::string name() const =0;
		virtual long results() const =0;
		virtual double run_time() const =0;
	};
}

#endif // CLASSDESCRIPTION_H_8FB67FC2_A64D_482E_8A12_8AB6CD787F1C
