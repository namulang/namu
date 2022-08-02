#include "defVarExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"

namespace namu {

    NAMU_DEF_ME(defVarExpr)

    me::defVarExpr(const std::string& name, const node& org): _org(org), _name(name) {}
    me::defVarExpr(const std::string& name, const node& org, const scope& where): _org(org),
            _name(name), _where(where) {}

    str me::run(const ucontainable& args) {
        const std::string& name = _name;
        node& org = (node&) *_org;
        nbool res = _where ? _where->add(name, org) : thread::get()._getNowFrame().pushLocal(name, org);
        if(!res)
            NAMU_E("define variable %s is failed.", name.c_str());

        return _org;
    }

    const std::string& me::getName() const { return _name; }
    const node& me::getOrigin() const { return *_org; }

    /// @return null of scope if this variable will be defined to local scope.
    const scope& me::getWhere() const { return *_where; }
    void me::setWhere(const scope& new1) { _where.bind(new1); }

    const node& me::getEval() const {
        return _org->getEval();
    }



    NAMU_VERIFY(defVarExpr, defineVariable, {
        NAMU_DI("verify: defVarExpr: check duplication");
        const scopes& top = thread::get().getNowFrame().getTop();
        const node& eval = it.getEval();
        const ntype& t = eval.getType();
        const nchar* typeName = nul(t) ? "null" : t.getName().c_str();
        if(nul(top)) return;
        if(top.getContainer().has(it.getName()))
            return _srcErr(errCode::ALREADY_DEFINED_VAR, it.getName().c_str(), typeName);


        // 'check duplication' must be front of 'is %s definable':
        std::string name = it.getName();
        NAMU_DI("verify: defVarExpr: is %s definable?", name.c_str());
        if(name == "") return _srcErr(errCode::HAS_NO_NAME);
        const node& org = it.getOrigin();
        if(nul(org)) return _srcErr(errCode::NO_ORIGIN, name.c_str());

        if(nul(t))
            _srcErr(errCode::CANT_DEF_VAR, name.c_str(), typeName);

        nbool res = it._where ? it._where->add(name.c_str(), eval) : thread::get()._getNowFrame()
                .pushLocal(name, eval);
        if(!res)
            NAMU_E("define variable %s is failed.", name.c_str());
    })
}
