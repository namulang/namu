#include "runExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"
#include "../../frame/thread.hpp"
#include "../../builtin/primitive/nVoid.hpp"
#include "getExpr.hpp"

namespace namu {

    NAMU_DEF_ME(runExpr)

    me::runExpr(const node& meObj, const node& subject, const args& a):
            _me(meObj), _args(a), _subject(subject)  {}
    me::runExpr(const node& meObj, const args& a): _me(meObj), _args(a), _subject(meObj) {}

    str me::run(const args& a) {
        str sub = _getSub(_args);
        if(!sub) return NAMU_E("_subject.as<node>() returns null"), str();

        str ret = sub->run(_args);
        _args.setMe(nulOf<baseObj>());
        return ret;
    }

    node& me::getMe() { return *_me; }
    const node& me::getMe() const { return *_me; }

    const node& me::getSubject() const { return *_subject; }
    node& me::getSubject() { return *_subject; }

    args& me::getArgs() { return _args; }
    const args& me::getArgs() const { return _args; }

    void me::setMe(const node& newMe) {
        _me.bind(newMe);
    }

    str me::_getSub(const args& a) const {
        tstr<baseObj> me = _me->as<baseObj>();
        if(!me) return NAMU_E("me Obj as baseObj == null"), str();
        if(!_subject) return NAMU_E("_subject as node == null"), str();

        if(!nul(a))
            a.setMe(*me);
        getExpr& cast = _subject->cast<getExpr>();
        if(!nul(cast))
            cast.setMe(*me);

        return _subject->as<node>();
    }

    str me::_getSub() const {
        return _getSub(nulOf<args>());
    }

    const node& me::getEval() const {
        str sub = _getSub();
        if(!sub) return NAMU_E("_subject.as<node>() returns null"), nulOf<node>();

        const func& f = sub.cast<func>();
        return nul(f) ? sub->getEval() : f.getRet();
    }



    NAMU_VERIFY({
        NAMU_DI("verify: runExpr: is it possible to run?");
        if(nul(it.getMe())) return _srcErr(errCode::CANT_CAST_TO_NODE);

        tstr<baseObj> me = it.getMe().as<baseObj>();
        if(!me) return _srcErr(errCode::CANT_CAST_TO_NODE);

        node& anySub = it.getSubject();
        if(nul(anySub)) return _srcErr(errCode::SUB_NOT_EXIST);

        args& a = it.getArgs();
        a.setMe(*me);

        getExpr& cast = anySub.cast<getExpr>();
        if(!nul(cast))
            cast.setMe(*me);

        str derivedSub = anySub.as<node>();
        if(!derivedSub) return _srcErr(errCode::CANT_ACCESS, me->getType().getName().c_str(), "sub-node");
        if(!derivedSub->canRun(it.getArgs())) return _srcErr(errCode::OBJ_WRONG_ARGS, it.getArgs().asStr().c_str());

        a.setMe(nulOf<baseObj>());

        NAMU_DI("...verified: runExpr: is it possible to run?");
    })

    NAMU_VERIFY({
        NAMU_DI("verify: runExpr: visit subNodes");
        verify(it.getMe());

        NAMU_DI("...verified: runExpr: visit subNodes");
    })
}
