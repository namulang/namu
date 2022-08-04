#pragma once

#include "../func.hpp"
#include "../exprs/blockExpr.hpp"
#include "../../builtin/container/native/tnmap.hpp"

namespace namu {

    typedef tnmap<std::string, node, immutableTactic> scope;
    class _nout mgdFunc : public func {
        NAMU(CLASS(mgdFunc, func),
            FRIEND_VERIFY(mgdFunc, subNodes))

    public:
        explicit mgdFunc(const params& ps, const node& retType);
        explicit mgdFunc(const params& ps, const node* retType);
        explicit mgdFunc(const params& ps, const node& retType, const blockExpr& newBlock);
        explicit mgdFunc(const params& ps, const node* retType, const blockExpr& newBlock);

    public:
        blockExpr& getBlock();
        const blockExpr& getBlock() const;
        const node& getRet() const override;
        nbicontainer& subs() override;
        const params& getParams() const override;

        using super::run;
        str run(const ucontainable& args) override;

        void setPos(const point& new1) override {
            _pos = new1;
        }

        const point& getPos() const override {
            return _pos;
        }

    private:
        void _inFrame(const bicontainable& args) override;
        void _outFrame() override;
        scope* _evalArgs(const ucontainable& args);

    private:
        params _params;
        nmap _shares;
        str _retType;
        tstr<blockExpr> _blk;
    };
}
