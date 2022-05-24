#pragma once

#include "buildFeature.hpp"

namespace wrd {

    class _wout platformAPI {
        WRD_DECL_ME(platformAPI)

    public:
        enum consoleColor {
            CONSOLE_COLOR_START = 0,
            BLACK=CONSOLE_COLOR_START, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
            LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
            LIGHTMAGENTA, YELLOW,
            CONSOLE_COLOR_END,
            WHITE = CONSOLE_COLOR_END
        };

        static void updateConsoleFore(consoleColor fore);
        static void updateConsoleBack(consoleColor back);
        static std::string createCurrentTime(const std::string& strftime_format);
    };
}
