#include "baseFunc.hpp"
#include "params.hpp"
#include "../frame/frameInteract.hpp"
#include "../visitor/visitor.hpp"
#include "../frame/frame.hpp"
#include "../builtin/primitive/nInt.hpp"
#include "../builtin/primitive/nByte.hpp"

namespace namu {

    NAMU(DEF_ME(baseFunc), DEF_VISIT())

    me::priority me::prioritize(const args& a) const {
        const params& ps = getParams();
        if(a.len() != ps.len()) return node::NO_MATCH;

        int n = 0;
        priority max = node::EXACT; // begining from lv0.
        for(const auto& e : a) {
            str t = e.getEval();
            if(!t) return NAMU_W("t == null"), NO_MATCH;
            str p = ps[n++].getOrigin().as<node>();
            if(!t->isComplete()) return NO_MATCH;

            // overloading priority algorithm:
            //  each subs can be categorized into 3 level of priority.
            //  the priority against func call will be computed maximum priority value between the argument and its paramter.
            //  the lower value of 'max', the more check needed.
            priority newP = _prioritize(*p, *t);
            max = newP > max ? newP : max;
            if(max == node::NO_MATCH)
                return node::NO_MATCH;
        }

        return max;
    }

    me::priority me::_prioritize(const node& param, const node& arg) const {
        if(arg.getType() == param.getType()) return node::EXACT;
        if(_isNatureNumber(param) && _isNatureNumber(arg)) return node::NUMERIC;
        if(arg.isImpli(param)) return node::IMPLICIT;

        return node::NO_MATCH;
    }

    const params& me::getParams() const {
        static params inner;
        return inner;
    }

    nbool me::setRet(const node& newRet) {
        return false;
    }

    nbool me::_isNatureNumber(const node& it) const {
        return it.isSub<nInt>() || it.isSub<nByte>();
    }
}
