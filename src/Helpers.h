#ifndef HELPERS_H_6D7D0E77_E929_4264_9FE6_0D30D0530B62
#define HELPERS_H_6D7D0E77_E929_4264_9FE6_0D30D0530B62

namespace gppUnit{
	template<typename T>
	struct Report{
		bool operator()(bool init, const T& description){
			return init & description.goodReport;
		}
	};
	template<typename T>
	struct Results{
		size_t operator()(size_t init, const T& description){
			return init+description.results;
		}
	};
	template<typename T>
	struct RunTime{
		double operator()(double init, const T& description){
			return init+description.reportedTime;
		}
	};
}

#endif // HELPERS_H_6D7D0E77_E929_4264_9FE6_0D30D0530B62
