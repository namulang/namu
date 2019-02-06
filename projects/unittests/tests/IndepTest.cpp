#include "../TestCase.hpp"

WRD_TEST_START(IndepTest)
	using namespace indep;

	BuildFeatures::Date date;
	WRD_INFO("today is %d-%d %d. %s", date.getMonth(), date.getDay(), date.getYear(),
	BuildFeatures::Time::get().c_str())
	WRD_INFO("Version is %s", BuildFeatures::Version::get().c_str())
	BuildFeatures::Platform plat;
	WRD_INFO("Platform is %d, %s, %s", plat.get(), plat.getName().c_str(), plat.getVersion().c_str())
	BuildFeatures::Building build;
	WRD_INFO("BuildType is %d, %s", build.get(), build.getName().c_str())

	return "";
WRD_TEST_END(IndepTest)
