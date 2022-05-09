#include "defVarExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(defVarExpr)

    str me::run(const ucontainable& args) {
        const std::string& name = _param.getName();
        node& org = (node&) *_param.getOrigin();
        wbool res = _where ? _where->add(name, org) : thread::get()._getNowFrame().pushLocal(name, org);
        if(!res)
            WRD_E("define variable %s is failed.", name.c_str());

        return str(org);
    }

    WRD_VERIFY(defVarExpr, defineVariable, {
        const param& p = it.getParam();
        WRD_DI("verify: define variable %s", p.getName().c_str());

        if(!it.run())
            _err(errCode::CANT_DEF_VAR, p.getName().c_str(), p.getOrigin().getType().getName().c_str());
    })
}
