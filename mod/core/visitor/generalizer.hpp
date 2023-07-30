#pragma once

#include "visitor.hpp"
#include "../ast/params.hpp"

namespace namu {

    class _nout generalizer: public visitor {
        NAMU(ME(generalizer, visitor))

    public:
        me& add(const param& newParam);

        using super::onVisit;
        void onVisit(visitInfo i, asExpr& me) override;
        void onVisit(visitInfo i, blockExpr& me) override;
        void onVisit(visitInfo i, defVarExpr& me) override;
        void onVisit(visitInfo i, runExpr& me) override;
        void onVisit(visitInfo i, func& me) override;
        void onVisit(visitInfo i, ctor& me) override;
        void onVisit(visitInfo i, params& me);
        void onVisit(visitInfo i, FBOExpr& me) override;
        void onVisit(visitInfo i, baseObj& me) override;
        void onVisit(visitInfo i, getGenericExpr& me) override;

    private:
        const node& _findOrigin(const node& toReplace) const;

    private:
        params _params;
    };
}
