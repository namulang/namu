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

        wbool checkEvalType(const wtype& eval) {
            if(nul(eval)) return false;
            for(const wtype* e : primitives)
                if(eval.isSub(*e))
                    return true;

            return false;
        }
    }

    const wtype& me::getEvalType() const {
        if(!_lhs || !_rhs) return nulOf<wtype>();

        return _lhs->getEvalType().reduce(_rhs->getEvalType());
    }

    WRD_VERIFY({
        WRD_DI("verify: addExpr: lhs & rhs should bind something.");

        const node& lhs = it.getLeft();
        const node& rhs = it.getRight();
        if(nul(lhs)) return _srcErr(errCode::LHS_IS_NULL);
        if(nul(rhs)) return _srcErr(errCode::RHS_IS_NULL);
        const wtype& lEval = lhs.getEvalType();
        const wtype& rEval = rhs.getEvalType();
        if(nul(lEval)) return _srcErr(errCode::LHS_IS_NULL);
        if(nul(rEval)) return _srcErr(errCode::RHS_IS_NULL);

        if(!checkEvalType(lEval)) return _srcErr(errCode::LHS_IS_NOT_ARITH, lEval.getName().c_str());
        if(!checkEvalType(rEval)) return _srcErr(errCode::RHS_IS_NOT_ARITH, rEval.getName().c_str());
    })

}
