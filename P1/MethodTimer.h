#ifndef METHODTIMER_H_B5430B47_5DEF_457B_B2D4_7DD515790747
#define METHODTIMER_H_B5430B47_5DEF_457B_B2D4_7DD515790747

namespace Prototype1{
	namespace Internal{
		class MethodCaller;
	}

	class TimeReport;

	class MethodTimer{
	public:
		virtual void timeMethod(Internal::MethodCaller& caller, TimeReport& report)=0;
	};
}

#endif // METHODTIMER_H_B5430B47_5DEF_457B_B2D4_7DD515790747
