#pragma once

#include "Logger.hpp"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define NE_DUMP(level, msg, ...) {                                              \
        Logger::getInstance().dumpFormat("%s " NE_TAG " %s <%s::%s#%d> " msg,   \
            PlatformAPI::createCurrentTime("%b %d %Y  %X").c_str(), level,      \
            __FILENAME__, __func__, __LINE__, ##__VA_ARGS__                     \
        );                                                                      \
    }
#define NE_INFO(msg, ...) NE_DUMP("I", msg, ##__VA_ARGS__)
#define NE_ERROR(msg, ...) NE_DUMP("E", msg, ##__VA_ARGS__)
#define NE_WARN(msg, ...) NE_DUMP("W", msg, ##__VA_ARGS__)