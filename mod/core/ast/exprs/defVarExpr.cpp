#include "defVarExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(defVarExpr), DEF_VISIT())

    me::defVarExpr(const std::string& name, const node& org): _org(org), _name(name) {}
    me::defVarExpr(const std::string& name, const node& org, const scope& where): _org(org),
            _name(name), _where(where) {}

    str me::run(const args& a) {
        const std::string& name = _name;
        str org = _org->as<node>();
        if(!org) {
            NAMU_E("getting origin by %s returns null", _name.c_str());
            return org;
        }

        nbool res = _where ? _where->add(name, *org) : thread::get()._getNowFrame().pushLocal(name, *org);
        if(!res)
            NAMU_E("define variable %s is failed.", name.c_str());

        return org;
    }

    const std::string& me::getName() const { return _name; }
    const node& me::getOrigin() const { return *_org; }

    /// @return null of scope if this variable will be defined to local scope.
    const scope& me::getWhere() const { return *_where; }
    void me::setWhere(const scope& new1) { _where.bind(new1); }

    str me::getEval() const {
        return _org->getEval();
    }
}
