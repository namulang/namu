#pragma once

#include "BuildFeatures.hpp"
#include <string>

namespace WRD
{
    class PlatformAPI
    {
    public:
        enum ConsoleColor
        {
            CONSOLE_COLOR_START = 0,
            BLACK=CONSOLE_COLOR_START, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, 
            LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, 
            LIGHTMAGENTA, YELLOW, 
            CONSOLE_COLOR_END,
            WHITE = CONSOLE_COLOR_END
        };
        static void updateConsoleColor(ConsoleColor fore, ConsoleColor back);
        static std::string createCurrentTime(const std::string& strftime_format);
    };
}
