#include "func.hpp"
#include "params.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verifier.hpp"

namespace namu {

    WRD_DEF_ME(func)

    wbool me::canRun(const ucontainable& args) const {
        const params& ps = getParams();
        if(args.len() != ps.len()) return false;

        int n = 0;
        for(const auto& e : args) {
            const node& t = e.getEval();
            if(nul(t)) return WRD_W("t == null"), false;
            if(!t.isImpli(ps[n++].getOrigin()))
                return false;
        }

        return true;
    }

    const params& me::getParams() const {
        static params inner;
        return inner;
    }

    WRD_VERIFY({
        WRD_DI("verify: func: param check");

        /*for(const param& p : it.getParams()) {
        }*/
    })
}
