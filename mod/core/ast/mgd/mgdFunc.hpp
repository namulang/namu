#pragma once

#include "../func.hpp"
#include "../exprs/blockExpr.hpp"
#include "../../builtin/container/native/tnmap.hpp"

namespace namu {

    class visitor;

    typedef tnmap<std::string, node, immutableTactic> scope;
    class _nout mgdFunc : public func {
        NAMU(CLASS(mgdFunc, func), VISIT())
        friend class verifier;

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
        str run(const args& a) override;

        void setPos(const point& new1) override {
            _pos = new1;
        }

        const point& getPos() const override {
            return _pos;
        }

        void inFrame(const bicontainable& args) override;
        void outFrame() override;

    private:
        scope* _evalArgs(const ucontainable& args);

    private:
        params _params;
        nmap _shares;
        str _retType;
        tstr<blockExpr> _blk;
    };
}
