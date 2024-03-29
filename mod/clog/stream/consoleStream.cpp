#include "consoleStream.hpp"
#include <iostream>

namespace namu {

    NAMU_DEF_ME(consoleStream)

    me::consoleStream(): super(false) {}

    const char* me::getName() const {
        return "consoleStream";
    }

    nbool me::logBypass(const char* message) {
        using std::clog;
        if(super::logBypass(message)) return true;

        clog << message;
        return false;
    }
}
