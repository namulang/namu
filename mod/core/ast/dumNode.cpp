#include "dumNode.hpp"
#include "../builtin/container/native/tndumMap.hpp"
#include "../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(dumNode), DEF_VISIT())

    nbicontainer& me::subs() {
        static ndumMap inner;
        return inner;
    }
}
