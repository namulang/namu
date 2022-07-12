#include "typeNode.hpp"
#include "../builtin/container/native/tndumMap.hpp"

namespace wrd {
    WRD_DEF_ME(typeNode)

    nbicontainer& me::subs() {
        static ndumMap inner;
        return inner;
    }

    str me::run(const ucontainable& args) {
        return str();
    }

    const wtype& me::getEval() const {
        return _type;
    }
}
