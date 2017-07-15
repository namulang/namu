#include "BuildFeatures.hpp"

namespace NE
{
    using namespace std;
    
    #define THIS BuildFeatures
    #define _STRING_METHOD(function, message)   \
        const string& THIS::function            \
        {                                       \
            static string inner = message;      \
            return inner;                       \
        }
    #define _INTEGER_METHOD(function, value)    \
        type_int THIS::function                 \
        {                                       \
            return value;                       \
        }
    
    _STRING_METHOD(Date::get(), NE_BUILD_DATE)    
    _INTEGER_METHOD(Date::getYear(), NE_BUILD_DATE_YEAR)
    _INTEGER_METHOD(Date::getMonth(), NE_BUILD_DATE_MONTH)
    _INTEGER_METHOD(Date::getDay(), NE_BUILD_DATE_DAY)
    
    _STRING_METHOD(Time::get(), NE_BUILD_TIME)
    _INTEGER_METHOD(Time::getHour(), NE_BUILD_TIME_HOUR)
    _INTEGER_METHOD(Time::getMinute(), NE_BUILD_TIME_MINUTE)
    _INTEGER_METHOD(Time::getSecond(), NE_BUILD_TIME_SECOND)

    _STRING_METHOD(Version::get(), NE_BUILD_VERSION)
    _INTEGER_METHOD(Version::getMajor(), NE_BUILD_VERSION_MAJOR)
    _INTEGER_METHOD(Version::getMinor(), NE_BUILD_VERSION_MINOR)
    _INTEGER_METHOD(Version::getFix(), NE_BUILD_VERSION_FIX)

    THIS::PlatformType THIS::Platform::get()
    {
        static PlatformType inner = PLATFORM_TYPE_START;
        if(inner == PLATFORM_TYPE_START)
        {
            const string& name = getName();
            const char* map[] = {"PLATFORM_TYPE_START", "WINDOW", "LINUX", NE_NULL};
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
    _STRING_METHOD(Platform::getName(), NE_BUILD_PLATFORM)
    _STRING_METHOD(Platform::getVersion(), NE_BUILD_PLATFORM_VERSION)

    THIS::BuildType THIS::Building::get()
    {
        static BuildType inner = BUILD_TYPE_START;
        if(inner == BUILD_TYPE_START)
        {
            const string& name = getName();
            const char* map[] = {"BUILD_TYPE_START", "DEBUG", "RELEASE", NE_NULL};
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
    _STRING_METHOD(Building::getName(), NE_BUILD_TYPENAME)
}