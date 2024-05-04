#include "enablesZone.hpp"
#include "logger.hpp"

namespace namu {
    NAMU(DEF_ME(enablesZone))

    me::enablesZone() {
        _enables = logger::get().getEnables();
    }

    me::~enablesZone() {
        logger::get().setEnables(_enables);
    }

    const enables& me::getPrev() const { return _enables; }

    void me::setPrev() { logger::get().setEnables(getPrev()); }
}
