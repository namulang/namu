#include "ConsoleStream.hpp"
#include <iostream>

namespace NE
{
    #define THIS ConsoleStream
    
    const char* THIS::getName() const { return "ConsoleStream"; }
    type_bool THIS::dump(const char* message)
    {
        using std::cout;
        if(Stream::dump(message)) return true;

        cout << message << "\n";
        return false;
    }
}