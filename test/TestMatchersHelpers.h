#ifndef TESTMATCHERSHELPERS_H_A3D0B478_2F63_4292_A712_747E447A8AC9
#define TESTMATCHERSHELPERS_H_A3D0B478_2F63_4292_A712_747E447A8AC9

#include "src\Matchers.h"

#include "AutoRun.h"

namespace Utilities{
	class MatcherHelper: public Auto::TestCase{
	protected:
		template<typename MATCHER, typename ACTUAL>
		void That(const ACTUAL& actual, MATCHER m, const char* desc){
			gppUnit::MatcherResult result=m.match(actual);
			confirm.isTrue(result.result,"result is true");
			confirm.that(result.description(),gppUnit::equals(desc),"description is '1'");
		}
		template<typename MATCHER, typename ACTUAL>
		void MisMatch(const ACTUAL& actual, MATCHER m, const char* desc){
			gppUnit::MatcherResult result=m.match(actual);
			confirm.isFalse(result.result,"result is false");
			confirm.that(result.description(),gppUnit::equals(desc),"description is '1'");
		}
	};
}

#endif // TESTMATCHERSHELPERS_H_A3D0B478_2F63_4292_A712_747E447A8AC9
