#include "verifier.inl"
#include "../frame/frame.hpp"
#include "../frame/thread.hpp"
#include "../loader/errReport.hpp"
#include "../builtin/primitive.hpp"
#include"../ast.hpp"

namespace namu {

    NAMU_DEF_ME(verifier)

    namespace {
        str primitives[] = {
            new nInt(),
            new nFlt(),
            new nStr(),
            new nChar(),
            new nBool(),
        };

        nbool checkEvalType(const node& eval) {
            if(nul(eval)) return false;
            for(str e : primitives)
                if(eval.isSub(*e))
                    return true;

            return false;
        }
        void _prepareArgsAlongParam(const params& ps, scope& s) {
            for(const auto& p : ps)
                s.add(p.getName(), *p.getOrigin().as<node>());
        }
    }

    me* me::_now = nullptr;

    void me::rel() {
        setReport(dummyErrReport::singletone);
        _frame.rel();
    }

    me::verifier() { rel(); }

    me& me::setReport(errReport& rpt) {
        _rpt.bind(rpt);
        return *this;
    }

    void me::_leaveErrFrame() {
        _frame.bind(thread::get().getNowFrame());
    }

    errReport& me::getReport() { return *_rpt; }
    frame& me::getErrFrame() { return *_frame; }


    // verification:
    void me::onVisit(visitInfo i, node& me) {
        NAMU_DI("verify: node: no same variable=%d", me.subs().len());
        if(me.isSub<frame>()) return;

        for(auto e=me.subs().begin(); e ;++e) {
            if(me.subAll<baseObj>(e.getKey()).len() > 1)
                return _err(e->getPos(), errCode::DUP_VAR, e.getKey().c_str());
        }
    }

    void me::onVisit(visitInfo i, asExpr& me) {
        NAMU_DI("verify: asExpr: _me & _as aren't null");
        if(nul(me.getMe())) return _srcErr(me.getPos(), errCode::LHS_IS_NULL);
        if(nul(me.getAs())) return _srcErr(me.getPos(), errCode::RHS_IS_NULL);

        NAMU_DI("verify: asExpr: checks that me can cast to 'as'");
        if(!me.getMe().is(me.getAs()))
            return _srcErr(me.getPos(), errCode::CAST_NOT_AVAILABLE, me.getMe().getType().getName().c_str(),
                    me.getAs().getType().getName().c_str());

        NAMU_DI("verify: asExpr: rhs shouldn't be expression");
        if(me.getAs().isSub<expr>())
            return _srcErr(me.getPos(), errCode::EXPR_SHOULDNT_BE_HERE);
    }

    void me::onVisit(visitInfo i, assignExpr& me) {
        NAMU_DI("verify: assignExpr: set iter");
        if(!me._getScopeIterOfLhs())
            _srcErr(me.getPos(), errCode::NOT_EXIST, me.getType().getName().c_str());

        NAMU_DI("verify: assignExpr: set evalType");
        const node& leftEval = me.getLeft().getEval();
        if(nul(leftEval)) return _srcErr(me.getPos(), errCode::LHS_IS_NULL);
        const ntype& ltype = me.getLeft().getEval().getType();
        if(nul(ltype)) return _srcErr(me.getPos(), errCode::LHS_IS_NULL);
        const node& rightEval = me.getRight().getEval();
        if(nul(rightEval)) return _srcErr(me.getPos(), errCode::RHS_IS_NULL);
        const ntype& rtype = me.getRight().getEval().getType();
        if(nul(rtype)) return _srcErr(me.getPos(), errCode::RHS_IS_NULL);
        if(!ltype.isImpli(rtype))
            return _srcErr(me.getPos(), errCode::TYPE_NOT_COMPATIBLE, ltype.getName().c_str(), rtype.getName()
                    .c_str());

        // verify rvalue and lvalue:
        //  first of all:
        //      in namulang there is no lvalue concept. to involve lvalue concept,
        //      I need to bring new concept or feature like 'const' but I don't want to.
        //      becuase the direction of this language is a toy lang. DON'T be serious.
        //      but I can't leave something which is going to operate like a lvalue by user.
        //      so I'll emulate the way how lvalue works.
        //
        //  when you assign something:
        //      into left identifier (= lhs), left one should be lvalue. and there are 3 case
        //      of lvalue you can find:
        //
        //      1. getExpr:
        //          assigning identifier registered into some scope is always valid
        //          operation.
        //          e.g. A.B = 5
        //
        //      2. RunExpr:
        //          running some method of object could come in chain of assignment exprs.
        //              e.g. A.B().C = 5
        //          however it shouldn't be the last expression to process.
        //              e.g. A.B() = 5 // invalid
        //
        //      3. ElementExpr:
        //          getting element by index also valid expression of assignment expr.
        //              e.g. A.B[C] = 5
        //          when verifier meets ElementExpr, it doesn't need to deep search any longer to
        //          verify invalidness of lvalue.
        //
        //      it looks complicated to verify this at glance but it's not.
        //      the reason is, structure of expression has been inside out:
        //          e.g. A.B.NAME = 5
        //
        //      the structure of above sample will be,
        //          AssignExpr(getExpr(getExpr(A, B), NAME), nInt(5))
        //      so, only I need to check is, lhs of AssignExpr is kind of getExpr() or not.
        //      I can care about that the last expression is valid.
        NAMU_DI("verify: assignExpr: checks rvalue");
        const node& lhs = me.getLeft();
        if(!lhs.isSub<getExpr>()/* TODO: && !lhs.isSub<ElementExpr>()*/)
            return _srcErr(me.getPos(), errCode::ASSIGN_TO_RVALUE, me.getRight().getType().getName().c_str(),
                    lhs.getType().getName().c_str());
    }

    void me::onVisit(visitInfo i, blockExpr& me) {
        NAMU_DI("verify: blockExpr: it will iterate all subnodes[%d]", me.getStmts().len());
    }

    void me::onLeave(visitInfo i, blockExpr& me) {
        NAMU_DI("verify: blockExpr: last stmt should match to ret type");
        const narr& stmts = me.getStmts();
        if(nul(stmts) || stmts.len() <= 0) return; // will be catched to another verification.

        NAMU_DI("verify: blockExpr: block.outFrame()");
    }


    void me::onVisit(visitInfo i, defAssignExpr& me) {
        NAMU_DI("verify: defAssignExpr: duplication of variable.");
        const scopes& top = thread::get().getNowFrame().getTop();
        if(nul(top)) return;
        const std::string name = me.getSubName();
        if(top.getContainer().has(name))
            return _srcErr(me.getPos(), errCode::ALREADY_DEFINED_VAR, name.c_str(), me.getEval().getType().getName()
                    .c_str());

        NAMU_DI("verify: defAssignExpr: is definable?");
        const node& rhs = me.getRight();
        if(nul(rhs))
            return _srcErr(me.getPos(), errCode::CANT_DEF_VAR, me.getSubName().c_str(), "null");

        NAMU_DI("verify: defAssignExpr: '%s %s' has defined.",
                me.getSubName().c_str(),
                nul(rhs) ? "name" : rhs.getType().getName().c_str());

        node& to = me.getTo();
        str new1 = me.isOnDefBlock() ? rhs.as<node>() : rhs.getEval();
        NAMU_DI("verify: defAssignExpr: new1[%s]", new1 ? new1->getType().getName().c_str() : "null");

        if(nul(to)) {
            frame& fr = thread::get()._getNowFrame();
            scopes& sc = (scopes&) fr.subs();
            if(sc.getContainer().has(me.getSubName()))
                return _srcErr(me.getPos(), errCode::ALREADY_DEFINED_VAR, me.getSubName().c_str(),
                        rhs.getType().getName().c_str());
            fr.pushLocal(me.getSubName(), *new1);

        } else {
            scopes& sc = (scopes&) to.run()->subs();
            if(sc.getContainer().has(me.getSubName()))
                return _srcErr(me.getPos(), errCode::ALREADY_DEFINED_VAR, me.getSubName().c_str(),
                        rhs.getType().getName().c_str());
            sc.add(me.getSubName(), *new1);
        }
    }

    void me::onVisit(visitInfo i, defVarExpr& me) {
        NAMU_DI("verify: defVarExpr: check duplication");
        const scopes& top = thread::get().getNowFrame().getTop();
        const node& eval = me.getEval();
        if(nul(eval)) return _srcErr(me.getPos(), errCode::TYPE_NOT_EXIST, me.getName().c_str());

        const ntype& t = eval.getType();
        const nchar* typeName = nul(t) ? "null" : t.getName().c_str();
        if(nul(top)) return;
        if(top.getContainer().has(me.getName()))
            return _srcErr(me.getPos(), errCode::ALREADY_DEFINED_VAR, me.getName().c_str(), typeName);


        // 'check duplication' must be front of 'is %s definable':
        std::string name = me.getName();
        NAMU_DI("verify: defVarExpr: is %s definable?", name.c_str());
        if(name == "") return _srcErr(me.getPos(), errCode::HAS_NO_NAME);
        const node& org = me.getOrigin();
        if(nul(org)) return _srcErr(me.getPos(), errCode::NO_ORIGIN, name.c_str());

        if(nul(t))
            _srcErr(me.getPos(), errCode::CANT_DEF_VAR, name.c_str(), typeName);

        nbool res = me._where ? me._where->add(name.c_str(), eval) : thread::get()._getNowFrame()
                .pushLocal(name, eval);
        if(!res)
            NAMU_E("verify: defVarExpr: define variable %s is failed.", name.c_str());
    }

    void me::onVisit(visitInfo i, defSeqExpr& me) {
        NAMU_DI("verify: defSeqExpr: check lhs & rhs");
        if(nul(me.getStart())) return _srcErr(me.getPos(), errCode::LHS_IS_NULL);
        if(nul(me.getEnd())) return _srcErr(me.getPos(), errCode::RHS_IS_NULL);
    }

    void me::onVisit(visitInfo i, defArrayExpr& me) {
        NAMU_DI("verify: defArrayExpr: check all elements");
        const node& type = me.getArrayType();
        if(nul(type)) return _srcErr(me.getPos(), errCode::ELEM_TYPE_DEDUCED_NULL);
        if(type.isSuper<obj>())
            return _srcErr(me.getPos(), errCode::ELEM_TYPE_DEDUCED_WRONG, type.getType().getName().c_str());
    }

    void me::onVisit(visitInfo i, FAOExpr& me) {
        NAMU_DI("verify: FAOExpr: lhs & rhs should bind something.");
        const node& lhs = me.getLeft();
        const node& rhs = me.getRight();
        if(nul(lhs)) return _srcErr(me.getPos(), errCode::LHS_IS_NULL);
        if(nul(rhs)) return _srcErr(me.getPos(), errCode::RHS_IS_NULL);

        NAMU_DI("verify: FAOExpr: finding eval of l(r)hs.");
        const node& lEval = lhs.getEval();
        const node& rEval = rhs.getEval();
        if(nul(lEval)) return _srcErr(me.getPos(), errCode::LHS_IS_NULL);
        if(nul(rEval)) return _srcErr(me.getPos(), errCode::RHS_IS_NULL);

        if(!checkEvalType(lEval)) return _srcErr(me.getPos(), errCode::LHS_IS_NOT_ARITH, lEval.getType().getName().c_str());
        if(!checkEvalType(rEval)) return _srcErr(me.getPos(), errCode::RHS_IS_NOT_ARITH, rEval.getType().getName().c_str());
    }

    void me::onVisit(visitInfo i, getExpr& me) {
        // TODO: I have to check that the evalType has what matched to given _params.
        // Until then, I rather use as() func and it makes slow emmersively.
        NAMU_DI("verify: getExpr: isRunnable: %s.%s", me.getType().getName().c_str(), me.getSubName().c_str());
        if(nul(me.getEval())) return _srcErr(me.getPos(), errCode::EVAL_NULL_TYPE);
        str got = me._get();
        if(!got) {
            const node& from = me.getMe();
            return _srcErr(me.getPos(), errCode::CANT_ACCESS, from.getType().getName().c_str(), me._name.c_str());
        }
        NAMU_DI("verify: getExpr: isRunnable: got=%s, me=%s", got->getType().getName().c_str(),
                me.getType().getName().c_str());
    }

    void me::onVisit(visitInfo i, returnExpr& me) {
        NAMU_DI("verify: returnExpr: checks evalType of func is matched to me");
        const func& f = thread::get().getNowFrame().getFunc();
        if(nul(f)) return _srcErr(me.getPos(), errCode::NO_FUNC_INFO);

        const node& myEval = me.getEval();
        if(nul(myEval)) return _srcErr(me.getPos(), errCode::EXPR_EVAL_NULL);
        NAMU_DI("verify: returnExpr: myEval=%s", myEval.getType().getName().c_str());
        const ntype& myType = myEval.getType();
        str retType = f.getRet().as<node>();
        const type& fType = retType->getType();
        NAMU_DI("verify: returnExpr: checks return[%s] == func[%s]", myType.getName().c_str(),
            fType.getName().c_str());

        if(!myType.isImpli(fType))
            return _srcErr(me.getPos(), errCode::RET_TYPE_NOT_MATCH, myType.getName().c_str(), fType.getName().c_str());
    }

    void me::onVisit(visitInfo i, runExpr& me) {
        NAMU_DI("verify: runExpr: is it possible to run?");
        if(nul(me.getMe())) return _srcErr(me.getPos(), errCode::CANT_CAST_TO_NODE);

        tstr<baseObj> ased  = me.getMe().as<baseObj>();
        if(!ased) return _srcErr(me.getPos(), errCode::CANT_CAST_TO_NODE);

        node& anySub = me.getSubject();
        if(nul(anySub)) return _srcErr(me.getPos(), errCode::SUB_NOT_EXIST);

        NAMU_DI("verify: runExpr: anySub[%s]", anySub.getType().getName().c_str());

        args& a = me.getArgs();
        a.setMe(*ased);

        getExpr& cast = anySub.cast<getExpr>();
        if(!nul(cast))
            cast.setMe(*ased);

        str derivedSub = anySub.as<node>();
        if(!derivedSub) return _srcErr(me.getPos(), errCode::CANT_ACCESS, ased->getType().getName().c_str(), "sub-node");
        NAMU_DI("verify: runExpr: derivedSub[%s]", derivedSub->getType().getName().c_str());
        if(!derivedSub->canRun(me.getArgs())) return _srcErr(me.getPos(), errCode::OBJ_WRONG_ARGS, me.getArgs().asStr().c_str());

        a.setMe(nulOf<baseObj>());
    }

    void me::onVisit(visitInfo i, mgdFunc& me) {
        onVisit(i, (mgdFunc::super&) me);

        NAMU_DI("verify: mgdFunc: retType exists and stmts exist one at least");
        const node& retType = me.getRet();
        if(nul(retType)) return _srcErr(me.getPos(), errCode::NO_RET_TYPE);
        if(!retType.isSub(ttype<node>::get()))
            return _srcErr(me.getPos(), errCode::WRONG_RET_TYPE, retType.getType().getName().c_str());

        blockExpr& blk = (blockExpr&) me.getBlock();
        if(nul(blk) || blk.getStmts().len() <= 0)
            return _err(blk.getPos(), errCode::NO_STMT_IN_FUNC);

        NAMU_DI("verify: mgdFunc[%s]: %s iterateBlock[%d]", i.name.c_str(),
                me.getType().getName().c_str(), me._blk->subs().len());

        scope* s = new scope();
        _prepareArgsAlongParam(me.getParams(), *s);

        baseObj& meObj = frame::_getMe();
        if(nul(meObj)) return _srcErr(me.getPos(), errCode::FUNC_REDIRECTED_OBJ);

        meObj.inFrame(nulOf<bicontainable>());
        me.inFrame(*s);
        // !important!:
        //  frameInteraction to blockstmt should be controlled by its holder, mgdFunc.
        //  for validation of implicitReturn, I need to postpone frame to be released by blockstmt.
        //  if I passed the control to blockstmts, it released its own frame before checking
        //  implicit Return.
        //
        //  so, all expressions contains blockstmt need to control in/out frame instead of blockstmt.
        me.getBlock().inFrame(nulOf<bicontainable>());
    }

    void me::_verifyMgdFuncImplicitReturn(mgdFunc& me) {
        str ret = me.getRet().as<node>();
        const type& retType = ret->getType();
        const node& lastStmt = *me.getBlock().getStmts().last();
        NAMU_DI("verify: mgdFunc: last stmt[%s] should matches to return type[%s]",
                lastStmt.getType().getName().c_str(), retType.getName().c_str());

        if(!(lastStmt.isSub<returnExpr>() || lastStmt.isSub<retExpr>()) &&
            retType == ttype<nVoid>::get()) {
            NAMU_DI("verify: mgdFunc: implicit return won't verify when retType is void.");
            return;
        }

        const node& lastEval = lastStmt.getEval();
        if(nul(lastEval)) return _err(lastStmt.getPos(), NO_RET_TYPE);
        const ntype& lastType = lastEval.getType(); // to get type of expr, always uses evalType.
        if(nul(lastType)) return _err(lastStmt.getPos(), NO_RET_TYPE);
        if(!lastType.isImpli(retType)) return _err(lastStmt.getPos(), errCode::RET_TYPE_NOT_MATCH, lastType.getName().c_str(),
                retType.getName().c_str());
    }

    void me::_prepare() {
        _us.clear();
        _loopCnt = 0;
    }

    void me::onLeave(visitInfo i, mgdFunc& me) {
        _verifyMgdFuncImplicitReturn(me);

        me.getBlock().outFrame();

        baseObj& meObj = frame::_getMe();
        me.outFrame();
        meObj.outFrame();
    }

    void me::onVisit(visitInfo i, baseObj& me) {
        _us.push_back(&frame::_setMe(me));

        NAMU_DI("verify: baseObj: %s push me[%x] len=%d",
                me.getType().getName().c_str(), &frame::_getMe(), me.subs().len());

        onVisit(i, (baseObj::super&) me);
    }

    void me::onLeave(visitInfo i, baseObj& me) {
        frame::_setMe(*_us.back());
        NAMU_DI("verify: baseObj: pop me[%x]", &frame::_getMe());
        _us.pop_back();
    }

    void me::onVisit(visitInfo i, genericObj& me) {
        NAMU_DI("verify: genericObj: cache check");
        for(auto e : me._cache)
            if(nul(e.second))
                _srcErr(me.getPos(), errCode::MAKE_GENERIC_FAIL, e.first.c_str());
    }

    void me::onLeave(visitInfo i, genericObj& me) {
        NAMU_DI("verify: genericObj: onLeave");
        // DO NOTHING, BUT LEAVE THIS FUNC:
        //  if I don't have this func, getGenericExpr::super (=baseObj)'s one will be called.
        //  and me pointer will be erased too inside the func.
    }

    void me::onVisit(visitInfo i, forExpr& me) {
        str container = me._container;
        str conAsed = container->as<node>();
        str elemType = conAsed->run("getElemType");
        if(!elemType)
            return _srcErr(me.getPos(), errCode::ELEM_TYPE_IS_NULL);

        const std::string& name = me.getLocalName();
        NAMU_DI("verify: forExpr: define iterator '%s %s'", elemType->getType().getName().c_str(),
                name.c_str());

        me.getBlock().inFrame(nulOf<bicontainable>());
        thread::get()._getNowFrame().pushLocal(name, *elemType);

        _loopCnt++;
    }

    void me::onLeave(visitInfo i, forExpr& me) {
        NAMU_DI("verify: forExpr: onLeave");
        me.getBlock().outFrame();

        _loopCnt--;
    }

    void me::onVisit(visitInfo i, breakExpr& me) {
        NAMU_DI("verify: breakExpr: declared inside of loop?");
        if(_loopCnt <= 0) return _srcErr(me.getPos(), errCode::BREAK_OUTSIDE_OF_LOOP);
    }

    void me::onVisit(visitInfo i, nextExpr& me) {
        NAMU_DI("verify: nextExpr: declared inside of loop?");
        if(_loopCnt <= 0) return _srcErr(me.getPos(), errCode::NEXT_OUTSIDE_OF_LOOP);
    }

    void me::onVisit(visitInfo i, ifExpr& me) {
        NAMU_DI("verify: ifExpr: condition-expr can be casted into bool?");
        node& condition = me.getCondition();
        if(nul(condition))
            return _srcErr(me.getPos(), errCode::CONDITION_IS_EMPTY);
        if(!condition.is<nBool>())
            return _srcErr(me.getPos(), errCode::CONDITION_CANT_CAST_TO_BOOL);
    }
}
