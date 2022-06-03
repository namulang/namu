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
            if(!e.getEvalType().isImpli(ps[n++].getOrigin()))
                return false;

        return true;
    }

    const params& me::getParams() const {
        static params inner;
        return inner;
    }

    WRD_VERIFY({
        for(const param& p : it.getParams()) {
            const std::string& name = p.getName();
            if(nul(name) || name.empty())
                return _srcErr(errCode::FUNC_HAS_NO_NAME);
        }
    })
}
