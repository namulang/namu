#include "BuildFeature.hpp"

namespace wrd { namespace indep {

    using namespace std;

    WRD_DEF_THIS(BuildFeature)

    wint This::Date::getYear() { return WRD_BUILD_DATE_YEAR; }
    wint This::Date::getMonth() { return WRD_BUILD_DATE_MONTH; }
    wint This::Date::getDay() { return WRD_BUILD_DATE_DAY; }

    wint This::Time::getHour() { return WRD_BUILD_TIME_HOUR; }
    wint This::Time::getMin() { return WRD_BUILD_TIME_MINUTE; }
    wint This::Time::getSec() { return WRD_BUILD_TIME_SECOND; }

    wint This::Version::getMajor() { return WRD_BUILD_VERSION_MAJOR; }
    wint This::Version::getMinor() { return WRD_BUILD_VERSION_MINOR; }
    wint This::Version::getFix() { return WRD_BUILD_VERSION_FIX; }

    This::PlatformType This::Platform::get() {
        static PlatformType inner = PLATFORM_TYPE_START;
        if(inner == PLATFORM_TYPE_START)
        {
            const string& name = getName();
            const char* map[] = {"Windows", "Linux", "Darwin", "Others", WRD_NULL};
            int n=-1;
            while(map[++n])
                if(name == map[n])
                {
                    inner = PlatformType(n);
                    break;
                }
        }

        return inner;
    }

    This::BuildType This::Building::get() {
        static BuildType inner = BUILD_TYPE_START;
        if(inner == BUILD_TYPE_START)
        {
            const string& name = getName();
            const char* map[] = {"DEBUG", "RELEASE", WRD_NULL};
            int n=-1;
            while(map[++n])
                if(name == map[n])
                {
                    inner = BuildType(n);
                    break;
                }
        }

        return inner;
    }
} }
