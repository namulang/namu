#pragma once

#include "../macro.hpp"
#include "../common.hpp"

namespace namu {
    using std::string;

    class _wout buildFeature {
        WRD_DECL_ME(buildFeature)

    public:
        struct _wout date {
            WRD_DECL_ME(date)

        public:
            static WRD_SINGLETON_GETTER(const string& get(), string, WRD_BUILD_DATE)
            static wint getYear();
            static wint getMonth();
            static wint getDay();
        };

        struct _wout time {
            WRD_DECL_ME(time)

        public:
            static WRD_SINGLETON_GETTER(const string& get(), string, WRD_BUILD_TIME)
            static wint getHour();
            static wint getMin();
            static wint getSec();
        };

        struct _wout version {
            WRD_DECL_ME(version)

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

        struct _wout platform {
            WRD_DECL_ME(platform)

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

        struct _wout config {
            WRD_DECL_ME(config)

        public:
            static buildType get();
            static wbool isDbg();
            static WRD_SINGLETON_GETTER(const string& getName(), string, WRD_BUILD_TYPENAME)
        };
    };
}
