#include "getExpr.hpp"
#include "../../frame/thread.hpp"
#include "../node.inl"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(getExpr), DEF_VISIT())

    me::getExpr(const std::string& name): _name(name) {}
    me::getExpr(const std::string& name, const args& a): _name(name), _args(a) {}
    me::getExpr(const node& me, const std::string& name): _me(me), _name(name) {}
    me::getExpr(const node& me, const std::string& name, const args& a): _me(me), _name(name), _args(a) {}

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

    const std::string& me::getSubName() const {
        return _name;
    }

    void me::setSubName(const std::string& new1) {
        _name = new1;
    }

    /// @return nullable
    const args& me::getSubArgs() const {
        return *_args;
    }

    args& me::getSubArgs() {
        return *_args;
    }

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

    void me::setMe(const node& newMe) {
        _me.bind(newMe);
    }

    clonable* me::deepClone() const {
        me* ret = (me*) clone();
        if(_args) ret->_args.bind((args*) _args->deepClone());

        return ret;
    }
}
