#pragma once

#include "../macro.hpp"
#include "../indep-common.hpp"

namespace wrd {
	namespace indep {
        using std::string;

		class BuildFeature {
            WRD_DECL_THIS(BuildFeature)

		public:
			struct Date {
                WRD_DECL_THIS(Date)

				static WRD_SINGLETON_GETTER(const string& get(), string, WRD_BUILD_DATE)
				static wint getYear();
				static wint getMonth();
				static wint getDay();
			};

			struct Time {
                WRD_DECL_THIS(Time)

				static WRD_SINGLETON_GETTER(const string& get(), string, WRD_BUILD_TIME)
				static wint getHour();
				static wint getMin();
				static wint getSec();
			};

			struct Version {
                WRD_DECL_THIS(Version)

				static WRD_SINGLETON_GETTER(const string& get(), string, WRD_BUILD_VERSION)
				static WRD_SINGLETON_GETTER(const string& getValue(), string, WRD_BUILD_VERSION_VALUE)
				static WRD_SINGLETON_GETTER(const string& getName(), string, WRD_BUILD_VERSION_NAME)
				static wint getMajor();
				static wint getMinor();
				static wint getFix();
			};

			enum PlatformType {
				PLATFORM_TYPE_START = 0,
				WINDOW = PLATFORM_TYPE_START,
				PLATFORM_TYPE_END,
				LINUX = PLATFORM_TYPE_END
			};

			struct Platform {
                WRD_DECL_THIS(Platform)

				static PlatformType get();
				static WRD_SINGLETON_GETTER(const string& getName(), string, WRD_BUILD_PLATFORM_NAME)
				static WRD_SINGLETON_GETTER(const string& getVersion(), string, WRD_BUILD_PLATFORM_VERSION)
			};

			enum BuildType {
				BUILD_TYPE_START = 0,
				DEBUG = BUILD_TYPE_START,
				BUILD_TYPE_END,
				RELEASE = BUILD_TYPE_END
			};

			struct Building {
                WRD_DECL_THIS(Building)

				static BuildType get();
				static WRD_SINGLETON_GETTER(const string& getName(), string, WRD_BUILD_TYPENAME)
			};
		};
	}
}
