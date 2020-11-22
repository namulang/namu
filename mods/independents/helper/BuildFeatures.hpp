#pragma once

#include "../macro.hpp"
#include "../indep-common.hpp"

namespace wrd
{
	namespace indep
	{
		class BuildFeatures
		{
			typedef std::string string;

		public:
			struct Date
			{
				static WRD_SINGLETON_GETTER(const string&, get, WRD_VOID(), string, WRD_BUILD_DATE)
				static wint getYear();
				static wint getMonth();
				static wint getDay();
			};
			struct Time
			{
				static WRD_SINGLETON_GETTER(const string&, get, WRD_VOID(), string, WRD_BUILD_TIME)
				static wint getHour();
				static wint getMinute();
				static wint getSecond();
			};
			struct Version
			{
				static WRD_SINGLETON_GETTER(const string&, get, WRD_VOID(), string, WRD_BUILD_VERSION)
				static WRD_SINGLETON_GETTER(const string&, getValue, WRD_VOID(), string, WRD_BUILD_VERSION_VALUE)
				static WRD_SINGLETON_GETTER(const string&, getName, WRD_VOID(), string, WRD_BUILD_VERSION_NAME)
				static wint getMajor();
				static wint getMinor();
				static wint getFix();
			};
			enum PlatformType
			{
				PLATFORM_TYPE_START = 0,
				WINDOW = PLATFORM_TYPE_START,
				PLATFORM_TYPE_END,
				LINUX = PLATFORM_TYPE_END
			};
			struct Platform
			{
				static PlatformType get();
				static WRD_SINGLETON_GETTER(const string&, getName, WRD_VOID(), string, WRD_BUILD_PLATFORM_NAME)
				static WRD_SINGLETON_GETTER(const string&, getVersion, WRD_VOID(), string, WRD_BUILD_PLATFORM_VERSION)
			};
			enum BuildType
			{
				BUILD_TYPE_START = 0,
				DEBUG = BUILD_TYPE_START,
				BUILD_TYPE_END,
				RELEASE = BUILD_TYPE_END
			};
			struct Building
			{
				static BuildType get();
				static WRD_SINGLETON_GETTER(const string&, getName, WRD_VOID(), string, WRD_BUILD_TYPENAME)
			};
		};
	}
}
