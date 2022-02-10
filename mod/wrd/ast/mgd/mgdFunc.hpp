#pragma once

#include "../func.hpp"
#include "../exprs/blockExpr.hpp"

namespace wrd {

    class mgdFunc : public func {
        WRD(CLASS(mgdFunc, func))

    public:
        explicit mgdFunc(const std::string& name, const wtypes& params, const wtype& evalType)
            : super(name), _params(params), _evalType(&evalType), _blk(new blockExpr()) {}
        explicit mgdFunc(const std::string& name, const wtypes& params, const wtype& evalType, const blockExpr& newBlock)
            : super(name), _params(params), _evalType(&evalType), _blk(newBlock) {}

    public:
        blockExpr& getBlock() { return *_blk; }
        const blockExpr& getBlock() const { return *_blk; }
        const wtypes& getParams() const override { return _params; }
        const wtype& getEvalType() const override {
            return *_evalType;
        }

        ncontainer& subs() override {
            return _shares;
        }

    protected:
        str _onCastArgs(narr& castedArgs) override;

    private:
        narr _shares;
        wtypes _params;
        const wtype* _evalType;
        tstr<blockExpr> _blk;
    };
}
