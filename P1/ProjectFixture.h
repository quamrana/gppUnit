#ifndef PROJECTFIXTURE_H_568B931A_8509_40BB_B223_FAF5E02941B9
#define PROJECTFIXTURE_H_568B931A_8509_40BB_B223_FAF5E02941B9

#include <vector>
#include <string>

namespace Prototype1{
	class PrototypeTestCase;

	namespace Internal{
		class ClassContext;
	}
	typedef std::vector<PrototypeTestCase*> TestCaseList;

	class ProjectFixture{
	public:
		void run(const std::string& title, const TestCaseList& caselist, Internal::ClassContext& context);
	};
}

#endif // PROJECTFIXTURE_H_568B931A_8509_40BB_B223_FAF5E02941B9
