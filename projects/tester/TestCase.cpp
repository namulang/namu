#include "TestCase.hpp"
#include <iomanip>

namespace NE
{
    #define CLASS TestCase
    using namespace std;
    using namespace std::chrono;
    
    void CLASS::test()
    {
        milliseconds prev = _getTime();
        bool result = _onTest();
        _printResult(result, (_getTime() - prev));
    }

    void CLASS::_printResult(bool is_success, milliseconds process_time) const
    {        
        PlatformAPI::ConsoleColor fore = is_success ? PlatformAPI::LIGHTGREEN : PlatformAPI::RED;
        PlatformAPI::updateConsoleColor(fore, PlatformAPI::BLACK);
        
        cout 	<< "[ " << setw(6) << setfill(' ') 
                << process_time.count() << "ms ] ";
        
        PlatformAPI::updateConsoleColor(PlatformAPI::LIGHTGRAY, PlatformAPI::BLACK);
        cout << getName() << "\n";
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