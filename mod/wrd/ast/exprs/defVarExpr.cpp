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

        const scopes& top = thread::get().getNowFrame().getTop();
        if(nul(top)) return;
        if(top.getContainer().has(p.getName()))
            return _err(errCode::ALREADY_DEFINED_VAR, p.getName().c_str(), p.getOrigin().getType().getName().c_str());

        if(!it.run())
            _err(errCode::CANT_DEF_VAR, p.getName().c_str(), p.getOrigin().getType().getName().c_str());
    })

    const param& me::getParam() const { return _param; }

    /// @return null of scope if this variable will be defined to local scope.
    const scope& me::getWhere() const { return *_where; }
    void me::setWhere(const scope& new1) { _where.bind(new1); }

    const wtype& me::getEvalType() const {
        // I need to return static eval type:
        //  if I return _param->getType(), then actually it returns
        //  dynamic eval type.
        return _param.getType();
    }
}
