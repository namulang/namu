#pragma once

#include "../macros.hpp"

namespace NE
{
    struct BuildFeatures
    {
        typedef std::string string;

        struct Date 
        {
            static const string& get();
            static type_int getYear();
            static type_int getMonth();
            static type_int getDay();
        };
        struct Time
        {
            static const string& get();
            static type_int getHour();
            static type_int getMinute();
            static type_int getSecond();
        };
        struct Version
        {
            static const string& get();
            static type_int getMajor();
            static type_int getMinor();
            static type_int getFix();
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