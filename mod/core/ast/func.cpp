#include "func.hpp"

#include "../builtin/container/native/tnchain.inl"
#include "../frame/frameInteract.hpp"
#include "../frame/thread.hpp"
#include "../worker/visitor/visitor.hpp"
#include "closure.hpp"
#include "obj.hpp"
#include "params.hpp"
#include "../builtin/err/nerr.hpp"

namespace nm {

    NM(DEF_ME(func), DEF_VISIT())

    me::func(const modifier& mod, const funcMgdType& type):
        super(mod), _type(type), _blk(new blockExpr()) {}

    me::func(const modifier& mod, const funcMgdType& type, const blockExpr& newBlock):
        super(mod), _type(type), _blk(newBlock) {}

    me::func(const modifier& mod, const funcMgdType& type, const scope& subs,
        const blockExpr& newBlock):
        super(mod), _type(type), _subs(subs), _blk(newBlock) {}

    const ntype& me::getType() const { return _type; }

    blockExpr& me::getBlock() { return *_blk; }

    const blockExpr& me::getBlock() const { return *_blk; }

    void me::setBlock(const blockExpr& new1) { _blk.bind(new1); }

    scope& me::subs() { return _subs; }

    str me::run(const args& a) {
        NM_I("@%s prepare to run `%s(%s)`...", this, getSrc(), getParams());
        if(nul(a)) return NM_E("a == null"), str();
        if(!thread::get().isInteractable())
            return NM_E("thread isn't interactable"),
                   nerr::newErr(errCode::THERE_IS_NO_FRAMES_IN_THREAD);

        // s is from heap space. but freed by _outFrame() of this class.
        scope& s = *_evalArgs(a) orRet str();
        node &meObj = a.getMe() orRet NM_E("meObj == null"), str();
        return _interactFrame(meObj, s, thread::get().getEx().len() - 1);
    }

    str me::_interactFrame(node& meObj, scope& s, nidx exN) {
        frameInteract f1(meObj);
        frameInteract f2(*this, s);
        frameInteract f3(*_blk);
        return _run(exN);
    }

    str me::_run(nidx exN) {
        _runEnds();
        NM_I("@%s --> run `%s(%s)", this, getSrc(), getParams());
        str ret = _blk->run();
        NM_I("@%s <-- ended `%s(%s)", this, getSrc(), getParams());
        ret = _postprocess(ret, exN);
        NM_I("@%s `%s <--ret-- %s(%s)`", this, ret, getSrc(), getParams());
        return ret;
    }

    str me::_postprocess(const str& blkRes, nidx exN) {
        frame& fr = thread::get()._getNowFrame();
        str frRes = fr.getRet();
        str res = frRes ? frRes : blkRes;
        fr.setRet();

        if(nul(res)) return NM_E("res == null"), str();
        const errReport& errs = thread::get().getEx();
        if(errs.inErr(exN)) return *errs.last(); // if new exception, I just return it.

        auto* closure = closure::make(*res);
        if(closure) res.bind(closure);
        return res ? res->as(*getRet().as<node>()) : res;
    }

    void me::_runEnds() {
        for(nidx n = _ends.len() - 1; n >= 0; n--)
            _ends[n].run();
    }

    void me::_setOrigin(const baseObj& org) { _org.bind(org); }

    scope* me::_evalArgs(const ucontainable& args) {
        scope* ret = new scope();
        evalArgs(args, getParams(),
            [&](const std::string& name, const node& arg) { ret->add(name, arg); });
        return ret;
    }

    void me::inFrame(const bicontainable& args) const {
        frame& fr = thread::get()._getNowFrame() orRet NM_E("fr == null");

        NM_DI("'%s'._inFrame() frames.len[%d]", *this, thread::get().getFrames().len());
        fr.addFunc(*this);
        fr.add(*this);
        fr.add(*scope::wrap<scope>(
            nul(args) ? nulOf<nbicontainer>() : (nbicontainer&) args)); // including 'me'
    }

    void me::outFrame(const bicontainable& args) const {
        NM_DI("'%s func'._outFrame() frames.len[%d]", getSrc(), thread::get().getFrames().len());

        frame& fr = thread::get()._getNowFrame();
        baseFunc& f = fr.getFunc();
        if(nul(f) || &f != this) return;

        fr.delFunc();
        fr.del();
        if(!nul(args)) fr.del();
    }

    const baseObj& me::getOrigin() const { return *_org; }

    ends& me::getEnds() { return _ends; }

    void me::onCloneDeep(const clonable& from) {
        const me& rhs = (const me&) from;
        _type.onCloneDeep(rhs._type);
        _subs.onCloneDeep(rhs._subs);
        _blk.bind((blockExpr*) rhs._blk->cloneDeep());
    }

    void me::evalArgs(const ucontainable& args, const params& ps, const onEval& lambda) {
        if(args.len() != ps.len())
            return NM_E("length of args(%d) and typs(%d) doesn't match.", args.len(), ps.len());
        int n = 0;
        for(const node& e: args) {
            const param& p = ps[n++];
            str evaluated = closure::make(e) orDo evaluated = e.asImpli(*p.getOrigin().as<node>());
            if(!evaluated)
                return NM_E("evaluation of arg[%s] -> param[%s] has been failed.", e,
                    p.getOrigin());
            lambda(p.getName(), *evaluated);
        }
    }

    nbool me::isAbstract() const { return _blk ? _blk->isAbstract() : true; }
} // namespace nm
