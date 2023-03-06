#pragma once

#include "visitor.hpp"
#include "../ast/params.hpp"

namespace namu {

    class _nout generalizer: public visitor {
        NAMU(ME(generalizer, visitor))

    public:
        me& add(const param& newParam) {
            _params.add(newParam);
            return *this;
        }

        using super::onVisit;
        void onVisit(visitInfo i, asExpr& me) override;
        void onVisit(visitInfo i, blockExpr& me) override;
        void onVisit(visitInfo i, defVarExpr& me) override;
        void onVisit(visitInfo i, runExpr& me) override;
        void onVisit(visitInfo i, func& me) override;
        void onVisit(visitInfo i, params& me);
        void onVisit(visitInfo i, FBOExpr& me) override;
        void onVisit(visitInfo i, baseObj& me) override;

    private:
        const node& _findOrigin(const node& toReplace) const;

    private:
        params _params;
    };
}
