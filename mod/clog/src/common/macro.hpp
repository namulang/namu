#pragma once

#define _LOG(func, level, fmt, ...) { \
    wrd::Logger::get().func(\
        "%s " WRD_TAG " %s <%s::%s#%d> " fmt, \
        wrd::PlatformAPI::createCurrentTime("%b %d %Y  %X").c_str(), \
        level, __FILENAME__, __func__, __LINE__, ## __VA_ARGS__); \
    }

//  Log macro:
//      prints debug log on console and file.
//      you can check the file recorded logs at your current work directory
//      named to "logs".
//
//      if you dbg version macros, _DI, _DE, _DW, then log msg will be left
//      only if you use dbg configuration.
//
//      usage:
//          WRD_I("just message.")
//          WRD_I("with format=%x string=%s", &format, format.c_str())
#define WRD_I(fmt, ...) _LOG(dumpFormat, "I", fmt, ## __VA_ARGS__)
#define WRD_E(fmt, ...) _LOG(dumpFormat, "E", fmt, ## __VA_ARGS__)
#define WRD_W(fmt, ...) _LOG(dumpFormat, "W", fmt, ## __VA_ARGS__)
#ifdef WRD_DEBUG
#   define WRD_DI(fmt, ...) WRD_I(fmt, ## __VA_ARGS__)
#   define WRD_DE(fmt, ...) WRD_I(fmt, ## __VA_ARGS__)
#   define WRD_DW(fmt, ...) WRD_I(fmt, ## __VA_ARGS__)
#else
#   define WRD_DI(fmt, ...)
#   define WRD_DE(fmt, ...)
#   define WRD_DW(fmt, ...)
#endif
