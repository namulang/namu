#include "func.hpp"
#include "params.hpp"
#include "../frame/frameInteract.hpp"
#include "../visitor/visitor.hpp"
#include "../frame/frame.hpp"

namespace namu {

    NAMU(DEF_ME(func), DEF_VISIT())

    nbool me::canRun(const args& a) const {
        const params& ps = getParams();
        if(a.len() != ps.len()) return false;

        int n = 0;
        for(const auto& e : a) {
            str t = e.getEval();
            str p = ps[n++].getOrigin().as<node>();
            if(!t) return NAMU_W("t == null"), false;
            if(!t->isImpli(*p))
                return false;
        }

        return true;
    }

    const params& me::getParams() const {
        static params inner;
        return inner;
    }
}
