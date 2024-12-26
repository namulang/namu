#include "closure.hpp"
#include "../frame/thread.hpp"
#include "../frame/frameInteract.hpp"
#include "../worker/visitor/visitor.hpp"
#include "exprs/getExpr.hpp"
#include "exprs/defNestedFuncExpr.hpp"
#include "baseFunc.hpp"

namespace nm {
    NM(DEF_ME(closure), DEF_VISIT())

    const ases& me::closureType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            struct asFunc : public tas<baseFunc> {
                str as(const node& me, const type& to) const override {
                    const closure& cast = me.cast<closure>() orRet str();
                    return cast.getFunc();
                }
            };
            inner.add(new asFunc());
        }
        return inner;
    }

    me::closure(const baseObj& org, const baseFunc& func): _org(org), _func(func) {}

    scope& me::subs() { return _func->subs(); }

    priorType me::prioritize(const args& a) const { return _func->prioritize(a); }

    const modifier& me::getModifier() const { return _func->getModifier(); }

    str me::run(const args& a) {
        NM_I("running closure for %s.%s", *_org, *_func);
        if(!_func) return str();

        args evaled;
        func::evalArgs(a, _func->getParams(),
            [&](const std::string& name, const node& arg) { evaled.add(arg); });
        evaled.setMe(*_org);
        return _func->run(evaled);
    }

    const baseObj& me::getOrigin() const { return *_org; }

    const baseFunc& me::getFunc() const { return *_func; }

    params& me::getParams() { return _func THEN(getParams()); }

    const src& me::getSrc() const { return _func ? _func->getSrc() : dumSrc::singletone(); }

    me* me::make(const node& e) {
        if(e.isSub<func>()) return _make((func&) e);
        if(e.isSub<getExpr>()) return _make((getExpr&) e);
        if(e.isSub<defNestedFuncExpr>()) return _make((defNestedFuncExpr&) e);
        return nullptr;
    }

    me* me::_make(const func& e) {
        const baseObj& meObj =
            thread::get().getNowFrame() THEN(getMe()) THEN(template cast<baseObj>()) orRet nullptr;

        NM_I("make a closure for %s.%s", meObj, e);
        return new me(meObj, e);
    }

    me* me::_make(const getExpr& e) {
        if(nul(e)) return nullptr;

        str mayMe = e._evalMe(true);
        frame& fr = mayMe->cast<frame>();
        tstr<baseObj> meObj =
            (!nul(fr) ? fr.getMe().cast<baseObj>() : mayMe->cast<baseObj>()) orRet nullptr;
        baseFunc& cast = e._onGet(*mayMe) THEN(template cast<baseFunc>()) orRet nullptr;

        NM_I("make a closure for %s.%s", meObj, cast.getSrc().getName());
        return new me(*meObj, cast);
    }

    me* me::_make(defNestedFuncExpr& e) {
        if(nul(e)) return nullptr;

        return _make(e.run()->cast<func>());
    }
} // namespace nm
