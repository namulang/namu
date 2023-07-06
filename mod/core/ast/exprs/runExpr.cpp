#include "runExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../builtin/primitive/nVoid.hpp"
#include "getExpr.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(runExpr), DEF_VISIT())

    me::runExpr(const node& meObj, const node& subject, const args& a):
            _me(meObj), _args(a), _subject(subject)  {}
    me::runExpr(const node& meObj, const args& a): _me(meObj), _args(a), _subject(meObj) {}

    str me::run(const args& a) {
        str sub = _getSub(getMe().as<node>(), _args);
        if(!sub) return NAMU_E("_subject.as<node>() returns null"), str();

        str ret = sub->run(_args);
        _args.setMe(nulOf<baseObj>());
        return ret;
    }

    node& me::getMe() {
        if(!_me)
            return thread::get()._getNowFrame();
        return *_me;
    }

    const node& me::getSubject() const { return *_subject; }
    node& me::getSubject() { return *_subject; }

    args& me::getArgs() { return _args; }
    const args& me::getArgs() const { return _args; }

    void me::setMe(const node& newMe) {
        _me.bind(newMe);
    }

    str me::_getSub(str me, const args& a) const {
        if(!me) return NAMU_E("me Obj == null"), str();
        if(!_subject) return NAMU_E("_subject as node == null"), str();

        if(!nul(a))
            a.setMe(*me);
        getExpr& cast = _subject->cast<getExpr>();
        if(!nul(cast))
            cast.setMe(*me);

        return _subject->as<node>();
    }

    str me::getEval() const {
        str sub = _getSub(getMe().getEval(), nulOf<args>());
        if(!sub) return NAMU_E("_subject.as<node>() returns null"), str();

        const func& f = sub.cast<func>();
        str ret = nul(f) ? sub->getEval() : f.getRet()->getEval();
        // clone returning value when eval this:
        //  think about following code:
        //      def a
        //          ...
        //      b := a()
        // because getEval() funcs returns the origin object always,
        // if I don't clone anything here, it'll return origin object of 'a'.
        // then when verify defAssignExpr it'll be judged to compile error.
        return str((node*) ret->clone());
    }
}
