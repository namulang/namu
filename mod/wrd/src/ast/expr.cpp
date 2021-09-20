#include "expr.hpp"
#include "../builtin/container/native/tnarr.inl"

namespace wrd {

    WRD_DEF_ME(expr)

    ncontainer& me::subs() {
        static narr inner;
        return inner;
    }
}
