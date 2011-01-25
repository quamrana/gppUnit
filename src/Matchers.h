#ifndef MATCHERS_H_A1A948B8_4BB3_4E59_8A68_E4E99CC5EEC2
#define MATCHERS_H_A1A948B8_4BB3_4E59_8A68_E4E99CC5EEC2

namespace gppUnit {
	struct MatcherResult {
		bool result;

		MatcherResult(): result(false) {}
	};
	struct is_null {
		MatcherResult match(const void* actual) const {
			MatcherResult result;
			result.result = (actual == 0);
			return result;
		}
	};
}

#endif // MATCHERS_H_A1A948B8_4BB3_4E59_8A68_E4E99CC5EEC2
