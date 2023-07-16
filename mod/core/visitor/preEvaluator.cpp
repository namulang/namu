#include "preEvaluator.hpp"
#include "../ast/node.inl"
#include "../ast/obj.hpp"
#include "../ast/mgd/mgdFunc.hpp"
#include "../frame/frameInteract.hpp"
#include "verifier.hpp"
#include "../ast/exprs/getGenericExpr.hpp"

namespace namu {

    NAMU(DEF_ME(preEvaluator))

    me::preEvaluator() {
        rel();
    }

    void me::rel() {
        _rel();

        super::rel();
    }

    void me::start() {
        super::start();

        _preEval();
    }

    void me::onVisit(visitInfo i, obj& me) {
        NAMU_DI("preEval: obj: %s", i.name.c_str());

        _obj.bind(me);
        me.inFrame();
    }

    void me::onLeave(visitInfo i, obj& me) {
        me.outFrame();
        _obj.rel();
    }

    void me::onVisit(visitInfo i, mgdFunc& me) {
        _func.bind(me);
        me.inFrame();

        NAMU_DI("preEval: mgdFunc: %s", i.name.c_str());
        for(const auto& p : me.getParams())
            ((node&) p.getOrigin()).accept(i, *this);

        if(i.name == baseObj::PRECTOR_NAME) {
            NAMU_DI("preEval: mgdFunc: found prector");
            _stack.push_back({*_obj, me, false});
        }

        me.getBlock().inFrame();
    }

    void me::onLeave(visitInfo i, mgdFunc& me) {
        me.getBlock().outFrame();
        me.outFrame();
        _func.rel();
    }

    void me::onVisit(visitInfo i, getGenericExpr& me) {
        NAMU_DI("preEval: getGenericExpr:");

        // this lets genericObj make a their generic obj.
        obj& genericObj = me.getEval().cast<obj>();
        if(nul(genericObj)) return;

        obj& prevObj = *_obj;
        mgdFunc& prevFunc = *_func;
        genericObj.accept(i, *this);
        _func.bind(prevFunc);
        _obj.bind(prevObj);
    }

    void me::_rel() {
        _stack.clear();
    }

    void me::_preEval() {
        NAMU_DI(" ===================================");
        NAMU_DI("          preEvaluationLoop         ");
        NAMU_DI(" ===================================");
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
        NAMU_DI(" ==== end of preEvaluationLoop ==== ");
    }

    void me::_delPreCtors() {
        for(auto& eval : _stack)
            eval.me->subs().del(baseObj::PRECTOR_NAME);
        _stack.clear();
    }

    void me::_preEvalStack(errReport& rpt) {
        NAMU_DI("preEval: evalStack[%d]", _stack.size());
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
            mgdFunc& fun = *eval.fun;
            frameInteract f2(fun); {
                blockExpr& blk = fun.getBlock();
                frameInteract f3(blk); {
                    narr& stmts = blk.getStmts();

                    NAMU_DI("preEval: evalFunc(%x).len = %d", &fun, stmts.len());

                    for(int n=0; n < stmts.len() ;) {
                        ncnt prevErrCnt = rpt.len();
                        verifier v;
                        v.setReport(rpt)
                         .setRoot(stmts[n])
                         .setLog(false)
                         .start();

                        if(rpt.len() > prevErrCnt) {
                            // if there was an error, proceed next stmt.
                            // TODO: it uses len() for counting errors.
                            //       but one of them could be just warning.
                            NAMU_DI("preEval: evalFunc(%x): eval failed on stmt[%d]", &fun, n);
                            n++;
                        } else
                            stmts.del(n);
                    } // end of inner for

                    NAMU_DI("preEval: end of evalFunc(%x).len = %d", &fun, stmts.len());

                    return stmts.len() == 0;
                }
            }
        }
    }
}
