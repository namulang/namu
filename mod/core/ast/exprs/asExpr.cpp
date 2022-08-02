#include "asExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"
#include "../../frame/thread.hpp"

namespace namu {

    WRD_DEF_ME(asExpr)

    WRD_VERIFY({
        WRD_DI("verify: asExpr: _me & _as aren't null");

        if(nul(it.getMe())) return _srcErr(errCode::LHS_IS_NULL);
        if(nul(it.getAs())) return _srcErr(errCode::RHS_IS_NULL);
    })

    WRD_VERIFY({
        WRD_DI("verify: asExpr: checks that me can cast to 'as'");

        if(!it.getMe().is(it.getAs()))
            return _srcErr(errCode::CAST_NOT_AVAILABLE, it.getMe().getType().getName().c_str(),
                    it.getAs().getType().getName().c_str());
    })

    WRD_VERIFY({
        WRD_DI("verify: asExpr: rhs shouldn't be expression");

        if(it.getAs().isSub<expr>())
            return _srcErr(errCode::EXPR_SHOULDNT_BE_HERE);
    })
}
