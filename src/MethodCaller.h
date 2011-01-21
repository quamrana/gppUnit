#ifndef METHODCALLER_H_A03DA9E5_A7B9_4477_830F_43B19569C9C4
#define METHODCALLER_H_A03DA9E5_A7B9_4477_830F_43B19569C9C4

namespace gppUnit {
	class MethodCaller {
	protected:
		virtual ~MethodCaller() {}
	public:
		virtual void forward() = 0;
	};
}

#endif // METHODCALLER_H_A03DA9E5_A7B9_4477_830F_43B19569C9C4
