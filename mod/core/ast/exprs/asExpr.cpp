#include "asExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"
#include "../../frame/thread.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(asExpr), DEF_VISIT())

    NAMU_VERIFY({
        NAMU_DI("verify: asExpr: _me & _as aren't null");

        if(nul(it.getMe())) return _srcErr(errCode::LHS_IS_NULL);
        if(nul(it.getAs())) return _srcErr(errCode::RHS_IS_NULL);

        NAMU_DI("...verified: asExpr: _me & _as aren't null");
    })

    NAMU_VERIFY({
        NAMU_DI("verify: asExpr: checks that me can cast to 'as'");

        if(!it.getMe().is(it.getAs()))
            return _srcErr(errCode::CAST_NOT_AVAILABLE, it.getMe().getType().getName().c_str(),
                    it.getAs().getType().getName().c_str());

        NAMU_DI("...verified: asExpr: checks that me can cast to 'as'");
    })

    NAMU_VERIFY({
        NAMU_DI("verify: asExpr: rhs shouldn't be expression");

        if(it.getAs().isSub<expr>())
            return _srcErr(errCode::EXPR_SHOULDNT_BE_HERE);

        NAMU_DI("...verified: asExpr: rhs shouldn't be expression");
    })
}
