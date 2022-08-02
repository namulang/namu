#pragma once

#define _LOG(func, level, fmt, ...) {                                         \
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
#define WRD_E(fmt, ...) ::namu::logger::get().dumpFormatLog("E", WRD_TAG, __FILENAME__, __func__, __LINE__, fmt "\n", ## __VA_ARGS__)
#define WRD_W(fmt, ...) ::namu::logger::get().dumpFormatLog("W", WRD_TAG, __FILENAME__, __func__, __LINE__, fmt "\n", ## __VA_ARGS__)
#define WRD_I(fmt, ...) ::namu::logger::get().dumpFormatLog("I", WRD_TAG, __FILENAME__, __func__, __LINE__, fmt "\n", ## __VA_ARGS__)
#ifdef WRD_DEBUG
#   define WRD_DE(fmt, ...) WRD_E(fmt, ## __VA_ARGS__)
#   define WRD_DW(fmt, ...) WRD_W(fmt, ## __VA_ARGS__)
#   define WRD_DI(fmt, ...) WRD_I(fmt, ## __VA_ARGS__)
#else
#   define WRD_DE(fmt, ...)
#   define WRD_DW(fmt, ...)
#   define WRD_DI(fmt, ...)
#endif
