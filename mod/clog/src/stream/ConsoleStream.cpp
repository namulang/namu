#include "ConsoleStream.hpp"
#include <iostream>

namespace wrd {

    WRD_DEF_THIS(ConsoleStream)

    const char* This::getName() const { return "ConsoleStream"; }

    wbool This::dump(const char* message) {
        using std::cout;
        if(Super::dump(message)) return true;

        cout << message << "\n";
        return false;
    }
}
