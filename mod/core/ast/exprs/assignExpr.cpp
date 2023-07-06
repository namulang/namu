#include "assignExpr.hpp"
#include "../../frame/thread.hpp"
#include "../obj.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(assignExpr), DEF_VISIT())

    me::iter me::_getScopeIterOfLhs() {
        if(!_lhs) return iter();

        getExpr& cast = _lhs->cast<getExpr>();
        if(nul(cast)) return iter();
        // TODO: elementExpr

        str ased = cast.getMe().getEval();
        if(!ased) return NAMU_E("ased == null"), iter();

        iter ret = ased->subs().iterate(cast.getSubName());
        while(ret) {
            if(!nul(ret.getVal<baseObj>()))
                return ret;

            ++ret;
        }

        return iter();
    }
}
