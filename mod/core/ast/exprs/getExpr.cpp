#include "getExpr.hpp"
#include "../../frame/thread.hpp"
#include "../node.inl"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(getExpr), DEF_VISIT())

    const node& me::getMe() const {
        if(!_me)
            return thread::get().getNowFrame();
        return *_me;
    }

    str me::getEval() const {
        str got = _get(true);
        if(!got)
            return got;
        return got->getEval();
    }

    str me::run(const args& a) {
        // believe that this expression was checked to be valid.
        return _get(false);
    }

    const std::string& me::getSubName() const { return _name; }

    /// @return nullable
    const args& me::getSubArgs() const { return *_args; }

    str me::_get(nbool evalMode) const {
        NAMU_DI("_name=%s", _name.c_str());
        const node& me = getMe();
        if(nul(me)) return NAMU_E("me == null"), str();

        str evalMe = evalMode ? me.getEval() : me.as<node>();
        if(!evalMe) return NAMU_E("from == null"), str();
        if(evalMode)
            evalMe = evalMe->as<node>();

        std::string argsName = _args ? _args->asStr().c_str() : "{}";
        NAMU_DI("%s.sub(%s, %s)", evalMe->getType().getName().c_str(), _name.c_str(), argsName.c_str());
        if(!_args) return evalMe->sub(_name);

        return evalMe->sub(_name, *_args);
    }
}
