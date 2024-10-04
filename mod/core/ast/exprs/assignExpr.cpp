#include "assignExpr.hpp"

#include "../../frame/thread.hpp"
#include "../../worker/visitor/visitor.hpp"
#include "../obj.hpp"

namespace nm {

    NM(DEF_ME(assignExpr), DEF_VISIT())

    me::assignExpr(const node& lhs, const node& rhs): _lhs(lhs), _rhs(rhs) {}

    str me::run(const args& a) {
        iter e = _getScopeIterOfLhs(); // e exists. verified.

        str ret = _rhs->as<node>();
        e.setVal(*ret);
        return ret;
    }

    str me::getEval() const { return _rhs->getEval(); }

    const node& me::getLeft() const { return *_lhs; }

    const node& me::getRight() const { return *_rhs; }

    void me::onCloneDeep(const clonable& from) {
        me& rhs = (me&) from;
        if(rhs._lhs) _lhs.bind((node*) rhs._lhs->cloneDeep());
        if(rhs._rhs) _rhs.bind((node*) rhs._rhs->cloneDeep());
    }

    me::iter me::_getScopeIterOfLhs() {
        getExpr& cast = _lhs THEN(template cast<getExpr>());
        if(nul(cast)) return iter();

        // TODO: elementExpr

        str ased = cast THEN(getMe()) THEN(template as<node>());
        if(!ased) return NM_E("ased == null"), iter();

        iter ret = ased->subs().iterate(cast.getName());
        while(ret) {
            if(!nul(ret.getVal<baseObj>())) return ret;

            ++ret;
        }

        return iter();
    }
} // namespace nm
