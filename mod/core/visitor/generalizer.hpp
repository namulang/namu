#pragma once

#include "visitor.hpp"
#include "../ast/params.hpp"

namespace namu {

    class generalizer: public visitor {
        NAMU(ME(generalizer, visitor))

    public:
        me& add(const param& newParam) {
            _params.add(newParam);
            return *this;
        }

        //void start() override;

        using super::onVisit;
        void onVisit(visitInfo i, asExpr& me) override;
        //void onVisit(visitInfo i, assignExpr& me) override;
        void onVisit(visitInfo i, blockExpr& me) override;
        //void onVisit(visitInfo i, defAssignExpr& me) override;
        void onVisit(visitInfo i, defVarExpr& me) override;
        //void onVisit(visitInfo i, FAOExpr& me) override;
        //void onVisit(visitInfo i, getExpr& me) override;
        //void onVisit(visitInfo i, returnExpr& me) override;
        //void onVisit(visitInfo i, runExpr& me) override;
        void onVisit(visitInfo i, mgdFunc& me) override;
        void onVisit(visitInfo i, params& me);
        void onVisit(visitInfo i, baseObj& me) override;
        //void onVisit(visitInfo i, genericObj& me) override;

    private:
        const node& _findOrigin(const node& toReplace) const;

    private:
        params _params;
    };
}
