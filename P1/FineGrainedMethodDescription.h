#ifndef FINEGRAINEDMETHODDESCRIPTION_H_5F546047_C6BC_41E8_B5C7_C0678D6CE9E3
#define FINEGRAINEDMETHODDESCRIPTION_H_5F546047_C6BC_41E8_B5C7_C0678D6CE9E3

namespace Prototype1{
	class FineGrainedMethodDescription{
	public:
		virtual std::string name() const =0;
		virtual long results() const =0;
		virtual double run_time() const =0;
	};
}

#endif // FINEGRAINEDMETHODDESCRIPTION_H_5F546047_C6BC_41E8_B5C7_C0678D6CE9E3
