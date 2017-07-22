#include "PlatformAPI.hpp"
#ifdef WIN32
#   include <windows.h>
#endif
#include <time.h>

namespace NE
{
    #define CLASS PlatformAPI
    using namespace std;

    void CLASS::updateConsoleColor(ConsoleColor fore, ConsoleColor back)
    {
        if(BuildFeatures::Platform::get() == BuildFeatures::WINDOW)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), back << 4 | fore);
    }

    string CLASS::createCurrentTime(const string& strftime_format)
    {
        time_t t = time(0);
        struct tm* timeinfo = localtime(&t);
        
        char buffer[80];
        strftime(buffer, 80, strftime_format.c_str(), timeinfo);

        return buffer;
    }
}