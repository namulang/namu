#include "muna.hpp"
#include "../../builtin/container/native/tndumMap.hpp"

namespace wrd {

    WRD_DEF_ME(muna)

    nbicontainer& me::subs() {
        static ndumMap inner;
        return inner;
    }

}
