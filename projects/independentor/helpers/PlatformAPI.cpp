#include "PlatformAPI.hpp"
#if WRD_BUILD_PLATFORM == WRD_TYPE_WINDOWS
#  include <windows.h>
#elif WRD_BUILD_PLATFORM == WRD_TYPE_LINUX
#    include <unistd.h>
#    include <vector>
#    include <string>
#    include <algorithm>
#    include <iostream>
#endif
#include <time.h>

namespace WRD
{
    #define CLASS PlatformAPI
    using namespace std;

#ifdef WRD_BUILD_PLATFORM_IS_LINUX
    namespace
    {
        bool _isAnsiColorTerminal()
        {
            static vector<string> samples = {
                "xterm", "rxvt", "vt100",
                "linux", "screen",
            };
            return find_if(samples.begin(), samples.end(), [](const string& e) {
                string use = getenv("TERM");
                return use.find(e) != string::npos;
            }) != samples.end();
        }

        void _printColorCharacter(CLASS::ConsoleColor fore, CLASS::ConsoleColor back)
        {
            static vector<string> fores = {
                "\x1B[0;30m", "\x1B[0;34m", "\x1B[0;32m", "\x1B[0;36m", // black, blue, green, cyan
                "\x1B[0;31m", "\x1B[0;35m", "\x1B[0;33m", "\x1B[0;37m", // red, purple, yellow, white
                "\x1B[1;30m", "\x1B[1;34m", "\x1B[1;32m", "\x1B[1;36m", // same ones but more lighter than above.
                "\x1B[1;31m", "\x1B[1;35m", "\x1B[1;33m", "\x1B[1;37m"
            };
            static vector<string> backs = {
                "\x1B[0;40m", "\x1B[0;44m", "\x1B[0;42m", "\x1B[0;46m", // black, blue, green, cyan
                "\x1B[0;41m", "\x1B[0;45m", "\x1B[0;43m", "\x1B[0;47m", // red, purple, yellow, white
                "\x1B[1;40m", "\x1B[1;44m", "\x1B[1;42m", "\x1B[1;46m", // black, blue, green, cyan
                "\x1B[1;41m", "\x1B[1;45m", "\x1B[1;43m", "\x1B[1;47m", // red, purple, yellow, white
            };
            cout << fores[fore] << backs[back];
        }
    }
#endif

    void CLASS::updateConsoleColor(ConsoleColor fore, ConsoleColor back)
    {
#if WRD_BUILD_PLATFORM == WRD_TYPE_WINDOWS
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), back << 4 | fore);
#elif WRD_BUILD_PLATFORM == WRD_TYPE_LINUX
        static bool is_terminal_supporting = _isAnsiColorTerminal();
        if( ! is_terminal_supporting) {
            // TODO: may need to print some error.
            cout << "ERROR!";
            return;
        }
        _printColorCharacter(fore, back);
#endif
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
