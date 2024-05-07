#include "preEvaluator.hpp"
#include "../ast/node.inl"
#include "../ast/obj.hpp"
#include "../ast/func.hpp"
#include "../frame/frameInteract.hpp"
#include "verifier.hpp"
#include "../ast/exprs/getGenericExpr.hpp"
#include "../frame/thread.hpp"
#include "../loader/worker/worker.inl"

namespace namu {

    NAMU(DEF_ME(preEvaluator))

#define GUARD(...) if(isFlag(GUARD)) NAMU_I(__VA_ARGS__)


    me::preEvaluator() {
        rel();
    }

    void me::rel() {
        _rel();

        super::rel();
    }

    void me::_onWork() {
        if(nul(thread::get())) {
            error(errCode::NO_THREAD);
            return;
        }
        super::_onWork();
        _preEval();
    }

    nbool me::onVisit(visitInfo i, obj& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_DI("preEval: obj: %s", i.name.c_str());

        _obj.bind(me);
        me.inFrame();
        return true;
    }

    void me::onLeave(visitInfo i, obj& me) {
        GUARD("%s.onLeave(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        me.outFrame();
        _obj.rel();
    }

    nbool me::onVisit(visitInfo i, func& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        _func.bind(me);
        me.inFrame();

        NAMU_I("preEval: func: %s", i.name.c_str());
        for(const auto& p : me.getParams())
            ((node&) p.getOrigin()).accept(i, *this);

        if(i.name == baseObj::PRECTOR_NAME) {
            NAMU_I("preEval: func: found prector");
            _stack.push_back({*_obj, me, false});
        }

        me.getBlock().inFrame();
        return true;
    }

    void me::onLeave(visitInfo i, func& me) {
        GUARD("%s.onLeave(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        me.getBlock().outFrame();
        me.outFrame();
        _func.rel();
    }

    nbool me::onVisit(visitInfo i, getGenericExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        // this lets genericObj make a their generic obj.
        obj& genericObj = me.getEval().cast<obj>();
        if(nul(genericObj)) return true;

        obj& prevObj = *_obj;
        func& prevFunc = *_func;
        genericObj.accept(i, *this);
        _func.bind(prevFunc);
        _obj.bind(prevObj);
        return true;
    }

    void me::_rel() {
        _stack.clear();
    }

    void me::_preEval() {
        NAMU_I(" ===================================");
        NAMU_I("          preEvaluationLoop         ");
        NAMU_I(" ===================================");
        errReport rpt;
        while(true) {
            errReport e;
            _preEvalStack(e);
            if(rpt == e)
                break;
            rpt = e;
        }

        _delPreCtors();
        getReport().add(rpt);
        NAMU_I(" ==== end of preEvaluationLoop ==== ");
    }

    void me::_delPreCtors() {
        for(auto& eval : _stack)
            eval.me->subs().del(baseObj::PRECTOR_NAME);
        _stack.clear();
    }

    void me::_preEvalStack(errReport& rpt) {
        NAMU_I("preEval: evalStack[%d]", _stack.size());
        for(nint n = 0; n < _stack.size() ;n++) {
            evaluation& eval = _stack[n];
            if(eval.evaluated) continue;

            if(_preEvalFunc(rpt, eval))
                eval.evaluated = true;
        }
    }

    nbool me::_preEvalFunc(errReport& rpt, evaluation& eval) {
        obj& me = *eval.me;
        frameInteract f1(me); {
            func& fun = *eval.fun;
            frameInteract f2(fun); {
                blockExpr& blk = fun.getBlock();
                frameInteract f3(blk); {
                    narr& stmts = blk.getStmts();

                    NAMU_I("preEval: evalFunc(%x).len = %d", &fun, stmts.len());

                    for(int n=0; n < stmts.len() ;) {
                        ncnt prevErrCnt = rpt.len();
                        verifier v;
                        v.setReport(rpt)
                         .setTask(stmts[n])
                         .setFlag(LOG_ON_EX | DUMP_ON_EX)
                         .work();

                        if(rpt.len() > prevErrCnt) {
                            // if there was an error, proceed next stmt.
                            // TODO: it uses len() for counting errors.
                            //       but one of them could be just warning.
                            NAMU_I("preEval: evalFunc(%x): eval failed on stmt[%d]", &fun, n);
                            n++;
                        } else
                            stmts.del(n);
                    } // end of inner for

                    NAMU_I("preEval: end of evalFunc(%x).len = %d", &fun, stmts.len());

                    return stmts.len() == 0;
                }
            }
        }
    }
}
