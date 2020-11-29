#include "../common/indep-test-dep.hpp"

TEST(BuildFeatureTest, getter) {
	using namespace wrd::indep;

	BuildFeature::Date date;
    ASSERT_GT(date.getYear(), 0);
}
