#include "core/ast/exprs/loopExpr.hpp"

#include "core/builtin/container/mgd/arr.hpp"
#include "core/builtin/container/mgd/tdumArr.hpp"
#include "core/frame/frameInteract.hpp"
#include "core/frame/thread.hpp"
#include "core/worker/visitor/visitor.hpp"
#include "core/ast/exprs/breakExpr.hpp"
#include "core/ast/exprs/nextExpr.hpp"
#include "core/ast/exprs/retExpr.hpp"

namespace nm {

    NM(DEF_ME(loopExpr), DEF_VISIT())

    me::loop::loop(arr& ret): _ret(ret) {}

    arr& me::loop::getRet() { return *_ret; }

    void me::loop::run(blockExpr& blk, frame& fr) {
        str res = blk.run();
        if(_ret) _ret->add(*res);
    }

    nbool me::loop::postprocess(frame& fr) {
        const node& ret = fr.getRet() OR.ret(true);
        if(ret.isSub<nextRet>()) return fr.setRet(), true;
        if(ret.isSub<breakRet>())
            return fr.setRet(), false; // after I go out of the loop, I should clear break state.
        // or stop the loop. I found the return value of the func.
        return false;
    }

    me::loopExpr(const blockExpr& blk): _blk(blk) {}

    blockExpr& me::getBlock() const { return *_blk; }

    str me::getEval() const {
        WHEN(_eval).ret(*_eval);

        return _eval = _makeEval();
    }

    str me::_makeEval() const {
        str res = getBlock().getEval() OR.ret(str());

        if(res->isSub<retExpr>()) return res;
        return new arr(*res->as<baseObj>());
    }

    str me::run(const args& a) {
        auto addr = platformAPI::toAddrId(this);
        blockExpr& blk = getBlock() OR.err("%s blk is null", addr).ret(str());
        tstr<loop> l = _makeLoop(*_makeRet()) OR.err("%s loop is null", addr).ret(str());

        frame& fr = thread::get()._getNowFrame();
        while(l->isLooping()) {
            frameInteract f1(getBlock());
            l->run(blk, fr);
            if(!l->postprocess(fr)) break;
        }
        return l->getRet();
    }

    tstr<arr> me::_makeRet() const {
        static dumArr inner;
        node& eval = *getEval() OR.err("eval is null ").retNul<arr>();
        WHEN(!eval.isSub<arr>()).retNul<arr>();

        return *new arr(*eval.getType().getParams()[0].getOrigin().as<baseObj>());
    }
} // namespace nm
