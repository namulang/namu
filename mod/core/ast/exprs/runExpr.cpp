#include "runExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"
#include "../../frame/thread.hpp"
#include "../../builtin/primitive/nVoid.hpp"

namespace namu {

    NAMU_DEF_ME(runExpr)

    me::runExpr(const node& meObj, const std::string& name, const narr& args):
            _me(meObj), _args(args), _name(name)  {}
    me::runExpr(const node& meObj, const narr& args): _me(meObj), _args(args) {}

    str me::run(const ucontainable& args) {
        str me = _me->as<node>();
        if(!me) return NAMU_E("_me as node == null"), str();

        return me->run(_name, _args);
    }

    node& me::getMe() { return *_me; }
    const node& me::getMe() const { return *_me; }

    const std::string& me::getName() const { return _name; }
    std::string& me::getName() { return _name; }

    narr& me::getArgs() { return _args; }
    const narr& me::getArgs() const { return _args; }

    void me::setMe(const node& newMe) {
        _me.bind(newMe);
    }

    const node& me::getEval() const {
        if(!_me) return nulOf<node>();

        str me = _me->as<node>();
        if(!me) return nulOf<node>();

        const node& sub = me->sub(getName(), getArgs());
        if(nul(sub)) return NAMU_W("sub is null"), nulOf<node>();

        const func& f = sub.cast<func>();
        return nul(f) ? sub.getEval() : f.getRet();
    }



    namespace {
        narr _evalArgs(const narr& args) {
            narr ret;
            for(auto& e : args)
                ret.add(e.getEval());
            return ret;
        }
    }

    NAMU_VERIFY({
        NAMU_DI("verify: runExpr: is it possible to run?");

        if(nul(it.getMe())) return _srcErr(errCode::CANT_CAST_TO_NODE);

        str me = it.getMe().as<node>();
        if(!me) return _srcErr(errCode::CANT_CAST_TO_NODE);

        str sub = me->sub(it.getName(), _evalArgs(it.getArgs()));
        if(!sub) return _srcErr(errCode::CANT_ACCESS, me->getType().getName().c_str(), it.getName().c_str());
        if(!sub->canRun(it.getArgs())) return _srcErr(errCode::OBJ_WRONG_ARGS);
    })

    NAMU_VERIFY({
        NAMU_DI("verify: runExpr: visit subNodes");
        verify(it.getMe());
    })
}
