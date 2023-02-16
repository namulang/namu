#pragma once

#include "loopExpr.hpp"

namespace namu {

    class frame;
    class _nout forExpr : public loopExpr {
        NAMU(CLASS(forExpr, loopExpr, expr::exprType), VISIT())
        friend class verifier;

    public:
        forExpr(const std::string& localName, const node& container, const blockExpr& blk);

    public:
        const std::string& getLocalName() const;
        str getContainer();

        using super::run;
        str run(const args& a) override;

        const node& getEval() const override;

    private:
        str _container;
        std::string _name;
        mutable nbool _initEval;
    };
}
