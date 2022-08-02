#include "buildFeature.hpp"

namespace namu {

    using namespace std;

    WRD_DEF_ME(buildFeature)

    wint me::date::getYear() { return WRD_BUILD_DATE_YEAR; }
    wint me::date::getMonth() { return WRD_BUILD_DATE_MONTH; }
    wint me::date::getDay() { return WRD_BUILD_DATE_DAY; }

    wint me::time::getHour() { return WRD_BUILD_TIME_HOUR; }
    wint me::time::getMin() { return WRD_BUILD_TIME_MINUTE; }
    wint me::time::getSec() { return WRD_BUILD_TIME_SECOND; }

    wint me::version::getMajor() { return WRD_BUILD_VERSION_MAJOR; }
    wint me::version::getMinor() { return WRD_BUILD_VERSION_MINOR; }
    wint me::version::getFix() { return WRD_BUILD_VERSION_FIX; }

    me::platformType me::platform::get() {
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

    me::buildType me::config::get() {
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

    wbool me::config::isDbg() {
#if WRD_IS_DBG
        return true;
#else
        return false;
#endif
    }
}
