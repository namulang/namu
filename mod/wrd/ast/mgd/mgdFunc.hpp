#pragma once

#include "../func.hpp"
#include "../exprs/blockExpr.hpp"
#include "../ref.hpp"

namespace wrd {

    class mgdFunc : public func {
        WRD(CLASS(mgdFunc, func))

    public:
        explicit mgdFunc(const std::string& name, const params& p, const wtype& evalType)
            : super(name), _params(p), _evalType(&evalType), _blk(new blockExpr()) {}
        explicit mgdFunc(const std::string& name, const params& p, const wtype& evalType, const blockExpr& newBlock)
            : super(name), _params(p), _evalType(&evalType), _blk(newBlock) {}

    public:
        blockExpr& getBlock() { return *_blk; }
        const blockExpr& getBlock() const { return *_blk; }
        const params& getParams() const override { return _params; }
        const wtype& getEvalType() const override { return *_evalType; }
        ncontainer& subs() override { return _shares; }

    protected:
        str _onCastArgs(narr& castedArgs) override;

    private:
        narr _shares;
        params _params;
        const wtype* _evalType;
        tstr<blockExpr> _blk;
    };
}
