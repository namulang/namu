#include "TestCase.hpp"
#include <independentor.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace wrd
{
    #define CLASS TestCase
    using namespace std;
    using namespace std::chrono;

    bool CLASS::test()
    {
        _start = getTime();

        string msg = _onTest();

		bool ret = msg != "";
        _printResult(ret, msg);
		return ret;
    }

	std::string CLASS::getHeader() const
	{
		stringstream sout;
        sout    << setw(6) << setfill(' ') << getTime().count() << "ms | "
                << setw(20) << setfill(' ') << getName();
		return sout.str();
	}

    void CLASS::_printResult(bool is_failed, string msg)
    {
        typedef PlatformAPI::ConsoleColor Color;
        Color   fore = is_failed ? PlatformAPI::RED : PlatformAPI::LIGHTGREEN,
                back = PlatformAPI::BLACK;

        PlatformAPI::updateConsoleColor(PlatformAPI::YELLOW, back);
        cout << "[";

        PlatformAPI::updateConsoleColor(back, fore);
		cout << getHeader().c_str();
        PlatformAPI::updateConsoleColor(PlatformAPI::YELLOW, back);
        cout << "] ";

        PlatformAPI::updateConsoleColor(PlatformAPI::CYAN, PlatformAPI::BLACK);
        cout << msg << "\n";
        PlatformAPI::updateConsoleColor(PlatformAPI::LIGHTGRAY, PlatformAPI::BLACK);
    }

	milliseconds CLASS::getTime() const
	{
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()) - _start;
	}
}
