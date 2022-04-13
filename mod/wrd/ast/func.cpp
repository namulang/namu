#include "func.hpp"
#include "params.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(func)

    wbool me::canRun(const ucontainable& args) const {
        const params& ps = getParams();
        if(args.len() != ps.len()) return false;

        int n = 0;
        for(const auto& e : args)
            if(!e.isImpli(ps[n++].getOriginType()))
                return false;

        return true;
    }

    WRD_VERIFY({
        for(const param& p : it.getParams()) {
            const std::string& name = p.getName();
            if(nul(name) || name.empty())
                return _err(19);
        }
    })
}
