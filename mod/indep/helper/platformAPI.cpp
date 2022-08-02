#include "platformAPI.hpp"
#if NAMU_BUILD_PLATFORM == NAMU_TYPE_WINDOWS
#  include <windows.h>
#elif NAMU_BUILD_PLATFORM == NAMU_TYPE_LINUX || NAMU_BUILD_PLATFORM == NAMU_TYPE_MACOS
#    include <unistd.h>
#    include <vector>
#    include <string>
#    include <algorithm>
#    include <iostream>
#endif
#include <time.h>

namespace namu {

    NAMU_DEF_ME(platformAPI)
    using namespace std;

#if defined(NAMU_BUILD_PLATFORM_IS_LINUX) || defined(NAMU_BUILD_PLATFORM_IS_MAC)
    namespace {
        bool _isAnsiColorTerminal() {
            static vector<const nchar*> samples = {
                "xterm", "rxvt", "vt100",
                "linux", "screen",
            };
            return find_if(samples.begin(), samples.end(), [](const string& e) {
                string use = getenv("TERM");
                return use.find(e) != string::npos;
            }) != samples.end();
        }
    }
#endif

    const std::string& me::getConsoleFore(consoleColor fore) {
#if NAMU_BUILD_PLATFORM == NAMU_TYPE_WINDOWS
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), platformAPI::BLACK << 4 | fore);
        static std::string inner;
        return inner;
#elif NAMU_BUILD_PLATFORM == NAMU_TYPE_LINUX || NAMU_BUILD_PLATFORM == NAMU_TYPE_MACOS
        static bool is_terminal_supporting = _isAnsiColorTerminal();
        if( ! is_terminal_supporting) {
            static string inner;
            return inner;
        }

        static vector<string> fores = {
            "\x1B[0;30m", "\x1B[0;34m", "\x1B[0;32m", "\x1B[0;36m", // black, blue, green, cyan
            "\x1B[0;31m", "\x1B[0;35m", "\x1B[0;33m", "\x1B[0;37m", // red, purple, yellow, white
            "\x1B[1;30m", "\x1B[1;34m", "\x1B[1;32m", "\x1B[1;36m", // same ones but more lighter than above.
            "\x1B[1;31m", "\x1B[1;35m", "\x1B[1;33m", "\x1B[1;37m"
        };
        return fores[fore];
#endif
    }

    const std::string& me::getConsoleBack(consoleColor back) {
        static std::string inner;
#if NAMU_BUILD_PLATFORM == NAMU_TYPE_WINDOWS
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), back << 4 | WHITE);
        return inner;

#elif NAMU_BUILD_PLATFORM == NAMU_TYPE_LINUX || NAMU_BUILD_PLATFORM == NAMU_TYPE_MACOS
        static bool is_terminal_supporting = _isAnsiColorTerminal();
        if( ! is_terminal_supporting)
            return inner;

        static vector<string> backs = {
            "\x1B[0;40m", "\x1B[0;44m", "\x1B[0;42m", "\x1B[0;46m", // black, blue, green, cyan
            "\x1B[0;41m", "\x1B[0;45m", "\x1B[0;43m", "\x1B[0;47m", // red, purple, yellow, white
            "\x1B[1;40m", "\x1B[1;44m", "\x1B[1;42m", "\x1B[1;46m", // black, blue, green, cyan
            "\x1B[1;41m", "\x1B[1;45m", "\x1B[1;43m", "\x1B[1;47m", // red, purple, yellow, white
        };
        return backs[back];
#endif
    }

    string me::createNowTime(const string& strftime_format) {
        time_t t = time(0);
        struct tm* timeinfo = localtime(&t);

        char buffer[80];
        strftime(buffer, 80, strftime_format.c_str(), timeinfo);

        return buffer;
    }
}
