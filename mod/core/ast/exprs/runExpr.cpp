#include "runExpr.hpp"

#include "../../builtin/primitive/nVoid.hpp"
#include "../../frame/thread.hpp"
#include "../../worker/visitor/visitor.hpp"
#include "../tmock.hpp"
#include "../closure.hpp"
#include "getExpr.hpp"

namespace nm {

    NM(DEF_ME(runExpr), DEF_VISIT())

    me::runExpr(const node& meObj, const node& subject, const args& a):
        _me(meObj), _args(a), _subject(subject) {}

    me::runExpr(const node& meObj, const args& a): _me(meObj), _args(a), _subject(meObj) {}

    str me::run(const args& a) {
        auto addr = platformAPI::toAddrId(this);
        str evaledMe =
            getMe() TO(template as<node>()) orRet NM_E("@%s `me` is null. no thread found", addr),
            str();

        str sub =
            _getSub(*evaledMe, _args) orRet NM_E("@%s can't find the func to `%s`", addr, evaledMe),
            str();

        NM_DI("@%s run: assigning me: me[%s] sub[%s@%s]", addr, evaledMe, sub, &sub.get());
        nbool needMe = !sub->isSub<baseObj>() && !sub->isSub<closure>();
        if(needMe && !nul(_args)) { // if sub is a baseObj, this expr will runs ctor
                                    // of it which doesn't need me obj.
            frame& fr = evaledMe->cast<frame>();
            _args.setMe(!nul(fr) ? fr.getMeHaving(*sub) : *evaledMe);
            NM_DI("@%s run: setting me on args. args.me[%s]", addr, _args TO(getMe()));
        }

        NM_I("@%s it'll call `%s.%s@%s(%s)", addr, evaledMe, sub->getSrc(), &sub.get(),
            _args.toStr());
        str ret = sub->run(_args);

        NM_DI("@%s `%s.%s@%s(%s) --returned--> %s`", addr, evaledMe, sub->getSrc(), &sub.get(),
            _args.toStr(), ret);
        _args.setMe(nulOf<baseObj>());
        return ret;
    }

    node& me::getMe() {
        WHEN(!_me).ret(thread::get()._getNowFrame());
        return *_me;
    }

    const node& me::getSubj() const { return *_subject; }

    node& me::getSubj() { return *_subject; }

    void me::setSubj(const node& new1) { _subject.bind(new1); }

    args& me::getArgs() { return _args; }

    const args& me::getArgs() const { return _args; }

    void me::onCloneDeep(const clonable& from) {
        const me& rhs = (const me&) from;

        if(rhs._me) _me.bind((node*) rhs._me->cloneDeep());
        _args.onCloneDeep(rhs._args);
        if(rhs._subject) _subject.bind((node*) rhs._subject->cloneDeep());
    }

    void me::setMe(const node& newMe) { _me.bind(newMe); }

    str me::_getSub(str me, const args& a) const {
        WHEN(!me).err("me Obj == null").ret(str());
        WHEN(!_subject).err("_subject as node == null").ret(str());

        getExpr& cast = _subject->cast<getExpr>();
        if(!nul(cast)) cast.setMe(*me);

        return _subject->as<node>();
    }

    str me::getEval() const {
        const node& me = getMe() orRet str();
        str sub =
            _getSub(me.getEval(), nulOf<args>()) orRet NM_E("_subject.as<node>() returns null"),
            str();
        WHEN(sub->isSub<baseObj>()).ret(sub->isComplete() ? sub : new mockNode(*sub));

        baseFunc &cast = sub->cast<baseFunc>() orRet NM_E("sub isn't obj or func. returns null"),
                 str();
        return new mockNode(cast.getRet());
    }
} // namespace nm
