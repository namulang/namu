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
        tstr<baseObj> me = _me->as<baseObj>();
        if(!me) return NAMU_E("me Obj as baseObj == null"), str();
        if(!_subject) return NAMU_E("_subject as node == null"), str();

        _args.setMe(*me);
        getExpr& get = _subject->cast<getExpr>();
        if(!nul(get))
            get.setMe(*me);
        str subject = _subject->as<node>();
        if(!subject) return NAMU_E("_subject.as<node>() returns null"), str();

        return subject->run(_args);
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

    const node& me::getEval() const {
        str sub = _subject->as<node>();
        if(!sub) return nulOf<node>();

        const func& f = sub.cast<func>();
        return nul(f) ? sub->getEval() : f.getRet();
    }



    namespace {
        args _evalArgs(const args& a) {
            args ret;
            for(auto& e : a)
                ret.add(e.getEval());
            return ret.setMe(a.getMe());
        }
    }

    NAMU_VERIFY({
        NAMU_DI("verify: runExpr: is it possible to run?");

        if(nul(it.getMe())) return _srcErr(errCode::CANT_CAST_TO_NODE);

        tstr<baseObj> me = it.getMe().as<baseObj>();
        if(!me) return _srcErr(errCode::CANT_CAST_TO_NODE);

        str sub = it.getSubject().as<node>();
        if(!sub) return _srcErr(errCode::CANT_ACCESS, me->getType().getName().c_str(), "sub-node");
        if(!sub->canRun(it.getArgs())) return _srcErr(errCode::OBJ_WRONG_ARGS);
    })

    NAMU_VERIFY({
        NAMU_DI("verify: runExpr: visit subNodes");
        verify(it.getMe());
    })
}
