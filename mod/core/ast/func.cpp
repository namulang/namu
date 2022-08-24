#include "func.hpp"
#include "params.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verifier.hpp"
#include "../frame/frameInteract.hpp"

namespace namu {

    NAMU_DEF_ME(func)

    nbool me::_canRun(const args& a) const {
        const params& ps = getParams();
        if(a.len() != ps.len()) return false;

        int n = 0;
        for(const auto& e : a) {
            const node& t = e.getEval();
            str p = ps[n++].getOrigin().as<node>();
            if(nul(t)) return NAMU_W("t == null"), false;
            if(!t.isImpli(*p))
                return false;
        }

        return true;
    }

    nbool me::canRun(const args& a) const {
        baseObj& me = a.getMe();
        if(nul(me)) return _canRun(a);

        return _canRun(a);
    }

    const params& me::getParams() const {
        static params inner;
        return inner;
    }

    NAMU_VERIFY({
        NAMU_DI("verify: func: param check");

        /*for(const param& p : it.getParams()) {
        }*/

        NAMU_DI("...verified: func: param check");
    })
}
