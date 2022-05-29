#include "literalExpr.hpp"

namespace wrd {

    WRD_DEF_ME(literalExpr)

    me::literalExpr(const node& n): _str(n) {}

    str me::run(const ucontainable& args) {
        return _str;
    }

    const wtype& me::getEvalType() const {
        // _str always binds to some object.
        return _str->getType();
    }

    str& me::getStr() { return _str; }
    const str& me::getStr() const { return _str; }
}
