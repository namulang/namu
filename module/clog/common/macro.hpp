#pragma once

//  Log macro:
//      prints debug log on console and file.
//      you can check the file recorded logs at your current work directory
//      named to "logs".
//
//      if you dbg version macros, _DI, _DE, _DW, then log msg will be left
//      only if you use dbg configuration.
//
//      usage:
//          NM_I("just message.")
//          NM_I("with format=%x string=%s", &format, format.c_str())
#ifndef __EMSCRIPTEN__
#    define NM_E(fmt, ...) \
        ::nm::richLog(::nm::errLv::ERR, __FILENAME__, __func__, __LINE__, fmt "\n", ##__VA_ARGS__)
#    define NM_W(fmt, ...) \
        ::nm::richLog(::nm::errLv::WARN, __FILENAME__, __func__, __LINE__, fmt "\n", ##__VA_ARGS__)
#    define NM_I(fmt, ...) \
        ::nm::richLog(::nm::errLv::INFO, __FILENAME__, __func__, __LINE__, fmt "\n", ##__VA_ARGS__)
#else
#    define NM_E(fmt, ...) void()
#    define NM_W(fmt, ...) void()
#    define NM_I(fmt, ...) void()
#endif
#ifdef NM_DEBUG
#    define NM_DE(fmt, ...) NM_E(fmt, ##__VA_ARGS__)
#    define NM_DW(fmt, ...) NM_W(fmt, ##__VA_ARGS__)
#    define NM_DI(fmt, ...) NM_I(fmt, ##__VA_ARGS__)
#else
#    define NM_DE(fmt, ...) void()
#    define NM_DW(fmt, ...) void()
#    define NM_DI(fmt, ...) void()
#endif

#undef NM_SIDE_FUNC_3
#define NM_SIDE_FUNC_3(paramPtr, expr, ret) { \
    return paramPtr ? expr : ret; \
}
