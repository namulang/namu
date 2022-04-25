#pragma once

#include "../func.hpp"
#include "../scope.hpp"
#include "../exprs/blockExpr.hpp"

namespace wrd {

    class mgdFunc : public func {
        WRD(CLASS(mgdFunc, func),
            FRIEND_VERIFY(mgdFunc, subNodes))

    public:
        explicit mgdFunc(const params& ps, const wtype& evalType)
            : super(), _params(ps), _evalType(&evalType), _blk(new blockExpr()) {}
        explicit mgdFunc(const params& ps, const wtype& evalType, const blockExpr& newBlock)
            : super(), _params(ps), _evalType(&evalType), _blk(newBlock) {}

    public:
        blockExpr& getBlock() { return *_blk; }
        const blockExpr& getBlock() const { return *_blk; }
        const wtype& getEvalType() const override { return *_evalType; }
        nbicontainer& subs() override { return _shares; }
        const params& getParams() const override { return _params; }

        using super::run;
        str run(const ucontainable& args) override;

    private:
        wbool _inFrame(scope& args);
        void _outFrame();
        scope* _evalArgs(const ucontainable& args);

    private:
        params _params;
        nmap _shares;
        const wtype* _evalType;
        tstr<blockExpr> _blk;
    };
}
