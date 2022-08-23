#pragma once

#include "../expr.hpp"

namespace namu {

    class _nout runExpr : public expr {
        NAMU(CLASS(runExpr, expr, expr::exprType))

    public:
        runExpr(const node& meObj, const node& subject, const args& a);
        runExpr(const node& meObj, const args& a);

    public:
        using super::run;
        str run(const args& a) override;

        const node& getEval() const override;

        node& getMe();
        const node& getMe() const;
        void setMe(const node& newMe);

        node& getSubject();
        const node& getSubject() const;

        args& getArgs();
        const args& getArgs() const;

    private:
        str _getSub(const args& a) const;
        str _getSub() const;

    private:
        str _me;
        args _args;
        mutable str _subject;
    };
}
