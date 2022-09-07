#include "func.hpp"
#include "expr.hpp"
#include "../builtin/container/native/tnmap.inl"
#include "args.hpp"
#include "../frame/frame.hpp"

namespace namu {

    NAMU_DEF_ME(expr)

    nbicontainer& me::subs() {
        static nmap inner;
        return inner;
    }

    nbool me::canRun(const args& a) const { return a.len() == 0; }
    const src& me::getSrc() const { return *_src; }
    const point& me::getPos() const { return _pos; }

    void me::_setSrc(const src& newSrc) {
        _src.bind(newSrc);
    }

    void me::setPos(const point& newPos) {
        _pos = newPos;
    }
}
