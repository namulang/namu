#pragma once

#include "Logger.hpp"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define NE_DUMP(level, msg) {                                               \
        Logger::getInstance().dumpFormat("%s " NE_TAG " %s <%s::%s#%d> %s", \
            PlatformAPI::createCurrentTime("%b %d %Y  %X").c_str(), level,  \
            __FILENAME__, __func__, __LINE__, msg                           \
        );                                                                  \
    }
#define NE_INFO(msg) NE_DUMP("I", msg)
#define NE_ERROR(msg) NE_DUMP("E", msg)
#define NE_WARN(msg) NE_DUMP("W", msg)