#include "expr.hpp"
#include "../builtin/container/native/tnmap.inl"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verifier.hpp"

namespace namu {

    WRD_DEF_ME(expr)

    nbicontainer& me::subs() {
        static nmap inner;
        return inner;
    }

    wbool me::canRun(const ucontainable& args) const { return args.len() == 0; }
    const src& me::getSrc() const { return *_src; }
    const point& me::getPos() const { return _pos; }

    void me::_setSrc(const src& newSrc) {
        _src.bind(newSrc);
    }

    void me::setPos(const point& newPos) {
        _pos = newPos;
    }
}
