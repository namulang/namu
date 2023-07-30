#include "func.hpp"
#include "expr.hpp"
#include "../builtin/container/native/tnmap.inl"
#include "args.hpp"
#include "../frame/frame.hpp"

namespace namu {

    NAMU_DEF_ME(expr)

    nbool me::exprType::isImpli(const type& to) const {
        return to.isSub<node>();
    }

    str me::exprType::asImpli(const node& from, const type& to) const {
        return str(((node&)from).run());
    }

    nbicontainer& me::subs() {
        static nmap inner;
        return inner;
    }

    nbool me::isImpli(const type& to) const {
        return getEval()->isSub(to);
    }

    str me::asImpli(const type& to) const {
        me* unconst = const_cast<me*>(this);
        str run = unconst->run();
        if(!run)
            return run;
        return run->asImpli(to);
    }

    nbool me::canRun(const args& a) const {
        return a.len() == 0;
    }

    const src& me::getSrc() const {
        return *_src;
    }

    const point& me::getPos() const {
        return _pos;
    }

    void me::_setSrc(const src& newSrc) {
        _src.bind(newSrc);
    }

    void me::_setPos(const point& newPos) {
        _pos = newPos;
    }
}
