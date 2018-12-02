#pragma once

#include "Logger.hpp"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define WRD_DUMP(level, msg, ...) {                                              \
	wrd::log::Logger::getInstance().dumpFormat("%s " WRD_TAG " %s <%s::%s#%d> " msg,   \
            wrd::indep::PlatformAPI::createCurrentTime("%b %d %Y  %X").c_str(), level,      \
            __FILENAME__, __func__, __LINE__, ##__VA_ARGS__                     \
        );                                                                      \
    }
#define WRD_INFO(msg, ...) WRD_DUMP("I", msg, ##__VA_ARGS__)
#define WRD_ERROR(msg, ...) WRD_DUMP("E", msg, ##__VA_ARGS__)
#define WRD_WARN(msg, ...) WRD_DUMP("W", msg, ##__VA_ARGS__)
