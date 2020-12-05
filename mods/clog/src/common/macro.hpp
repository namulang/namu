#pragma once

#define WRD_LOG(level, msg, ...) { \
	wrd::clog::Logger::getInstance().dumpFormat("%s " WRD_TAG " %s <%s::%s#%d> " msg, \
            wrd::indep::PlatformAPI::createCurrentTime("%b %d %Y  %X").c_str(), level, \
            __FILENAME__, __func__, __LINE__, ##__VA_ARGS__ \
        ); \
    }
#define WRD_I(msg, ...) WRD_LOG("I", msg, ##__VA_ARGS__)
#define WRD_E(msg, ...) WRD_LOG("E", msg, ##__VA_ARGS__)
#define WRD_W(msg, ...) WRD_LOG("W", msg, ##__VA_ARGS__)
