#pragma once

#define _LOG(func, level, msg) { \
	wrd::clog::Logger::getInstance().func(\
        "%s " WRD_TAG " %s <%s::%s#%d> %s", \
        wrd::indep::PlatformAPI::createCurrentTime("%b %d %Y  %X").c_str(), \
        level, __FILENAME__, __func__, __LINE__, msg); \
    }

#define WRD_LOG(level, msg) _LOG(dumpFormat, level, msg)

#define WRD_I(msg) _LOG(dumpFormat, "I", msg)
#define WRD_E(msg) _LOG(dumpFormat, "E", msg)
#define WRD_W(msg) _LOG(dumpFormat, "W", msg)
#define WRD_DI(msg) _LOG(dumpDbgFormat, "I", msg)
#define WRD_DE(msg) _LOG(dumpDbgFormat, "E", msg)
#define WRD_DW(msg) _LOG(dumpDbgFormat, "W", msg)
