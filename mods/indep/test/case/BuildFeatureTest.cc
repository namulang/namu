#include "../common/indep-test-dep.hpp"

using namespace wrd::indep;

TEST(BuildFeature, dateGetter) {
	BuildFeature::Date date;
    ASSERT_GT(date.getYear(), 0);
    ASSERT_GT(date.getMonth(), 0);
    ASSERT_GT(date.getDay(), 0);
    ASSERT_STRNE(date.get().c_str(), "");
}

TEST(BuildFeature, timeGetter) {
    ASSERT_GT(BuildFeature::Time::getHour(), 0);
    ASSERT_GT(BuildFeature::Time::getMin(), 0);
    ASSERT_GT(BuildFeature::Time::getSec(), 0);
    ASSERT_STRNE(BuildFeature::Time::get().c_str(), "");
}

TEST(BuildFeature, versionGetter) {
    ASSERT_GE(BuildFeature::Version::getMajor(), 0);
    ASSERT_GE(BuildFeature::Version::getMinor(), 0);
    ASSERT_GE(BuildFeature::Version::getFix(), 0);
    ASSERT_STRNE(BuildFeature::Version::get().c_str(), "");
    ASSERT_STRNE(BuildFeature::Version::getValue().c_str(), "");
    ASSERT_STRNE(BuildFeature::Version::getName().c_str(), "");
}

TEST(BuildFeature, platformGetter) {
    BuildFeature::PlatformType type = BuildFeature::Platform::get();
    ASSERT_GT(type, BuildFeature::PLATFORM_TYPE_START);
    ASSERT_LE(type, BuildFeature::PLATFORM_TYPE_END);
    ASSERT_STRNE(BuildFeature::Platform::getVersion().c_str(), "");
    ASSERT_STRNE(BuildFeature::Platform::getName().c_str(), "");
}
