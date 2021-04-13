#pragma once

#include "../macro.hpp"
#include "../common.hpp"

namespace wrd {
    using std::string;

    class buildFeature {
        WRD_DECL_THIS(buildFeature)

    public:
        struct date {
            WRD_DECL_THIS(date)

        public:
            static WRD_SINGLETON_GETTER(const string& get(), string, WRD_BUILD_DATE)
            static wint getYear();
            static wint getMonth();
            static wint getDay();
        };

        struct time {
            WRD_DECL_THIS(time)

        public:
            static WRD_SINGLETON_GETTER(const string& get(), string, WRD_BUILD_TIME)
            static wint getHour();
            static wint getMin();
            static wint getSec();
        };

        struct version {
            WRD_DECL_THIS(version)

        public:
            static WRD_SINGLETON_GETTER(const string& get(), string, WRD_BUILD_VERSION)
            static WRD_SINGLETON_GETTER(const string& getValue(), string, WRD_BUILD_VERSION_VALUE)
            static WRD_SINGLETON_GETTER(const string& getName(), string, WRD_BUILD_VERSION_NAME)
            static wint getMajor();
            static wint getMinor();
            static wint getFix();
        };

        enum platformType {
            PLATFORM_TYPE_START = -1,
            WINDOW,
            LINUX,
            MACOS,
            OTHERS,
            PLATFORM_TYPE_END,
        };

        struct platform {
            WRD_DECL_THIS(platform)

        public:
            static platformType get();
            static WRD_SINGLETON_GETTER(const string& getName(), string, WRD_BUILD_PLATFORM_NAME)
            static WRD_SINGLETON_GETTER(const string& getVersion(), string, WRD_BUILD_PLATFORM_VERSION)
        };

        enum buildType {
            BUILD_TYPE_START = -1,
            DEBUG,
            RELEASE,
            BUILD_TYPE_END,
        };

        struct config {
            WRD_DECL_THIS(config)

        public:
            static buildType get();
            static WRD_SINGLETON_GETTER(const string& getName(), string, WRD_BUILD_TYPENAME)
        };
    };
}
