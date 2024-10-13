#pragma once

#include "../../ast/params.hpp"
#include "visitor.hpp"

namespace nm {

    class _nout generalizer: public visitor {
        NM(CLASS(generalizer, visitor))

    public:
        /// @param origin of generic object.
        me& add(const obj& origin);
        me& add(const param& newParam);
        me& add(const params& newParams);

        using super::onVisit;
        nbool onVisit(const visitInfo& i, asExpr& me) override;
        nbool onVisit(const visitInfo& i, blockExpr& me) override;
        nbool onVisit(const visitInfo& i, defVarExpr& me) override;
        nbool onVisit(const visitInfo& i, runExpr& me) override;
        nbool onVisit(const visitInfo& i, baseFunc& me) override;
        nbool onVisit(const visitInfo& i, ctor& me) override;
        nbool onVisit(const visitInfo& i, baseCtor& me) override;
        nbool onVisit(const visitInfo& i, params& me);
        nbool onVisit(const visitInfo& i, FBOExpr& me) override;
        nbool onVisit(const visitInfo& i, baseObj& me) override;
        nbool onVisit(const visitInfo& i, getGenericExpr& me) override;

    private:
        const node& _findOrigin(const node& toReplace) const;
        const node& _findOriginFrom(const getExpr& expr) const;
        const node& _findOriginFrom(const getGenericExpr& expr) const;

    private:
        params _params;
        tstr<obj> _org;
    };
}
