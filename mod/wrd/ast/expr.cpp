#include "expr.hpp"
#include "../builtin/container/native/tnmap.inl"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(expr)

    nbicontainer& me::subs() {
        static nmap inner;
        return inner;
    }
}
