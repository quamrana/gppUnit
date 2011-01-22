#ifndef METHODTIMER_H_49D8BBA3_EEBD_4789_9ABE_6FE8687E9BD7
#define METHODTIMER_H_49D8BBA3_EEBD_4789_9ABE_6FE8687E9BD7

namespace gppUnit {

	class MethodCaller;
	class TimeReport;

	class MethodTimer {
	protected:
		virtual ~MethodTimer() {}
	public:
		virtual void timeMethod(MethodCaller& caller, TimeReport& report) = 0;

		// Platform specific timer implementation
		static MethodTimer& getTimer();
	};
}

#endif // METHODTIMER_H_49D8BBA3_EEBD_4789_9ABE_6FE8687E9BD7
