#include "defVarExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(defVarExpr)

    me::defVarExpr(const std::string& name, const node& org): _org(org), _name(name) {}
    me::defVarExpr(const std::string& name, const node& org, const scope& where): _org(org),
            _name(name), _where(where) {}

    str me::run(const ucontainable& args) {
        const std::string& name = _name;
        node& org = (node&) *_org;
        wbool res = _where ? _where->add(name, org) : thread::get()._getNowFrame().pushLocal(name, org);
        if(!res)
            WRD_E("define variable %s is failed.", name.c_str());

        return _org;
    }

    const std::string& me::getName() const { return _name; }
    const node& me::getOrigin() const { return *_org; }

    /// @return null of scope if this variable will be defined to local scope.
    const scope& me::getWhere() const { return *_where; }
    void me::setWhere(const scope& new1) { _where.bind(new1); }

    const wtype& me::getEvalType() const {
        return _org->getEvalType();
    }



    WRD_VERIFY(defVarExpr, defineVariable, {
        const wchar* name = it.getName().c_str();
        const wchar* typeName = it.getOrigin().getType().getName().c_str();
        WRD_DI("verify: define variable %s", name);

        const scopes& top = thread::get().getNowFrame().getTop();
        if(nul(top)) return;
        if(top.getContainer().has(it.getName()))
            return _srcErr(errCode::ALREADY_DEFINED_VAR, name, typeName);

        if(!it.run())
            _srcErr(errCode::CANT_DEF_VAR, name, typeName);
    })

}
