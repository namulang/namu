#pragma once

#include "../macros.hpp"

namespace wrd
{
	namespace indep
	{
		struct BuildFeatures
		{
			typedef std::string string;

			struct Date 
			{
				static const string& get();
				static wint getYear();
				static wint getMonth();
				static wint getDay();
			};
			struct Time
			{
				static const string& get();
				static wint getHour();
				static wint getMinute();
				static wint getSecond();
			};
			struct Version
			{
				static const string& get();
				static const string& getValue();
				static const string& getName();
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
				static const string& getName();
				static const string& getVersion();
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
				static const string& getName();
			};
		};
	}
}
