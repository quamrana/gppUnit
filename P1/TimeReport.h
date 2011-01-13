#ifndef TIMEREPORT_H_7E1EA5E4_29EA_40D7_A150_8DB7AC76E816
#define TIMEREPORT_H_7E1EA5E4_29EA_40D7_A150_8DB7AC76E816

namespace Prototype1{

	class TimeReport{
	protected:
		virtual ~TimeReport(){}
	public:
		virtual void reportTime(double run_time)=0;
	};

}

#endif // TIMEREPORT_H_7E1EA5E4_29EA_40D7_A150_8DB7AC76E816
