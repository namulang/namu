#pragma once

#include "../func.hpp"
#include "../exprs/blockExpr.hpp"
#include "../ref.hpp"

namespace wrd {

    class mgdFunc : public func {
        WRD(CLASS(mgdFunc, func),
            FRIEND_VERIFY(mgdFunc, subNodes))

    public:
        explicit mgdFunc(const signature& sig, const wtype& evalType)
            : super(), _sig(sig), _evalType(&evalType), _blk(new blockExpr()) {}
        explicit mgdFunc(const signature& sig, const wtype& evalType, const blockExpr& newBlock)
            : super(sig), _evalType(&evalType), _blk(newBlock) {}

    public:
        blockExpr& getBlock() { return *_blk; }
        const blockExpr& getBlock() const { return *_blk; }
        const wtype& getEvalType() const override { return *_evalType; }
        nbicontainer& subs() override { return _shares; }
        wbool doesNeedScope() const override { return true; }
        const signature& getSignature() const override { return _sig; }

    protected:
        str _onCastArgs(narr& castedArgs) override;

    private:
        narr& _nameArgs(narr& args);
        wbool _inFrame(narr& args);
        void _outFrame();

    private:
        signature _sig;
        nmap _shares;
        const wtype* _evalType;
        tstr<blockExpr> _blk;
    };
}
