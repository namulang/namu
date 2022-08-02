#pragma once

#include "buildFeature.hpp"

namespace namu {

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

        static const std::string& getConsoleFore(consoleColor fore);
        static const std::string& getConsoleBack(consoleColor back);
        static std::string createNowTime(const std::string& strftime_format);
    };
}
