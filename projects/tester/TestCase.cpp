#include "TestCase.hpp"
#include <independentor.hpp>
#include <iomanip>
#include <iostream>

namespace NE
{
    #define CLASS TestCase
    using namespace std;
    using namespace std::chrono;
    
    void CLASS::test()
    {
        milliseconds prev = _getTime();
        string result = _onTest();
        _printResult(result, (_getTime() - prev));
    }

    void CLASS::_printResult(string result, milliseconds process_time) const
    {        
        typedef PlatformAPI::ConsoleColor Color;
        Color   fore = result == "" ? PlatformAPI::LIGHTGREEN : PlatformAPI::RED,
                back = PlatformAPI::BLACK;
        
        PlatformAPI::updateConsoleColor(PlatformAPI::YELLOW, back);
        cout << "[";
        
        PlatformAPI::updateConsoleColor(back, fore);
        cout    << setw(6) << setfill(' ') << process_time.count() << "ms | " 
                << setw(20) << setfill(' ') << getName();

        PlatformAPI::updateConsoleColor(PlatformAPI::YELLOW, back);
        cout << "] ";
        
        PlatformAPI::updateConsoleColor(PlatformAPI::CYAN, PlatformAPI::BLACK);
        cout << result << "\n";
        PlatformAPI::updateConsoleColor(PlatformAPI::LIGHTGRAY, PlatformAPI::BLACK);
    }

    milliseconds CLASS::_getTime()
    {
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    }

    vector<TestCase*>& CLASS::getTests() {
        static vector<TestCase*> collections;
        return collections;
    }
}