#include "consoleStream.hpp"
#include <iostream>

namespace namu {

    NAMU_DEF_ME(consoleStream)

    me::consoleStream(): super(false) {}

    const char* me::getName() const {
        return "consoleStream";
    }

    nbool me::dump(const char* message) {
        using std::cout;
        if(super::dump(message)) return true;

        cout << message;
        return false;
    }
}
