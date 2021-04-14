#include "buildFeature.hpp"

namespace wrd {

    using namespace std;

    WRD_DEF_THIS(buildFeature)

    wint This::date::getYear() { return WRD_BUILD_DATE_YEAR; }
    wint This::date::getMonth() { return WRD_BUILD_DATE_MONTH; }
    wint This::date::getDay() { return WRD_BUILD_DATE_DAY; }

    wint This::time::getHour() { return WRD_BUILD_TIME_HOUR; }
    wint This::time::getMin() { return WRD_BUILD_TIME_MINUTE; }
    wint This::time::getSec() { return WRD_BUILD_TIME_SECOND; }

    wint This::version::getMajor() { return WRD_BUILD_VERSION_MAJOR; }
    wint This::version::getMinor() { return WRD_BUILD_VERSION_MINOR; }
    wint This::version::getFix() { return WRD_BUILD_VERSION_FIX; }

    This::platformType This::platform::get() {
        static platformType inner = PLATFORM_TYPE_START;
        if(inner == PLATFORM_TYPE_START)
        {
            const string& name = getName();
            const char* map[] = {"Windows", "Linux", "Darwin", "Others", nullptr};
            int n=-1;
            while(map[++n])
                if(name == map[n])
                {
                    inner = platformType(n);
                    break;
                }
        }

        return inner;
    }

    This::buildType This::config::get() {
        static buildType inner = BUILD_TYPE_START;
        if(inner == BUILD_TYPE_START)
        {
            const string& name = getName();
            const char* map[] = {"Debug", "Release", nullptr};
            int n=-1;
            while(map[++n])
                if(name == map[n])
                {
                    inner = buildType(n);
                    break;
                }
        }

        return inner;
    }
}
