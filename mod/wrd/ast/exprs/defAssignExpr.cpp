#include "defAssignExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"

namespace wrd {
    WRD_DEF_ME(defAssignExpr)

    str me::run(const ucontainable& args) {
        frame& fr = thread::get()._getNowFrame();
        str new1 = _rhs->run();
        if(!new1)
            return WRD_E("new1 is null"), str();

        fr.pushLocal(_name, *new1);
        return new1;
    }

    WRD_VERIFY({
        WRD_DI("verify: defAssignExpr: duplication of variable.");

        const scopes& top = thread::get().getNowFrame().getTop();
        if(nul(top)) return;
        const std::string name = it.getSubName();
        if(top.getContainer().has(name))
            return _srcErr(errCode::ALREADY_DEFINED_VAR, name.c_str(), it.getEvalType().getName()
                    .c_str());
    })

    WRD_VERIFY({
        WRD_DI("verify: defAssignExpr: isRunnable");

        if(!it.getRight().run())
            _srcErr(errCode::CANT_DEF_VAR, it.getSubName().c_str(), it.getEvalType().getName()
                    .c_str());
    })

    WRD_VERIFY({
        WRD_DI("verify: defAssignExpr: visitSubNodes");
        // TODO:
    })
}
