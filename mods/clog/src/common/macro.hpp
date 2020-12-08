#pragma once

#define WRD_LOG(level, msg) { \
	wrd::clog::Logger::getInstance().dumpFormat(\
        "%s " WRD_TAG " %s <%s::%s#%d> %s", \
        wrd::indep::PlatformAPI::createCurrentTime("%b %d %Y  %X").c_str(), \
        level, __FILENAME__, __func__, __LINE__, msg); \
    }
#define WRD_I(msg) WRD_LOG("I", msg)
#define WRD_E(msg) WRD_LOG("E", msg)
#define WRD_W(msg) WRD_LOG("W", msg)
