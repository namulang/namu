#include "assignExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"
#include "../../frame/thread.hpp"
#include "../obj.hpp"

namespace namu {

    WRD_DEF_ME(assignExpr)

    me::iter me::_getScopeIterOfLhs() {
        if(!_lhs) return iter();

        getExpr& cast = _lhs->cast<getExpr>();
        if(nul(cast)) return iter();
        // TODO: elementExpr

        iter ret = cast.getFrom().subs().iterate(cast.getSubName());
        while(ret) {
            if(!nul(ret.getVal<baseObj>()))
                return ret;

            ++ret;
        }

        return iter();
    }

    WRD_VERIFY(assignExpr, verifyIter, {
        if(!it._getScopeIterOfLhs())
            _srcErr(errCode::NOT_EXIST, getType().getName().c_str());
    })

    WRD_VERIFY({
        WRD_DI("verify: set evalType");

        const node& leftEval = it.getLeft().getEval();
        if(nul(leftEval)) return _srcErr(errCode::LHS_IS_NULL);
        const wtype& ltype = it.getLeft().getEval().getType();
        if(nul(ltype)) return _srcErr(errCode::LHS_IS_NULL);
        const node& rightEval = it.getRight().getEval();
        if(nul(rightEval)) return _srcErr(errCode::RHS_IS_NULL);
        const wtype& rtype = it.getRight().getEval().getType();
        if(nul(rtype)) return _srcErr(errCode::RHS_IS_NULL);

        if(!ltype.isImpli(rtype))
            return _srcErr(errCode::TYPE_NOT_COMPATIBLE, ltype.getName().c_str(), rtype.getName()
                    .c_str());
    })

    WRD_VERIFY({
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
        //          AssignExpr(getExpr(getExpr(A, B), NAME), wInt(5))
        //      so, only I need to check is, lhs of AssignExpr is kind of getExpr() or not.
        //      I can care about that the last expression is valid.
        WRD_DI("verify: checks rvalue");

        const node& lhs = it.getLeft();
        if(!lhs.isSub<getExpr>()/* TODO: && !lhs.isSub<ElementExpr>()*/)
            return _srcErr(errCode::ASSIGN_TO_RVALUE, it.getRight().getType().getName().c_str(),
                    lhs.getType().getName().c_str());
    })

    WRD_VERIFY({
        WRD_DI("verify: assignExpr: visit subNodes");

        verify((node&) it.getLeft());
        verify((node&) it.getRight());
    })
}
