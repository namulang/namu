#include "FAOExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"
#include "../../frame/thread.hpp"
#include "../../builtin/primitive.hpp"

namespace namu {

    NAMU_DEF_ME(FAOExpr)

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
    }

    const node& me::getEval() const {
        if(!_lhs || !_rhs) return nulOf<node>();
        const node& lhsEval = _lhs->getEval();
        if(nul(lhsEval)) return nulOf<node>();
        const node& rhsEval = _rhs->getEval();
        if(nul(rhsEval)) return nulOf<node>();

        return lhsEval.reduce(rhsEval);
    }

    NAMU_VERIFY({
        NAMU_DI("verify: FAOExpr: lhs & rhs should bind something.");

        const node& lhs = it.getLeft();
        const node& rhs = it.getRight();
        if(nul(lhs)) return _srcErr(errCode::LHS_IS_NULL);
        if(nul(rhs)) return _srcErr(errCode::RHS_IS_NULL);

        NAMU_DI("verify: FAOExpr: finding eval of l(r)hs.");
        const node& lEval = lhs.getEval();
        const node& rEval = rhs.getEval();
        if(nul(lEval)) return _srcErr(errCode::LHS_IS_NULL);
        if(nul(rEval)) return _srcErr(errCode::RHS_IS_NULL);

        if(!checkEvalType(lEval)) return _srcErr(errCode::LHS_IS_NOT_ARITH, lEval.getType().getName().c_str());
        if(!checkEvalType(rEval)) return _srcErr(errCode::RHS_IS_NOT_ARITH, rEval.getType().getName().c_str());
    })

}
