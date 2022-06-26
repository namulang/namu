#include "func.hpp"
#include "params.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(func)

    wbool me::canRun(const ucontainable& args) const {
        const params& ps = getParams();
        if(args.len() != ps.len()) return false;

        int n = 0;
        for(const auto& e : args)
            if(!e.getEvalType().isImpli(ps[n++].getOrgType()))
                return false;

        return true;
    }

    const params& me::getParams() const {
        static params inner;
        return inner;
    }

    WRD_VERIFY({
        WRD_DI("verify: func: params lengthed 0 or first of params should be 'me'");

        const param& me = it.getParams()[0];
        if(nul(me)) return;

        if(me.getName() != func::ME) return _srcErr(errCode::FUNC_DONT_HAVE_ME);
    })

    WRD_VERIFY({
        WRD_DI("verify: func: param check");

        /*for(const param& p : it.getParams()) {
        }*/
    })
}
