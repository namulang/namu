#include "PlatformAPI.hpp"
#ifdef WIN32
#   include <windows.h>
#endif

namespace NE
{
    #define CLASS PlatformAPI

    void CLASS::updateConsoleColor(ConsoleColor fore, ConsoleColor back)
    {
        if(BuildFeatures::Platform::get() == BuildFeatures::WINDOW)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), back << 4 | fore);
    }
}