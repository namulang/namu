#include "func.hpp"
#include "obj.hpp"
#include "../builtin/container/native/tnchain.inl"
#include "../frame/thread.hpp"
#include "params.hpp"
#include "../frame/frameInteract.hpp"
#include "../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(func), DEF_VISIT())

    me::func(const params& ps, const node& retType):
            super(), _params(ps), _retType(retType), _blk(new blockExpr()) {}
    me::func(const params& ps, const node* retType):
            super(), _params(ps), _retType(retType), _blk(new blockExpr()) {}
    me::func(const params& ps, const node& retType, const blockExpr& newBlock):
            super(), _params(ps), _retType(retType), _blk(newBlock) {}
    me::func(const params& ps, const node* retType, const blockExpr& newBlock):
            super(), _params(ps), _retType(retType), _blk(newBlock) {}

    blockExpr& me::getBlock() { return *_blk; }
    const blockExpr& me::getBlock() const { return *_blk; }
    void me::setBlock(const blockExpr& new1) {
        _blk.bind(new1);
    }
    str me::getRet() const { return _retType; }

    nbool me::setRet(const node& newRet) { return _retType.bind(newRet); }

    nbicontainer& me::subs() { return _shares; }
    const params& me::getParams() const { return _params; }

    str me::run(const args& a) {
        if(nul(a)) return NAMU_E("a == null"), str();

        // s is from heap space. but freed by _outFrame() of this class.
        scope& s = *_evalArgs(a);
        if(nul(s)) return str();
        node& meObj = a.getMe();
        if(nul(meObj)) return NAMU_E("meObj == null"), str();

        str ret;
        frameInteract f1(meObj); {
            frameInteract f2(*this, s); {
                frameInteract f3(*_blk); {
                    return _postprocess(_blk->run());
                }
            }
        }
    }

    const point& me::getPos() const {
        return _pos;
    }

    str me::_postprocess(str ret) {
        frame& fr = thread::get()._getNowFrame();
        node* retVal = &fr.getRet();
        if(nul(retVal)) retVal = &ret.get();
        if(nul(retVal)) return NAMU_E("retVal == null"), str();

        ret = retVal->as(*getRet()->as<node>());
        fr.setRet();
        return ret;
    }

    scope* me::_evalArgs(const ucontainable& args) {
        const params& ps = getParams();
        if(args.len() != ps.len())
            return NAMU_E("length of args(%d) and typs(%d) doesn't match.", args.len(), ps.len()), nullptr;

        scope* ret = new scope(*this);
        int n = 0;
        for(const node& e: args) {
            const param& p = ps[n++];
            str evaluated = e.asImpli(*p.getOrigin().as<node>());
            if(!evaluated)
                return NAMU_E("evaluation of arg[%s] -> param[%s] has been failed.", e.getType().getName().c_str(),
                        p.getOrigin().getType().getName().c_str()), ret;

            ret->add(p.getName(), *evaluated);
        }
        return ret;
    }

    void me::_setPos(const point& new1) {
        _pos = new1;
    }

    void me::inFrame(const bicontainable& args) {
        frame& fr = thread::get()._getNowFrame();
        if(nul(fr)) {
            NAMU_E("fr == null");
            return;
        }

        NAMU_DI("%s._inFrame()", getType().getName().c_str());
        fr.pushLocal(subs());
        fr.setFunc(*this);
        fr.pushLocal(nul(args) ? nulOf<nbicontainer>() : (nbicontainer&) args); // including 'me'
    }

    void me::outFrame() {
        NAMU_DI("%s._outFrame()", getType().getName().c_str());

        frame& fr = thread::get()._getNowFrame();
        baseFunc& f = fr.getFunc();
        if(nul(f) || &f != this) return;

        fr.setFunc();
        fr.popLocal();
        fr.popLocal();
    }

    clonable* me::deepClone() const {
        me* ret = (me*) clone();
        // params:
        ret->_params.rel();
        for(auto e=_params.begin(); e ;++e)
            ret->_params.add((param*) e->deepClone());
        // shares:
        ret->_shares.rel();
        for(auto e=_shares.begin(); e ;++e)
            ret->_shares.add(e.getKey(), (node*) e->deepClone());
        // retType:
        ret->_retType.bind((node*) _retType->deepClone());
        // blk:
        ret->_blk.bind((blockExpr*) _blk->deepClone());

        return ret;
    }
}
