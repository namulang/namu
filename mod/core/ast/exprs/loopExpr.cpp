#include "loopExpr.hpp"

#include "../../builtin/container/mgd/arr.hpp"
#include "../../builtin/container/mgd/tdumArr.hpp"
#include "../../frame/frameInteract.hpp"
#include "../../frame/thread.hpp"
#include "../../worker/visitor/visitor.hpp"
#include "breakExpr.hpp"
#include "nextExpr.hpp"
#include "retExpr.hpp"

namespace nm {

    NM(DEF_ME(loopExpr), DEF_VISIT())

    me::loop::loop(arr& ret): _ret(ret) {}

    arr& me::loop::getRet() { return *_ret; }

    void me::loop::run(blockExpr& blk, frame& fr) {
        str res = blk.run();
        if(_ret) _ret->add(*res);
    }

    nbool me::loop::postprocess(frame& fr) {
        const node& ret = fr.getRet();
        if(nul(ret)) return true;

        if(ret.isSub<nextRet>()) return fr.setRet(), true;
        if(ret.isSub<breakRet>())
            return fr.setRet(), false; // after I go out of the loop, I should clear break state.
        // or stop the loop. I found the return value of the func.
        return false;
    }

    me::loopExpr(const blockExpr& blk): _blk(blk) {}

    blockExpr& me::getBlock() const { return *_blk; }

    str me::getEval() const {
        if(_eval) return *_eval;

        return _eval = _makeEval();
    }

    str me::_makeEval() const {
        str res = getBlock().getEval();
        if(!res) return str();

        if(res->isSub<retExpr>()) return res;
        return new arr(*res);
    }

    str me::run(const args& a) {
        auto addr = platformAPI::toAddrId(this);
        blockExpr& blk = getBlock();
        if(nul(blk)) return NM_E("%s blk is null", addr), str();

        auto l = _makeLoop(*_makeRet());
        if(!l) return NM_E("%s loop is null", addr), str();

        frame& fr = thread::get()._getNowFrame();
        while(l->isLooping()) {
            frameInteract f1(getBlock());
            {
                l->run(blk, fr);
                if(!l->postprocess(fr)) break;
            }
        }
        return l->getRet();
    }

    tstr<arr> me::_makeRet() const {
        static dumArr inner;
        node& eval = *getEval();
        if(nul(eval)) return NM_E("eval is null "), nulOf<arr>();
        if(!eval.isSub<arr>()) return nulOf<arr>();

        return *new arr(eval.getType().getBeans()[0]);
    }
} // namespace nm
