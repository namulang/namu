#include "muna.hpp"
#include "../../builtin/container/native/tndumMap.hpp"

namespace namu {

    NAMU_DEF_ME(muna)

    nbicontainer& me::subs() {
        static ndumMap inner;
        return inner;
    }

}
