#pragma once

#include "../func.hpp"
#include "../exprs/blockExpr.hpp"

namespace wrd {

    class mgdFunc : public func {
        WRD(INTERFACE(mgdFunc, func))

    public:
        explicit mgdFunc(const std::string& name, const blockExpr* newBlock = new blockExpr()): super(name), _blk(newBlock) {}

    public:
        blockExpr& getBlock() { return *_blk; }
        const blockExpr& getBlock() const { return *_blk; }

        ncontainer& subs() override {
            return _shares;
        }

    protected:
        str _onCast(narr& castedArgs) override;

    private:
        tstr<blockExpr> _blk;
        narr _shares;
    };
}
