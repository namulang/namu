#include "verifier.hpp"
#include "../frame/frame.hpp"
#include "../frame/thread.hpp"
#include "../loader/errReport.hpp"
#include "../builtin/primitive.hpp"
#include "../ast.hpp"
#include "../frame/starter.hpp"

namespace namu {

    NAMU_DEF_ME(verifier)

#define GUARD(...) if(isFlag(GUARD)) NAMU_I(__VA_ARGS__)

    namespace {
        str primitives[] = {
            new nInt(),
            new nFlt(),
            new nStr(),
            new nByte(),
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
    }

    me::verifier() { rel(); }

    void me::_onWork() {
        if(nul(thread::get())) {
            error(errCode::NO_THREAD);
            return;
        }

        super::_onWork();
    }

    void me::_onEndWork() {
        _postpare();
    }

    // verification:
    nbool me::onVisit(visitInfo i, node& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: node: no same variable=%d", me.subs().len());
        if(me.isSub<frame>()) return true;

        for(auto e=me.subs().begin(); e ;++e) {
            if(me.subAll<baseObj>(e.getKey()).len() > 1)
                return error(*e, errCode::DUP_VAR, e.getKey().c_str()), true;
        }
        return true;
    }

    nbool me::onVisit(visitInfo i, asExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: asExpr: _me & _as aren't null");
        if(nul(me.getMe())) return error(me, errCode::LHS_IS_NULL), true;
        if(nul(me.getAs())) return error(me, errCode::RHS_IS_NULL), true;
        if(me.getAs().isSub<nVoid>()) return error(me, errCode::VOID_NOT_CAST), true;

        NAMU_I("verify: asExpr: checks that me can cast to 'as'");
        if(!me.getMe().is(me.getAs()))
            return error(me, errCode::CAST_NOT_AVAILABLE, me.getMe().getType().getName().c_str(),
                    me.getAs().getType().getName().c_str()), true;

        NAMU_I("verify: asExpr: rhs shouldn't be expression");
        if(!me.getAs().asImpli<node>())
            return error(me, errCode::CAST_TO_UNKNOWN), true;
        return true;
    }

    nbool me::onVisit(visitInfo i, assignExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: assignExpr: set evalType");
        str leftEval = me.getLeft().getEval();
        if(!leftEval) return error(me, errCode::LHS_IS_NULL), true;
        const ntype& ltype = leftEval->getType();
        if(nul(ltype)) return error(me, errCode::LHS_IS_NULL), true;
        str rightEval = me.getRight().getEval();
        if(!rightEval) return error(me, errCode::RHS_IS_NULL), true;
        const ntype& rtype = rightEval->getType();
        if(nul(rtype)) return error(me, errCode::RHS_IS_NULL), true;
        if(!rtype.isImpli(ltype))
            return error(me, errCode::TYPE_NOT_COMPATIBLE, rtype.getName().c_str(), ltype.getName()
                    .c_str()), true;

        // verify rvalue and lvalue:
        //  first of all:
        //      in namulang there is no lvalue concept. to involve lvalue concept,
        //      I need to bring new concept or feature like 'const' but I don't want to.
        //      because the direction of this language is a toy lang. DON'T be serious.
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
        NAMU_I("verify: assignExpr: checks rvalue");
        const node& lhs = me.getLeft();
        if(!lhs.isSub<getExpr>()/* TODO: && !lhs.isSub<ElementExpr>()*/)
            return error(me, errCode::ASSIGN_TO_RVALUE, me.getRight().getType().getName().c_str(),
                    lhs.getType().getName().c_str()), true;
        return true;
    }

    nbool me::onVisit(visitInfo i, blockExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: blockExpr: it will iterate all subnodes[%d]", me.getStmts().len());
        return true;
    }

    void me::onLeave(visitInfo i, blockExpr& me) {
        GUARD("%s.onLeave(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: blockExpr: last stmt should match to ret type");
        const narr& stmts = me.getStmts();
        if(nul(stmts) || stmts.len() <= 0) return; // will be catched to another verification.

        func& parent = i.parent ? i.parent->cast<func>() : nulOf<func>();
        if(!nul(parent))
            _verifyMgdFuncImplicitReturn(parent);
    }


    void me::onLeave(visitInfo i, defAssignExpr& me) {
        GUARD("%s.onLeave(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: defAssignExpr: duplication of variable.");
        const nbicontainer& top = thread::get().getNowFrame().getTop();
        if(nul(top)) return;

        const std::string name = me.getSubName();
        if(top.has(name))
            return error(me, errCode::ALREADY_DEFINED_VAR, name.c_str(), me.getEval()->getType().getName()
                    .c_str());

        NAMU_I("verify: defAssignExpr: is definable?");
        const node& rhs = me.getRight();
        if(nul(rhs))
            return error(me, errCode::CANT_DEF_VAR, me.getSubName().c_str(), "null");

        NAMU_I("verify: defAssignExpr: '%s %s' has defined.", me.getSubName().c_str(),
                nul(rhs) ? "name" : rhs.getType().getName().c_str());

        node& to = me.getTo();
        str new1 = me.isOnDefBlock() ? rhs.as<node>() : rhs.getEval();

        NAMU_I("verify: defAssignExpr: new1[%s]", new1 ? new1->getType().getName().c_str() : "null");
        if(!new1)
            return error(me, errCode::RHS_NOT_EVALUATED);
        if(!new1->isComplete())
            return error(me, errCode::ACCESS_TO_INCOMPLETE);
        if(new1->isSub<nVoid>())
            return error(me, errCode::VOID_CANT_DEFINED);

        // when you define variable, I need to clone it:
        //  if don't, it may be incomplete object.
        if(nul(to)) {
            frame& fr = thread::get()._getNowFrame();
            scopes& sc = (scopes&) fr.subs();
            if(sc.getContainer().has(me.getSubName()))
                return error(me, errCode::ALREADY_DEFINED_VAR, me.getSubName().c_str(),
                        rhs.getType().getName().c_str());
            fr.pushLocal(me.getSubName(), *new1);

        } else {
            scopes& sc = (scopes&) to.run()->subs();
            if(sc.getContainer().has(me.getSubName()))
                return error(me, errCode::ALREADY_DEFINED_VAR, me.getSubName().c_str(),
                        rhs.getType().getName().c_str());
            sc.add(me.getSubName(), *new1);
        }
    }

    nbool me::onVisit(visitInfo i, defPropExpr& me) {
        GUARD("%s.onLeave(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: defPropExpr: check duplication");
        const nbicontainer& top = thread::get().getNowFrame().getTop();
        str eval = me.getEval();
        if(!eval)
            return error(me, errCode::TYPE_NOT_EXIST, me.getName().c_str()), true;
        if(eval->isSub<nVoid>())
            return error(me, errCode::VOID_CANT_DEFINED), true;

        NAMU_I("verify: defPropExpr: check whether make a void container.");
        const narr& beans = eval->getType().getBeans();
        for(const node& bean : beans)
            if(bean.isSub<nVoid>())
                return error(me, errCode::NO_VOID_CONTAINER), true;

        const ntype& t = eval->getType();
        const nchar* typeName = nul(t) ? "null" : t.getName().c_str();
        if(nul(top)) return true;
        if(top.has(me.getName()))
            return error(me, errCode::ALREADY_DEFINED_VAR, me.getName().c_str(), typeName), true;


        // 'check duplication' must be front of 'is %s definable':
        std::string name = me.getName();
        NAMU_I("verify: defPropExpr: is %s definable?", name.c_str());
        if(name == "") return error(me, errCode::HAS_NO_NAME), true;
        const node& org = me.getOrigin();
        if(nul(org)) return error(me, errCode::NO_ORIGIN, name.c_str()), true;

        if(nul(t))
            error(me, errCode::CANT_DEF_VAR, name.c_str(), typeName);

        // when you define variable, I need to clone it:
        //  if don't, it may be incomplete object.
        if(!eval->canRun(args()))
            error(me, errCode::DONT_HAVE_CTOR, name.c_str());
        else {
            nbool res = me._where ? me._where->add(name.c_str(), (node*) eval->clone()) : thread::get()._getNowFrame()
                    .pushLocal(name, (node*) eval->clone());
            if(!res)
                NAMU_I("verify: defPropExpr: define variable %s is failed.", name.c_str());
        }
        return true;
    }

    nbool me::onVisit(visitInfo i, defSeqExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: defSeqExpr: check lhs & rhs");
        if(nul(me.getStart())) return error(me, errCode::LHS_IS_NULL), true;
        if(nul(me.getEnd())) return error(me, errCode::RHS_IS_NULL), true;

        NAMU_I("verify: defSeqExpr: lhs & rhs is sort of Int?");
        if(!me.getStart().isImpli<nInt>()) return error(me, errCode::SEQ_SHOULD_INT_COMPATIBLE), true;
        if(!me.getEnd().isImpli<nInt>()) return error(me, errCode::SEQ_SHOULD_INT_COMPATIBLE), true;
        return true;
    }

    nbool me::onVisit(visitInfo i, defArrayExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: defArrayExpr: check all elements");
        const node& type = me.getArrayType();
        if(nul(type)) return error(me, errCode::ELEM_TYPE_DEDUCED_NULL), true;
        if(type.isSuper<obj>())
            return error(me, errCode::ELEM_TYPE_DEDUCED_WRONG, type.getType().getName().c_str()), true;
        if(type.isSub<nVoid>())
            return error(me, errCode::ELEM_TYPE_NOT_VOID), true;
        return true;
    }

    nbool me::onVisit(visitInfo i, FBOExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: FBOExpr: lhs & rhs should bind something.");
        const node& lhs = me.getLeft();
        const node& rhs = me.getRight();
        if(nul(lhs)) return error(me, errCode::LHS_IS_NULL), true;
        if(nul(rhs)) return error(me, errCode::RHS_IS_NULL), true;

        NAMU_I("verify: FBOExpr: finding eval of l(r)hs.");
        str lEval = lhs.getEval();
        str rEval = rhs.getEval();
        if(!lEval) return error(me, errCode::LHS_IS_NULL), true;
        if(!rEval) return error(me, errCode::RHS_IS_NULL), true;

        if(!checkEvalType(*lEval)) return error(me, errCode::LHS_IS_NOT_ARITH, lEval->getType().getName().c_str()), true;
        if(!checkEvalType(*rEval)) return error(me, errCode::RHS_IS_NOT_ARITH, rEval->getType().getName().c_str()), true;

        if(nul(lEval->deduce(*rEval)))
            return error(me, errCode::IMPLICIT_CAST_NOT_AVAILABLE,
                    lEval->getType().getName().c_str(), rEval->getType().getName().c_str()), true;

        auto r = me.getRule();
        if((lEval->isSub<nStr>() || rEval->isSub<nStr>())) {
            switch(r) {
                case FBOExpr::AND: case FBOExpr::OR: case FBOExpr::SUB: case FBOExpr::DIV:
                case FBOExpr::MOD: case FBOExpr::BITWISE_AND: case FBOExpr::BITWISE_XOR:
                case FBOExpr::BITWISE_OR: case FBOExpr::LSHIFT: case FBOExpr::RSHIFT:
                    return error(me, errCode::STRING_IS_NOT_PROPER_TO_OP), true;

                default:;
            }
        }
        return true;
    }

    nbool me::onVisit(visitInfo i, FUOExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: FUOExpr: string isn't proper to any FUO operator");
        str eval = me.getEval();
        if(eval && eval->isImpli<nStr>())
            return error(me, errCode::STRING_IS_NOT_PROPER_TO_OP), true;

        return true;
    }

    nbool me::onVisit(visitInfo i, getExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        // TODO: I have to check that the evalType has what matched to given _params.
        // Until then, I rather use as() func and it makes slow emmersively.
        NAMU_I("verify: getExpr: isRunnable: %s.%s", me.getType().getName().c_str(), me.getSubName().c_str());
        if(!me.getEval()) return error(me, errCode::WHAT_IS_THIS_IDENTIFIER, me.getSubName().c_str()), true;
        auto matches = me._get(true);
        if(matches.isEmpty()) {
            const node& from = me.getMe();
            return error(me, errCode::CANT_ACCESS, me._name.c_str(), from.getType().getName().c_str()), true;
        }
        if(matches.len() >= 2) {
            // TODO: leave all ambigious candidates as err.
            return error(me, errCode::AMBIGIOUS_ACCESS, i.name.c_str()), true;
        }
        str got = matches.getMatch();
        NAMU_I("verify: getExpr: isRunnable: got=%s, me=%s", got->getType().getName().c_str(),
                me.getType().getName().c_str());

        NAMU_I("verify: getExpr: accesses to incomplete 'me' object");
        str asedMe = me.getMe().as<node>();
        if(asedMe && !asedMe->isComplete())
            return error(me, errCode::ACCESS_TO_INCOMPLETE), true;
        return true;
    }

    nbool me::onVisit(visitInfo i, retExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: retExpr: checks evalType of func is matched to me");
        const baseFunc& f = thread::get().getNowFrame().getFunc();
        if(nul(f)) return error(me, errCode::NO_FUNC_INFO), true;

        str myEval = me.getEval();
        if(!myEval) return error(me, errCode::EXPR_EVAL_NULL), true;

        NAMU_I("verify: retExpr: myEval=%s", myEval->getType().getName().c_str());
        const ntype& myType = myEval->getType();
        str retType = f.getRet()->as<node>();
        const type& fType = retType->getType();

        NAMU_I("verify: retExpr: checks return[%s] == func[%s]", myType.getName().c_str(),
            fType.getName().c_str());

        if(!myType.isImpli(fType))
            return error(me, errCode::RET_TYPE_NOT_MATCH, myType.getName().c_str(), fType.getName().c_str()), true;
        return true;
    }

    nbool me::onVisit(visitInfo i, runExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: runExpr: is it possible to run?");
        if(nul(me.getMe())) return error(me, errCode::DONT_KNOW_ME), true;

        str ased = me.getMe().getEval();
        if(!ased) return error(me, errCode::DONT_KNOW_ME), true;

        node& anySub = me.getSubject();
        if(nul(anySub)) return error(me, errCode::FUNC_NOT_EXIST), true;

        NAMU_I("verify: runExpr: anySub[%s]", anySub.getType().getName().c_str());

        args& a = me.getArgs();
        a.setMe(*ased);

        getExpr& cast = anySub.cast<getExpr>();
        if(!nul(cast))
            cast.setMe(*ased);

        str derivedSub = anySub.as<node>();
        if(!derivedSub) return error(me, errCode::CANT_ACCESS, ased->getType().getName().c_str(), "sub-node"), true;

        NAMU_I("verify: runExpr: derivedSub[%s]", derivedSub->getType().getName().c_str());
        if(!derivedSub->canRun(me.getArgs())) {
            const baseFunc& derivedCast = derivedSub->cast<baseFunc>();
            std::string params = nul(derivedCast) ? "ctor" : _asStr(derivedCast.getParams());
            return error(me, errCode::OBJ_WRONG_ARGS, i.name.c_str(), me.getArgs().asStr().c_str(), params.c_str()), true;
        }

        a.setMe(nulOf<baseObj>());
        return true;
    }

    std::string me::_asStr(const params& ps) {
        std::string ret;
        nbool first = true;
        for(const param& p : ps) {
            ret += (first ? "" : ",") + p.getOrigin().getType().getName();
            first = false;
        }

        return ret;
    }

    nbool me::onVisit(visitInfo i, func& me) {
        onVisit(i, (func::super&) me);

        obj& meObj = frame::_getMe().cast<obj>(); // TODO: same to 'thread::get().getNowFrame().getMe().cast<obj>();'
        if(nul(meObj)) return error(me, errCode::FUNC_REDIRECTED_OBJ), true;

        NAMU_I("verify: check func duplication");
        const nbicontainer& top = meObj.getShares();
        ncnt len = me.getParams().len();
        const node& errFound = top.get([&](const std::string& key, const node& val) {
            if(key != i.name) return false;
            if(&val == &me) return false;

            const baseFunc& cast = val.cast<baseFunc>();
            if(nul(cast))
                // this has same name on shares, but it's not func! it's not valid.
                // this could be an origin obj.
                return true;

            const params& castPs = cast.getParams();
            if(castPs.len() != len) return false;

            for(int n=0; n < castPs.len() ;n++) {
                str lhs = castPs[n].getOrigin().getEval();
                str rhs = me.getParams()[n].getOrigin().getEval();
                if(lhs->getType() != rhs->getType())
                    return false;
            }

            return true;
        });
        if(!nul(errFound))
            error(me, errCode::ALREADY_DEFINED_FUNC, i.name.c_str());

        //  obj or property shouldn't have same name to any func.
        NAMU_I("verify: check func has same name to field");
        if(!nul(meObj.getOwns().get(i.name)))
            error(me, errCode::ALREADY_DEFINED_IDENTIFIER, i.name.c_str());

        NAMU_I("verify: func: main func return type should be int or void");
        if(i.name == starter::MAIN) {
            str ret = me.getRet();
            if(!ret->isSub<nInt>() && !ret->isSub<nVoid>())
                error(me, errCode::MAIN_FUNC_RET_TYPE);
        }

        NAMU_I("verify: func: retType exists and stmts exist one at least");
        str retType = me.getRet();
        if(!retType) return error(me, errCode::NO_RET_TYPE), true;
        if(!retType->isSub(ttype<node>::get()))
            return error(me, errCode::WRONG_RET_TYPE, retType->getType().getName().c_str()), true;

        blockExpr& blk = (blockExpr&) me.getBlock();
        if(nul(blk) || blk.getStmts().len() <= 0) {
            if(i.name == starter::MAIN)
                error(blk, errCode::MAIN_SHOULD_HAVE_STMTS);
            /*TODO: uncomment after implement abstract:
            if(!func.isAbstract() && !retType->isSub<nVoid>())
                error(...)
            */
            return true;
        }

        NAMU_I("verify: func: 'break' or 'next' can't be used to last stmt");
        const node& lastStmt = *blk.getStmts().last();
        if(lastStmt.isSub<retStateExpr>())
            return error(lastStmt, errCode::FUNC_SHOULD_RETURN_SOMETHING), true;

        NAMU_I("verify: func[%s]: %s iterateBlock[%d]", i.name.c_str(), me.getType().getName().c_str(),
                me._blk->subs().len());

        // sequence of adding frame matters:
        //  object scope is first:
        meObj.inFrame();

        //  parameters of func is second:
        scope* s = new scope();
        for(const auto& p : me.getParams()) {
            if(p.getOrigin().isSub<nVoid>()) {
                error(me, errCode::PARAM_NOT_VOID, p.getName().c_str());
                continue;
            }
            s->add(p.getName(), *(node*) p.getOrigin().as<node>()->clone());
        }

        //  function's subs are third:
        me.inFrame(*s);

        //  blockExpr is fourth:
        //      blockExpr shouldn't interact the frame on their side. that's concept.
        blk.inFrame();
        return true;
    }

    void me::_verifyMgdFuncImplicitReturn(func& me) {
        str ret = me.getRet()->as<node>();
        const type& retType = ret->getType();
        const node& lastStmt = *me.getBlock().getStmts().last();
        NAMU_I("verify: func: last stmt[%s] should matches to return type[%s]",
                lastStmt.getType().getName().c_str(), retType.getName().c_str());

        if(!lastStmt.isSub<retExpr>() && retType == ttype<nVoid>::get()) {
            NAMU_I("verify: func: implicit return won't verify when retType is void.");
            return;
        }

        str lastEval = lastStmt.getEval();
        if(!lastEval) return error(lastStmt, NO_RET_TYPE);
        const ntype& lastType = lastEval->getType(); // to get type of expr, always uses evalType.
        if(nul(lastType)) return error(lastStmt, NO_RET_TYPE);
        if(!lastType.isImpli(retType)) return error(lastStmt, errCode::RET_TYPE_NOT_MATCH, lastType.getName().c_str(),
                retType.getName().c_str());
    }

    void me::_prepare() {
        super::_prepare();
        _us.clear();
        _recentLoops.clear();

        baseObj& root = getTask().cast<baseObj>();
        if(!nul(root))
            // before verify obj and its subs, I need to register onto frame.
            root.inFrame();
    }

    void me::_postpare() {
        baseObj& root = getTask().cast<baseObj>();
        if(!nul(root))
            root.outFrame();
    }

    void me::onLeave(visitInfo i, func& me) {
        me.getBlock().outFrame();
        me.outFrame();
        baseObj& meObj = frame::_getMe();
        meObj.outFrame();
    }

    nbool me::onVisit(visitInfo i, baseObj& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: baseObj: %s push me[%x] len=%d", me.getType().getName().c_str(),
                &frame::_getMe(), me.subs().len());
        _us.push_back(&frame::_setMe(me));

        NAMU_I("verify: baseObj: iterate all subs and checks void type variable");
        for(const node& elem : me.subs())
            if(elem.isSub<nVoid>())
                // don't finsh and return. i need to check all subs by calling super::onVisit().
                error(elem, errCode::VOID_CANT_DEFINED);

        onVisit(i, (baseObj::super&) me);
        return true;
    }

    void me::onLeave(visitInfo i, baseObj& me) {
        GUARD("%s.onLeave(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        frame::_setMe(*_us.back());
        NAMU_I("verify: baseObj: pop me[%x]", &frame::_getMe());
        _us.pop_back();
    }

    nbool me::onVisit(visitInfo i, genericObj& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: genericObj: cache check");
        for(auto e : me._cache)
            if(nul(e.second))
                error(me, errCode::MAKE_GENERIC_FAIL, e.first.c_str());
        return true;
    }

    void me::onLeave(visitInfo i, genericObj& me) {
        GUARD("%s.onLeave(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: genericObj: onLeave");
        // DO NOTHING, BUT LEAVE THIS FUNC:
        //  if I don't have this func, getGenericExpr::super (=baseObj)'s one will be called.
        //  and me pointer will be erased too inside the func.
    }

    nbool me::onVisit(visitInfo i, forExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        str container = me._container;
        str conAsed = container->getEval();
        if(!conAsed)
            return error(me, errCode::CONTAINER_IS_NULL), true;
        str elemType = conAsed->run("getElemType");
        if(!elemType)
            return error(me, errCode::ELEM_TYPE_IS_NULL), true;

        const std::string& name = me.getLocalName();
        NAMU_I("verify: forExpr: define iterator '%s %s'", elemType->getType().getName().c_str(),
                name.c_str());

        me.getBlock().inFrame();
        thread::get()._getNowFrame().pushLocal(name, (node*) elemType->clone());
        _recentLoops.push_back(&me);
        return true;
    }

    void me::onLeave(visitInfo i, forExpr& me) {
        GUARD("%s.onLeave(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: forExpr: eval Value check: is an array?");
        tstr<arr> eval = me.getEval();
        if(!eval) return error(me, errCode::LOOP_NO_RET_ARR);

        NAMU_I("verify: forExpr: onLeave");
        me.getBlock().outFrame();
        _recentLoops.pop_back();
    }

    nbool me::onVisit(visitInfo i, whileExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: whileExpr: onVisit");
        _recentLoops.push_back(&me);
        return true;
    }

    void me::onLeave(visitInfo i, whileExpr& me) {
        GUARD("%s.onLeave(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: whileExpr: eval Value check: is an array?");
        tstr<arr> eval = me.getEval();
        if(!eval) return error(me, errCode::LOOP_NO_RET_ARR);

        NAMU_I("verify: whileExpr: onLeave");
        _recentLoops.pop_back();
    }

    nbool me::onVisit(visitInfo i, breakExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: breakExpr: declared outside of loop?");
        if(_recentLoops.size() <= 0) return error(me, errCode::BREAK_OUTSIDE_OF_LOOP), true;
        return true;
    }

    nbool me::onVisit(visitInfo i, nextExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: nextExpr: declared outside of loop?");
        if(_recentLoops.size() <= 0) return error(me, errCode::NEXT_OUTSIDE_OF_LOOP), true;
        return true;
    }

    nbool me::onVisit(visitInfo i, ifExpr& me) {
        GUARD("%s.onVisit(%s)", getType().getName().c_str(), me.getType().getName().c_str());

        NAMU_I("verify: ifExpr: condition-expr can be casted into bool?");
        node& condition = me.getCondition();
        if(nul(condition))
            return error(me, errCode::CONDITION_IS_EMPTY), true;
        if(!condition.is<nBool>())
            return error(me, errCode::CONDITION_CANT_CAST_TO_BOOL), true;
        return true;
    }
}
