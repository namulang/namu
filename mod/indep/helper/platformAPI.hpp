#pragma once

#include "buildFeature.hpp"
#include <vector>

namespace namu {

    class _nout platformAPI {
        NAMU_ME(platformAPI)

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
        static std::vector<std::string> callstack();
        static std::string demangle(const nchar* org);
        static std::string filterDemangle(const nchar* org);
        static std::string getExecPath();
        static std::string exec(const std::string& cmd);
        static nulong getNowMs();
    };
}
