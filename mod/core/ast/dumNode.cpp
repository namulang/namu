#include "dumNode.hpp"
#include "../builtin/container/native/tndumMap.hpp"
#include "../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(dumNode), DEF_VISIT())

    const ntype& me::getType() const {
        return ttype<node>::get();
    }

    nbool me::canRun(const args& a) const {
        return false;
    }

    str me::run(const args& a) {
        return str();
    }

    clonable* me::clone() const {
        return new me(*this);
    }

    nbicontainer& me::subs() {
        static ndumMap inner;
        return inner;
    }
}
