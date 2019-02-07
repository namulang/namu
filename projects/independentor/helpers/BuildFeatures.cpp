#include "BuildFeatures.hpp"

namespace wrd
{
	namespace indep
	{
		using namespace std;
	   
		#define THIS BuildFeatures
		#define _INTEGER_METHOD(function, value)    \
			wint THIS::function                \
			{                                      \
				return value;                      \
			}
	   
		_INTEGER_METHOD(Date::getYear(), WRD_BUILD_DATE_YEAR)
		_INTEGER_METHOD(Date::getMonth(), WRD_BUILD_DATE_MONTH)
		_INTEGER_METHOD(Date::getDay(), WRD_BUILD_DATE_DAY)
	   
		_INTEGER_METHOD(Time::getHour(), WRD_BUILD_TIME_HOUR)
		_INTEGER_METHOD(Time::getMinute(), WRD_BUILD_TIME_MINUTE)
		_INTEGER_METHOD(Time::getSecond(), WRD_BUILD_TIME_SECOND)

		_INTEGER_METHOD(Version::getMajor(), WRD_BUILD_VERSION_MAJOR)
		_INTEGER_METHOD(Version::getMinor(), WRD_BUILD_VERSION_MINOR)
		_INTEGER_METHOD(Version::getFix(), WRD_BUILD_VERSION_FIX)

		THIS::PlatformType THIS::Platform::get()
		{
			static PlatformType inner = PLATFORM_TYPE_START;
			if(inner == PLATFORM_TYPE_START)
			{
				const string& name = getName();
				const char* map[] = {"Windows", "Linux", WRD_NULL};
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

		THIS::BuildType THIS::Building::get()
		{
			static BuildType inner = BUILD_TYPE_START;
			if(inner == BUILD_TYPE_START)
			{
				const string& name = getName();
				const char* map[] = {"BUILD_TYPE_START", "DEBUG", "RELEASE", WRD_NULL};
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
	}
}
