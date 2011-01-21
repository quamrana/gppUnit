#ifndef TIMEREPORT_H_EE79312F_5D82_4216_B11D_C0117EA21C11
#define TIMEREPORT_H_EE79312F_5D82_4216_B11D_C0117EA21C11

namespace gppUnit {

	class TimeReport {
	protected:
		virtual ~TimeReport() {}
	public:
		virtual void reportTime(double run_time) = 0;
	};

}

#endif // TIMEREPORT_H_EE79312F_5D82_4216_B11D_C0117EA21C11
