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

    const node& me::getEval() const {
        str got = _get();
        if(!got)
            return nulOf<node>();
        return got->getEval();
    }

    str me::run(const args& a) {
        // believe that this expression was checked to be valid.
        return _get();
    }

    const std::string& me::getSubName() const { return _name; }

    /// @return nullable
    const args& me::getSubArgs() const { return *_args; }

    str me::_get() const {
        NAMU_DI("_name=%s", _name.c_str());
        const node& me = getMe();
        if(nul(me)) return NAMU_E("me == null"), str();
        str evalMe = me.as<node>();
        if(!evalMe) return NAMU_E("from == null"), str();

        std::string argsName = _args ? _args->asStr().c_str() : "{}";
        NAMU_DI("%s.sub(%s, %s)", evalMe->getType().getName().c_str(), _name.c_str(), argsName.c_str());
        if(!_args) return str(evalMe->sub(_name));

        return str(evalMe->sub(_name, *_args));
    }
}
