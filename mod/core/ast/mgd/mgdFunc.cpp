#include "mgdFunc.hpp"
#include "../obj.hpp"
#include "../../builtin/container/native/tnchain.inl"
#include "../../frame/thread.hpp"
#include "../params.hpp"
#include "../../frame/frameInteract.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(mgdFunc), DEF_VISIT())

    me::mgdFunc(const params& ps, const node& retType):
            super(), _params(ps), _retType(retType), _blk(new blockExpr()) {}
    me::mgdFunc(const params& ps, const node* retType):
            super(), _params(ps), _retType(retType), _blk(new blockExpr()) {}
    me::mgdFunc(const params& ps, const node& retType, const blockExpr& newBlock):
            super(), _params(ps), _retType(retType), _blk(newBlock) {}
    me::mgdFunc(const params& ps, const node* retType, const blockExpr& newBlock):
            super(), _params(ps), _retType(retType), _blk(newBlock) {}

    blockExpr& me::getBlock() { return *_blk; }
    const blockExpr& me::getBlock() const { return *_blk; }
    const node& me::getRet() const { return *_retType; }

    nbool me::setRet(const node& newRet) { return _retType.bind(newRet); }

    nbicontainer& me::subs() { return _shares; }
    const params& me::getParams() const { return _params; }

    str me::run(const args& a) {
        if(nul(a)) return NAMU_E("a == null"), str();

        // s is from heap space. but freed by _outFrame() of this class.
        scope& s = *_evalArgs(a);
        if(nul(s)) return str();
        baseObj& meObj = a.getMe();
        if(nul(meObj)) return NAMU_E("meObj == null"), str();

        str ret;
        frameInteract f1(meObj); {
            frameInteract f2(*this, s); {
                frameInteract f3(*_blk); {
                    _blk->run();
                    return _postProcess();
                }
            }
        }
    }

    str me::_postProcess() {
        frame& fr = thread::get()._getNowFrame();
        node& retVal = fr.getRet();

        str ret;
        if(!nul(retVal))
            ret = retVal.as(getRet());

        fr.relRet();
        return ret;
    }

    scope* me::_evalArgs(const ucontainable& args) {
        const params& ps = getParams();
        if(args.len() != ps.len())
            return NAMU_E("length of args(%d) and typs(%d) doesn't match.", args.len(), ps.len()), nullptr;

        scope* ret = new scope();
        int n = 0;
        for(const node& e: args) {
            const param& p = ps[n++];
            str evaluated = e.as(*p.getOrigin().as<node>());
            if(!evaluated)
                return NAMU_E("evaluation of arg[%s] -> param[%s] has been failed.", e.getType().getName().c_str(),
                        p.getOrigin().getType().getName().c_str()), ret;

            ret->add(p.getName(), *evaluated);
        }
        return ret;
    }

    void me::inFrame(const bicontainable& args) {
        frame& fr = thread::get()._getNowFrame();
        if(nul(fr)) {
            NAMU_E("fr == null");
            return;
        }

        NAMU_DI("%s._onInFrame()", getType().getName().c_str());
        fr.pushLocal(subs());
        fr.setFunc(*this);
        fr.pushLocal((nbicontainer&) args); // including 'me'
    }

    void me::outFrame() {
        NAMU_DI("%s._onOutFrame()", getType().getName().c_str());

        frame& fr = thread::get()._getNowFrame();
        // TODO: is it safe to delete below lines?
        fr.setFunc(nulOf<func>());
        fr.popLocal();
        fr.popLocal();
    }
}
