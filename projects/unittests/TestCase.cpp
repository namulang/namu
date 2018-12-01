#include "TestCase.hpp"
#include <independentor.hpp>
#include <iomanip>
#include <iostream>

namespace wrd
{
    #define CLASS TestCase
    using namespace std;
    using namespace std::chrono;
    
    bool CLASS::test()
    {
        milliseconds prev = getTime();
        string msg = _onTest();
		bool ret = msg != "";
        printResult(ret, getName(), msg, (getTime() - prev));

		return ret; 
    }

    void CLASS::printResult(bool is_failed, string name, string msg, milliseconds process_time)
    {        
        typedef PlatformAPI::ConsoleColor Color;
        Color   fore = is_failed ? PlatformAPI::RED : PlatformAPI::LIGHTGREEN,
                back = PlatformAPI::BLACK;
        
        PlatformAPI::updateConsoleColor(PlatformAPI::YELLOW, back);
        cout << "[";
        
        PlatformAPI::updateConsoleColor(back, fore);
        cout    << setw(6) << setfill(' ') << process_time.count() << "ms | " 
                << setw(20) << setfill(' ') << name;

        PlatformAPI::updateConsoleColor(PlatformAPI::YELLOW, back);
        cout << "] ";
        
        PlatformAPI::updateConsoleColor(PlatformAPI::CYAN, PlatformAPI::BLACK);
        cout << msg << "\n";
        PlatformAPI::updateConsoleColor(PlatformAPI::LIGHTGRAY, PlatformAPI::BLACK);
    }

    milliseconds CLASS::getTime()
    {
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    }

	CLASS::TestCases& CLASS::getTests()
	{
        static TestCases collections;
        return collections;
    }
}
