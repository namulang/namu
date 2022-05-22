#pragma once

#include "../func.hpp"
#include "../scope.hpp"
#include "../exprs/blockExpr.hpp"

namespace wrd {

    class _wout mgdFunc : public func {
        WRD(CLASS(mgdFunc, func),
            FRIEND_VERIFY(mgdFunc, subNodes))

    public:
        explicit mgdFunc(const params& ps, const wtype& retType)
            : super(), _params(ps), _retType(&retType), _blk(new blockExpr()) {}
        explicit mgdFunc(const params& ps, const wtype& retType, const blockExpr& newBlock)
            : super(), _params(ps), _retType(&retType), _blk(newBlock) {}

    public:
        blockExpr& getBlock() { return *_blk; }
        const blockExpr& getBlock() const { return *_blk; }
        const wtype& getRetType() const override { return *_retType; }
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
        const wtype* _retType;
        tstr<blockExpr> _blk;
    };
}
