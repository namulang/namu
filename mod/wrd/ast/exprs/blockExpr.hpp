#pragma once

#include "../expr.hpp"
#include "../../frame/frameInteractable.hpp"

namespace wrd {

    class blockExpr : public expr, public frameInteractable {
        WRD(CLASS(blockExpr, expr, expr::exprType))
        friend class mgdFunc;

    public:
        blockExpr() {}
        blockExpr(std::initializer_list<const expr*> elems): _exprs(elems) {}
        template <typename... Es>
        blockExpr(const Es&... elems): _exprs(elems...) {}

    public:
        using super::subs;
        ncontainer& subs() override {
            return _exprs;
        }

        using super::run;
        str run(const containable& args) override {
            str ret;
            for(auto e=_exprs.begin<expr>(); e ; ++e)
                ret = e->run(nulOf<containable>());

            return ret;
        }

        const wtype& getEvalType() const override {
            wcnt len = _exprs.len();
            if(len <= 0) return nulOf<wtype>();

            return _exprs[len-1].getEvalType();
        }

    protected:
        wbool _onInFrame(frame& fr, const containable& args) override;
        wbool _onOutFrame(frame& fr, const containable& args) override;

    private:
        tnarr<expr> _exprs;
    };
}
