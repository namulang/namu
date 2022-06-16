#include "addExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"
#include "../../frame/thread.hpp"
#include "../../builtin/primitive.hpp"

namespace wrd {

    WRD_DEF_ME(addExpr)

    namespace {
        const wtype* primitives[] = {
            &ttype<wInt>::get(),
            &ttype<wFlt>::get(),
            &ttype<wStr>::get(),
            &ttype<wChar>::get(),
            &ttype<wBool>::get(),
        };

        wbool checkEvalType(const wtype& lEval) {
            for(const wtype* e : primitives)
                if(lEval.isSub(*e))
                    return true;

            return false;
        }
    }

    WRD_VERIFY({
        WRD_DI("verify: addExpr: lhs & rhs should bind something.");

        if(nul(it.getLeft())) _srcErr(errCode::LHS_IS_NULL);
        if(nul(it.getRight())) _srcErr(errCode::RHS_IS_NULL);

        const wtype& lEval = it.getLeft().getEvalType();
        const wtype& rEval = it.getRight().getEvalType();
        if(!checkEvalType(lEval)) _srcErr(errCode::LHS_IS_NOT_ARITH, lEval.getName().c_str());
        if(!checkEvalType(rEval)) _srcErr(errCode::RHS_IS_NOT_ARITH, rEval.getName().c_str());
    })

}
